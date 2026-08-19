#include <zephyr/kernel.h>          //必備
#include <zephyr/device.h>          //必備
#include <zephyr/drivers/uart.h>    //電腦傳資料到板子
#include <zephyr/drivers/gpio.h>    // led燈需要用到的函數庫
#include <zephyr/sys/printk.h>      //系統列印

/*功能:輸入1、2、3分別讓三顆LED燈閃一次，重點:gpio、uart、queue*/

#define LED_ON_TIME_MS 1000
/*定義三顆LED燈*/
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

/* 三顆led燈的防呆*/
#if !DT_NODE_HAS_STATUS_OKAY(LED0_NODE)
#error "led0 alias is not defined in devicetree"
#endif

#if !DT_NODE_HAS_STATUS_OKAY(LED1_NODE)
#error "led1 alias is not defined in devicetree"
#endif

#if !DT_NODE_HAS_STATUS_OKAY(LED2_NODE)
#error "led2 alias is not defined in devicetree"
#endif



K_MSGQ_DEFINE(uart_msg, sizeof(char), 10, 4);   //定義queue名稱為uart_msg，每次接收一個字元，對多可接收10個

const struct device *uart_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console)); //取得硬體(板子)指標位置

/*初始化3顆LED燈*/
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

void threadA(void *p1, void *p2, void *p3)
{
    char c;
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    if (!uart_irq_update(p1)) {
        return;
    }

    if (uart_irq_rx_ready(p1)) {   //接收端準備
        while (uart_fifo_read(p1, &c, 1) == 1) {   //裝置從硬體的fifo buffer讀取資料
            if (k_msgq_put(&uart_msg, &c, K_NO_WAIT) != 0) {    //將讀取的資料放入queue
                printk("putting data in queue...\n");
                
            }
        }
    }
}

void threadB(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);
    char recv_char;
    while (1) {
        if (k_msgq_get(&uart_msg, &recv_char, K_FOREVER) == 0) {    //讀取queue資料(uart_msg)，並放入recv_char變數

            if (recv_char == '\r' || recv_char == '\n') {
                continue;
            }


            printk("[Main] Received: %c\n", recv_char);

            if (recv_char == '1') {
                gpio_pin_set_dt(&led0, 1);  //燈亮
                k_sleep(K_MSEC(LED_ON_TIME_MS));
                gpio_pin_set_dt(&led0, 0);  //燈暗
            } else if (recv_char == '2') {
                gpio_pin_set_dt(&led1, 1);
                k_sleep(K_MSEC(LED_ON_TIME_MS));
                gpio_pin_set_dt(&led1, 0);
            }else if (recv_char == '3') {
                gpio_pin_set_dt(&led2, 0);
                k_sleep(K_MSEC(LED_ON_TIME_MS));
                gpio_pin_set_dt(&led2, 1);
            } else {
                printk("Please type 1 or 2 or 3\n");
            }
        }
    }
}




K_THREAD_DEFINE(threada_id, STACK_SIZE, threadA, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(threadb_id, STACK_SIZE, threadB, NULL, NULL, NULL, 7, 0, 0);

int main(void)
{
    char recv_char;
    int ret;
    /*板子準備*/
    if (!device_is_ready(uart_dev)) {
        printk("UART device not ready\n");
        return 0;
    }
    /*led燈準備*/
    if (!gpio_is_ready_dt(&led0)) {
        printk("led0 device not ready\n");
        return 0;
    }

    if (!gpio_is_ready_dt(&led1)) {
        printk("led1 device not ready\n");
        return 0;
    }
	if (!gpio_is_ready_dt(&led2)) {
        printk("led2 device not ready\n");
        return 0;
    }
    /*三顆LED燈設為輸出模式*/
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        printk("Failed to configure led0\n");
        return 0;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        printk("Failed to configure led1\n");
        return 0;
    }

	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        printk("Failed to configure led2\n");
        return 0;
    }

    ret = uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);      //板子收到uart資料時，觸發serial_cb函式
    if (ret < 0) {
        printk("Failed to set UART callback\n");
        return 0;
    }

    uart_irq_rx_enable(uart_dev);   //觸發板子接收功能

    printk("UART Queue Demo Started.\n");
    printk("Type 1 -> led0 ON for 1 second\n");
    printk("Type 2 -> led1 ON for 1 second\n");
	printk("Type 3 -> led1 ON for 1 second\n");


    return 0;
}