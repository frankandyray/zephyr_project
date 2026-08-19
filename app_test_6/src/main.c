#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/*功能:利用計時器每一秒觸發執行序並顯示thread running。重點:thread、Semaphore、timer*/

/* 定義計時器週期 */
#define TIMER_PERIOD K_MSEC(1000)

/* 1. 定義 Semaphore*/
K_SEM_DEFINE(my_sem, 0, 1);

/* 2. 給訊號到Semaphore */
void my_timer_handler(struct k_timer *dummy)
{
    
    k_sem_give(&my_sem);
}

/* 3. 建立計時器結構 */
struct k_timer my_timer;

/* 4. 獨立 Thread：負責處理繁重工作（此處為列印訊息） */
void logic_thread(void *p1, void *p2, void *p3)
{
    while (1) {
        /*從Semaphore拿訊號*/
        k_sem_take(&my_sem, K_FOREVER);
        
        // 執行工作
        printk("Thread Running.\n");
    }
}

/* 定義 Thread */
K_THREAD_DEFINE(logic_tid, 1024, logic_thread, NULL, NULL, NULL, 5, 0, 0);

int main(void)
{
    /* 初始化計時器 */
    k_timer_init(&my_timer, my_timer_handler, NULL);

    /* 啟動計時器：每秒觸發一次 */
    k_timer_start(&my_timer, TIMER_PERIOD, TIMER_PERIOD);

    return 0;
}