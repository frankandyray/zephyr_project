#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/*功能:建立3個執行序依序對count++，每家100次就休息3秒。重點:multithread、mutex*/

#define STACK_SIZE   1024 //定義thread大小
#define PRIORITY     5
#define NUM_THREADS  3

/* 定義互斥鎖*/
K_MUTEX_DEFINE(count_mutex);



/*可用以下的靜態thread替換，但須要放在main的前面

K_THREAD_DEFINE(t0_id, STACK_SIZE, counter_thread, INT_TO_POINTER(0), NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(t1_id, STACK_SIZE, counter_thread, INT_TO_POINTER(1), NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(t2_id, STACK_SIZE, counter_thread, INT_TO_POINTER(2), NULL, NULL, PRIORITY, 0, 0);

*/
/* 定義三個thread的名稱與記憶體大小 */
K_THREAD_STACK_DEFINE(thread0_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread1_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread2_stack, STACK_SIZE);

/*定義thread資料架構(status、priority、id)*/
static struct k_thread thread0_data;
static struct k_thread thread1_data;
static struct k_thread thread2_data;

/* 共享變數 */
static int count = 0;
static int turn = 0;                  // 0 -> thread1, 1 -> thread2, 2 -> thread3
static int64_t pause_until_ms = 0;    // 全域暫停到什麼時間點

void counter_thread(void *p1, void *p2, void *p3)
{
    int my_turn = POINTER_TO_INT(p1);   // 0, 1, 2
    int my_id   = my_turn + 1;          // 顯示用：1, 2, 3

    /*不使用*/
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while (1) {
        bool did_work = false;

        k_mutex_lock(&count_mutex, K_FOREVER);  //上鎖

        int64_t now = k_uptime_get();

        /* 若目前在全域休息時間內，先解鎖，稍後再試 */
        if (now < pause_until_ms) {
            k_mutex_unlock(&count_mutex);
            k_sleep(K_MSEC(50));
            continue;
        }

        /* 只有輪到自己的 thread 才能加 1 */
        if (turn == my_turn) {
            count++;
            printk("Thread %d -> count = %d\n", my_id, count);

            /* 換下一個 thread */
            turn = (turn + 1) % NUM_THREADS;
            did_work = true;

            /* count 每到 100 的倍數，全部休息 3 秒 */
            if ((count % 100) == 0) {
                pause_until_ms = k_uptime_get() + 3000;
                printk("count = %d,stop 3 seconds\n", count);
            }
        }

        k_mutex_unlock(&count_mutex);   //解鎖

        /*
         * 沒輪到自己：短暫休息避免一直搶 CPU
         * 做完一次：也稍微 sleep，讓其他 thread 更容易切進來
         */
        if (did_work) {
            k_sleep(K_MSEC(100));
        } else {
            k_sleep(K_MSEC(10));
        }
    }
}

void main(void)
{
    printk("Start 3 threads with mutex...\n");

    /*三個thread輪流執行count++*/

    k_thread_create(&thread0_data, thread0_stack, STACK_SIZE,
                    counter_thread,
                    INT_TO_POINTER(0), NULL, NULL,
                    PRIORITY, 0, K_NO_WAIT);

    k_thread_create(&thread1_data, thread1_stack, STACK_SIZE,
                    counter_thread,
                    INT_TO_POINTER(1), NULL, NULL,
                    PRIORITY, 0, K_NO_WAIT);

    k_thread_create(&thread2_data, thread2_stack, STACK_SIZE,
                    counter_thread,
                    INT_TO_POINTER(2), NULL, NULL,
                    PRIORITY, 0, K_NO_WAIT);
}