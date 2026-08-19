#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <stdlib.h>

/*功能:兩個執行續輪流每秒感測器讀取一組數值並輸出，同時切換兩顆LED燈。重點:gpio(2-LED)、sensor、multithread、mutex、spi(4條線:SCK->SCL、MOSI->SDA、MISO->SDO、CS->CS)*/

#define STACK_SIZE      1024
#define THREAD_PRIORITY 5
#define TOTAL_SAMPLES   10
#define OBSERVE_MS      1000    //幾秒讀一次值

/* 感測器 */
#define ADXL345_NODE DT_NODELABEL(adxl345)

/* 兩顆 LED */
#define LED1_NODE DT_ALIAS(led0)
#define LED2_NODE DT_ALIAS(led1)

/* 建立 mutex */
K_MUTEX_DEFINE(sensor_mutex);

/* 建立兩個 thread stack 與控制塊 */
K_THREAD_STACK_DEFINE(thread1_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread2_stack, STACK_SIZE);
static struct k_thread thread1_data;
static struct k_thread thread2_data;

/* 裝置 */
static const struct device *dev = DEVICE_DT_GET(ADXL345_NODE);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

/* 共用統計資料 */
static int sample_count = 0;
static int64_t sum_x = 0;
static int64_t sum_y = 0;
static int64_t sum_z = 0;
static bool finished = false;

/* 把 sensor_value 轉成「微單位」整數，避免用浮點 printf */
static int64_t sensor_value_to_micro_int(const struct sensor_value *val)
{
    return ((int64_t)val->val1 * 1000000LL) + val->val2;
}

/* 印出微單位數值，例如 1234567 -> 1.234567 */
static void print_micro_value(const char *name, int64_t value)
{
    int64_t int_part = value / 1000000LL;
    int64_t frac_part = llabs(value % 1000000LL);

    printk("%s: %lld.%06lld", name, int_part, frac_part);
}


/*感測器讀取數值(使用mutex)，並切換LED*/
void sensor_thread(void *p1, void *p2, void *p3)
{
    const struct gpio_dt_spec *led = (const struct gpio_dt_spec *)p1;
    const char *thread_name = (const char *)p2;
    ARG_UNUSED(p3);

    struct sensor_value acc[3];

    while (1) {
        k_mutex_lock(&sensor_mutex, K_FOREVER);

        if (finished) {
            k_mutex_unlock(&sensor_mutex);
            break;
        }

        /* 每1秒讀一次*/
        printk("[%s] observation delay 1 second...\n", thread_name);
        k_msleep(OBSERVE_MS);

        if (sensor_sample_fetch(dev) < 0) {
            printk("[%s] samples receive failed\n", thread_name);
            k_mutex_unlock(&sensor_mutex);
            k_msleep(100);
            continue;
        }

        if (sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, acc) < 0) {
            printk("[%s] read XYZ failed\n", thread_name);
            k_mutex_unlock(&sensor_mutex);
            k_msleep(100);
            continue;
        }

        int64_t x = sensor_value_to_micro_int(&acc[0]);
        int64_t y = sensor_value_to_micro_int(&acc[1]);
        int64_t z = sensor_value_to_micro_int(&acc[2]);

        sample_count++;
        sum_x += x;
        sum_y += y;
        sum_z += z;

        printk("[%s] Sample %d -> ", thread_name, sample_count);
        print_micro_value("X", x);
        printk(", ");
        print_micro_value("Y", y);
        printk(", ");
        print_micro_value("Z", z);
        printk(" (m/s^2)\n");

        /* 讀完數值後切換 LED */
        gpio_pin_toggle_dt(led);

        if (sample_count >= TOTAL_SAMPLES) {
            int64_t avg_x = sum_x / TOTAL_SAMPLES;
            int64_t avg_y = sum_y / TOTAL_SAMPLES;
            int64_t avg_z = sum_z / TOTAL_SAMPLES;

            printk("\n===== Final Average (%d samples) =====\n", TOTAL_SAMPLES);
            print_micro_value("AVG X", avg_x);
            printk(" (m/s^2)\n");
            print_micro_value("AVG Y", avg_y);
            printk(" (m/s^2)\n");
            print_micro_value("AVG Z", avg_z);
            printk(" (m/s^2)\n");
            printk("======================================\n");

            finished = true;
        }

        k_mutex_unlock(&sensor_mutex);

        k_msleep(100);
    }

    printk("[%s] thread finished\n", thread_name);
}

void main(void)
{
    printk("ADXL345 two thread mutex start testing...\n");

    if (!device_is_ready(dev)) {
        printk("ADXL345 error!\n");
        return;
    }

    if (!gpio_is_ready_dt(&led1)) {
        printk("LED0 error!\n");
        return;
    }

    if (!gpio_is_ready_dt(&led2)) {
        printk("LED1 error!\n");
        return;
    }

    if (gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE) < 0) {
        printk("LED0 setting failed!\n");
        return;
    }

    if (gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE) < 0) {
        printk("LED1 setting failed!\n");
        return;
    }

    k_thread_create(&thread1_data, thread1_stack, STACK_SIZE,
                    sensor_thread,
                    (void *)&led1, (void *)"Thread-1", NULL,
                    THREAD_PRIORITY, 0, K_NO_WAIT);

    k_thread_create(&thread2_data, thread2_stack, STACK_SIZE,
                    sensor_thread,
                    (void *)&led2, (void *)"Thread-2", NULL,
                    THREAD_PRIORITY, 0, K_NO_WAIT);
}