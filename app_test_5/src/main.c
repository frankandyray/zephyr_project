#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <stdio.h>

/*透過按鈕觸發中斷，執行從感測器讀去數值，並顯示在LCD顯示器上。重點:gpio(按鈕、sensor、LCD(不能接3.3V)、thread、Semaphore)*/
/*i2c1腳位:SCL->pb8、SDA->pb9*/
/*i2c3腳位:SCL->pc0、SDA->pc1*/
/* --- 硬體定義 --- */
// 根據你的 Overlay，LCD 在 i2c3，ADXL345 在 i2c1
static const struct i2c_dt_spec lcd_spec = I2C_DT_SPEC_GET(DT_ALIAS(lcd0));     //LED硬體定義
static const struct i2c_dt_spec adxl_spec = I2C_DT_SPEC_GET(DT_ALIAS(accel0));  //LCD硬體定義
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw1), gpios);   //按鈕硬體定義

/* LCD 控制位元 (PCF8574 對應 LCD1602 引腳) */
#define RS_BIT 0x01 // P0
#define RW_BIT 0x02 // P1
#define EN_BIT 0x04 // P2
#define BK_BIT 0x08 // P3 - 背光控制 (一定要為 1 才會亮)

/* 同步元件 */
K_SEM_DEFINE(button_sem, 0, 1); // Binary Semaphore

/* --- LCD 底層函式 --- */

static void lcd_write_nibble(uint8_t nibble, uint8_t rs) {
    uint8_t data = (nibble & 0xF0) | rs | BK_BIT;
    uint8_t pkt[2];

    // Enable high
    pkt[0] = data | EN_BIT;
    i2c_write_dt(&lcd_spec, &pkt[0], 1);
    k_usleep(1); // 脈衝寬度

    // Enable low
    pkt[1] = data;
    i2c_write_dt(&lcd_spec, &pkt[1], 1);
    k_usleep(50); // 指令執行時間
}

static void lcd_send_cmd(uint8_t cmd) {
    lcd_write_nibble(cmd & 0xF0, 0);       // 高 4 位
    lcd_write_nibble((cmd << 4) & 0xF0, 0); // 低 4 位
}

static void lcd_send_data(uint8_t data) {
    lcd_write_nibble(data & 0xF0, RS_BIT);
    lcd_write_nibble((data << 4) & 0xF0, RS_BIT);
}

static void lcd_init(void) {
    k_msleep(50);
    // 初始化為 4-bit 模式 (根據 HD44780 手冊)
    lcd_write_nibble(0x30, 0);
    k_msleep(5);
    lcd_write_nibble(0x30, 0);
    k_usleep(150);
    lcd_write_nibble(0x30, 0);
    lcd_write_nibble(0x20, 0);

    lcd_send_cmd(0x28); // 4-bit, 2-line, 5x8
    lcd_send_cmd(0x0C); // Display on, cursor off
    lcd_send_cmd(0x06); // Entry mode
    lcd_send_cmd(0x01); // Clear
    k_msleep(2);
}

static void lcd_send_string(const char *str) {
    while (*str) lcd_send_data(*str++);
}

/* --- 按鈕中斷 --- */
static struct gpio_callback button_cb_data;
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    k_sem_give(&button_sem); // 釋放信號量
}

/* --- 工作執行緒：不使用 Mutex，純由 Semaphore 觸發 --- */
void worker_thread(void) {
    uint8_t raw[6];
    uint8_t reg = 0x32; // ADXL345 DATAX0
    char buf[32];

    lcd_init();
    lcd_send_string("System Ready");

    while (1) {
        // 1. 等待按鈕按下 (Binary Semaphore)
        k_sem_take(&button_sem, K_FOREVER); 

        // 2. 顯示等待畫面
        lcd_send_cmd(0x01); // Clear Display
        k_msleep(2);
        
        lcd_send_cmd(0x80); // 第一行
        lcd_send_string("Resetting...");
        lcd_send_cmd(0xC0); // 第二行
        lcd_send_string("Please Wait...");

        // 模擬處理時間，讓使用者看清楚「等待」字樣
        k_msleep(800); 

        // 3. 直接進行 I2C 讀取 (不使用 mutex)
        int ret = i2c_write_read_dt(&adxl_spec, &reg, 1, raw, 6);

        if (ret == 0) {
            int16_t x = (int16_t)((raw[1] << 8) | raw[0]);
            int16_t y = (int16_t)((raw[3] << 8) | raw[2]);
            int16_t z = (int16_t)((raw[5] << 8) | raw[4]);

            lcd_send_cmd(0x01); // Clear
            k_msleep(2);

            // 第一行：顯示 X 和 Y
            // 使用 %-6d 格式化可以讓數字佔據固定寬度，畫面比較不會抖動
            snprintf(buf, sizeof(buf), "X:%d Y:%d", x, y);
            lcd_send_cmd(0x80); 
            lcd_send_string(buf);

            // 第二行：顯示 Z
            snprintf(buf, sizeof(buf), "Z:%d [OK]", z);
            lcd_send_cmd(0xC0); 
            lcd_send_string(buf);

            printk("Update Done -> X:%d Y:%d Z:%d\n", x, y, z);
        } else {
            lcd_send_cmd(0x01);
            lcd_send_string("I2C Error!");
            printk("Error: ADXL345 Read Failed\n");
        }

        // 5. 防彈跳延遲
        k_msleep(200);
    }
}

K_THREAD_DEFINE(worker_tid, 1024, worker_thread, NULL, NULL, NULL, 5, 0, 0);

int main(void) {
    if (!device_is_ready(lcd_spec.bus) || !device_is_ready(adxl_spec.bus)) {
        return 0;
    }

    // 初始化 ADXL345 (Measure Mode)
    uint8_t pwr_cmd[] = {0x2D, 0x08};
    i2c_write_dt(&adxl_spec, pwr_cmd, sizeof(pwr_cmd));

    // 配置按鈕
    gpio_pin_configure_dt(&button, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);

    return 0;
}