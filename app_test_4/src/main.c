#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define STACK_SIZE      1024
#define LED_ON_TIME_MS  1000
#define SLEEP_TIME_MS   10000


/*功能:threadA每10秒喚醒threadB觸發3次閃爍。重點:gpio(led)、multithread、Semaphore*/

// 將初始值設為 0，最大值設為 1。這樣 A 一定要等 B 給了之後才能執行。
K_SEM_DEFINE(my_sem, 0, 1);

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void threadA(void *p1, void *p2, void *p3)
{
    if (!device_is_ready(led0.port)) {
        return;
    }
    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);

    while (1) {
        // 使用 K_FOREVER，Thread A 會在這裡掛起（Suspend），不占用 CPU
        // 直到 Thread B 執行 k_sem_give
        if (k_sem_take(&my_sem, K_FOREVER) == 0) {
            printk("Thread A: Triggered by Semaphore!\n");
            
            // 執行三次閃爍
            for (int i = 0; i < 3; i++) {
                gpio_pin_set_dt(&led0, 1);
                k_msleep(LED_ON_TIME_MS);
                gpio_pin_set_dt(&led0, 0);
                k_msleep(LED_ON_TIME_MS);
            }
        }
    }
}

void threadB(void *p1, void *p2, void *p3)
{
    while (1) {
        // 每 10 秒給予執行權限
        k_msleep(SLEEP_TIME_MS);
        printk("Thread B: Giving Semaphore...\n");
        k_sem_give(&my_sem);
    }
}

// 定義執行緒
K_THREAD_DEFINE(threada_id, STACK_SIZE, threadA, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(threadb_id, STACK_SIZE, threadB, NULL, NULL, NULL, 7, 0, 0);

// Zephyr 3.x 以後建議使用 int main(void)
int main(void)
{
    printk("System started, waiting for triggers...\n");
    return 0;
}