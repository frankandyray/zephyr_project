#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>

/*功能:按鈕讓count++，再透過uart輸入讓count--。重點:uart、interrupt(gpio)、event、multithread*/

//定義event
#define EVENT_BUTTON_PRESS BIT(0)
#define EVENT_UART_DEC     BIT(1)

/*按鈕防呆*/
#if !DT_NODE_HAS_STATUS(DT_ALIAS(sw0), okay)
#error "This board does not have a sw0 alias in devicetree."
#endif

static struct k_event system_events; //定義event功能
static volatile int Count = 0;

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);//從DTS取出gpio的硬體位置(按鈕)

static struct gpio_callback button_cb;//定義中斷callback

K_MSGQ_DEFINE(uart_msg, sizeof(char), 10, 4); //定義UART傳輸時，Queue的大小
const struct device *uart_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));//UART根據DTS取dev的指標

/* UART RX callback */
static void serial_cb(const struct device *dev, void *user_data)
{
	ARG_UNUSED(user_data);
	//UART確認硬體是否有資料要傳出來
	if (!uart_irq_update(dev)) { 
		return;
	}

	if (!uart_irq_rx_ready(dev)) {
		return;
	}

	uint8_t c;
	while (uart_fifo_read(dev, &c, 1) == 1) {  //從硬體取出1筆資料
		k_msgq_put(&uart_msg, &c, K_NO_WAIT);	//將資料放入queue
	}
}

/* Button ISR: sw0 按下時 Count++ */
static void button_isr(const struct device *dev,
		       struct gpio_callback *cb,
		       uint32_t pins)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(cb);
	ARG_UNUSED(pins);

	Count++;
	k_event_post(&system_events, EVENT_BUTTON_PRESS);//公布目前持行的event是interuppt
}

/* 獨立 thread：通知現在執行的event */
void logic_thread(void *arg1, void *arg2, void *arg3)
{
	ARG_UNUSED(arg1);
	ARG_UNUSED(arg2);
	ARG_UNUSED(arg3);

	while (1) {
		uint32_t events = k_event_wait(&system_events,
					       EVENT_BUTTON_PRESS | EVENT_UART_DEC,
					       true,
					       K_FOREVER);//等待指定event

		if (events & EVENT_BUTTON_PRESS) {
			printk("[BUTTON] Count = %d\n", Count);
		}

		if (events & EVENT_UART_DEC) {
			printk("[UART] Count = %d\n", Count);
		}
	}
}

K_THREAD_DEFINE(logic_tid, 1024, logic_thread, NULL, NULL, NULL, 5, 0, 0);	//靜態定義thread，等效於K_THREAD_STACK_DEFINE->struct k_thread->k_thread_create

int main(void)
{
	int ret;
	char recv_char;

	printk("System start\n");
	printk("Press sw0 -> Count++\n");
	printk("Type '1' in UART -> Count--\n");

	k_event_init(&system_events);

	/* GPIO初始化確認*/
	if (!gpio_is_ready_dt(&button)) {//確認gpio是否可用
		printk("Error: button device is not ready\n");
		return -ENODEV;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT); //設定觸發的輸入輸出
	if (ret != 0) {
		printk("Error %d: failed to configure button pin\n", ret);
		return ret;
	}

	/*按鈕中斷確認*/
	ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);//設定是否為正負緣觸發
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt\n", ret);
		return ret;
	}

	gpio_init_callback(&button_cb, button_isr, BIT(button.pin)); //初始化GPIO中斷觸發

	ret = gpio_add_callback(button.port, &button_cb);//將GPIO中斷與ISR註冊
	if (ret != 0) {
		printk("Error %d: failed to add callback\n", ret);
		return ret;
	}

	/* UART初始化確認 */
	if (!device_is_ready(uart_dev)) {
		printk("UART device not ready\n");
		return -ENODEV;
	}

	ret = uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);
	if (ret < 0) {
		printk("Failed to set UART callback\n");
		return ret;
	}

	uart_irq_rx_enable(uart_dev);

	while (1) {
		if (k_msgq_get(&uart_msg, &recv_char, K_FOREVER) == 0) { //從queue取一筆資料出來

			if (recv_char == '\r' || recv_char == '\n') {
				continue;
			}

			printk("[Main] Received: %c\n", recv_char);

			if (recv_char == '1') {
				Count--;
				k_event_post(&system_events, EVENT_UART_DEC);//公布目前執行的事件是uart
			}
		}
	}

	return 0;
}