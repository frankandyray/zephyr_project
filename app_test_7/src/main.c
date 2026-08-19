#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>     //adc相關函式庫
#include <zephyr/sys/printk.h>

/*功能:利用計時器每一秒觸發執行序中斷並執行adc訊號的讀取並顯示結果。重點:thread、Semaphore、timer、adc*/
/* adc接收腳位:pc0*/
/* 1. 定義硬體相關資訊 */
// 獲取 Device Tree 中的 ADC 節點 (假設標籤為 adc1)
#define ADC_NODE DT_NODELABEL(adc1)
static const struct device *adc_dev = DEVICE_DT_GET(ADC_NODE);  //adc硬體位置

#define ADC_RESOLUTION  12
#define ADC_CHANNEL     1       //通道選取
#define ADC_REFERENCE   ADC_REF_INTERNAL
#define ADC_GAIN        ADC_GAIN_1

/* 2. 定義同步工具與緩衝區 */
K_SEM_DEFINE(adc_sem, 0, 1);      // 定義 Semaphore，初始值為 0
static uint16_t sample_buffer;    // 存放 ADC 原始數值的緩衝區

/* 3. ADC 通道配置 */
static const struct adc_channel_cfg m_channel_cfg = {
    .gain             = ADC_GAIN,
    .reference        = ADC_REFERENCE,
    .acquisition_time = ADC_ACQ_TIME_DEFAULT,
    .channel_id       = ADC_CHANNEL,
    .differential     = 0,
};

/* 4. ADC 序列配置 */
static struct adc_sequence sequence = {
    .channels    = BIT(ADC_CHANNEL),
    .buffer      = &sample_buffer,
    .buffer_size = sizeof(sample_buffer),
    .resolution  = ADC_RESOLUTION,
};

/* 5. Timer 回呼函數：只負責釋放 Semaphore */
void my_timer_handler(struct k_timer *dummy)
{
    k_sem_give(&adc_sem); // 喚醒 Thread
}

/*靜態的timer初始化*/
K_TIMER_DEFINE(my_timer, my_timer_handler, NULL);

/* 6. 執行工作 Thread：負責讀取 ADC 並顯示結果 */
void adc_thread(void *p1, void *p2, void *p3)
{
    int err;    //用於檢驗的變數
    
    // ADC裝置準備確認
    if (!device_is_ready(adc_dev)) {
        printk("ADC device not ready\n");
        return;
    }

    // ADC通道準備確認
    err = adc_channel_setup(adc_dev, &m_channel_cfg);
    if (err < 0) {
        printk("ADC setup failed with error %d\n", err);
        return;
    }

    while (1) {
        // 等待 Timer 的訊號 (每秒一次)
        k_sem_take(&adc_sem, K_FOREVER);

        // 執行 ADC 讀取
        err = adc_read(adc_dev, &sequence); //資料會被讀進sequence函式中的sample_buffer
        if (err != 0) {
            printk("ADC read failed with error %d\n", err);
            continue;
        }

        /* 數值轉換邏輯 (假設參考電壓為 3300mV) */
        int32_t mv_value = sample_buffer;
        int32_t adc_vref = 3300; // 請根據你的板子參考電壓調整
        
        // 將原始碼轉換為毫伏(mV)並輸出結果
        adc_raw_to_millivolts(adc_vref, ADC_GAIN, ADC_RESOLUTION, &mv_value);
        printk("ADC Raw: %d | Voltage: %d mV\n", sample_buffer, mv_value);
    }
}

/* 定義 Thread：優先權設為 5 */
K_THREAD_DEFINE(adc_tid, 1024, adc_thread, NULL, NULL, NULL, 5, 0, 0);

int main(void)
{
    printk("ADC Thread with Semaphore starting...\n");
    // 啟動計時器：1秒後開始，之後每 1000ms 觸發一次
    k_timer_start(&my_timer, K_MSEC(1000), K_MSEC(1000));

    return 0;
}