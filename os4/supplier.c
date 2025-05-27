/*
 *    Filename           : supplier.c
 *    Function           : 模拟供应者进程
 */
#include "ipc.h"

// 在ipc.h中已声明，这里提供定义（每个可执行文件都会有自己的副本，但它们通过key访问内核中的同一个信号量）


int main(int argc, char *argv[]) {
    int rate;
    if (argv[1] != NULL) rate = atoi(argv[1]);
    else rate = 2; // 默认2秒

    sem_flg = IPC_CREAT | 0644;

    // 初始化/获取信号量
    // agent_sem: 供应者信号，初始为1，表示供应者可以先放原料
    agent_sem_id = set_sem(KEY_AGENT_SEM, 1, sem_flg);
    // smoker_xxx_sem: 各个抽烟者等待的信号量，初始为0
    smoker_tobacco_sem_id = set_sem(KEY_SMOKER_TOBACCO_SEM, 0, sem_flg);
    smoker_paper_sem_id = set_sem(KEY_SMOKER_PAPER_SEM, 0, sem_flg);
    smoker_glue_sem_id = set_sem(KEY_SMOKER_GLUE_SEM, 0, sem_flg);

    int offer_type = 0; // 0: paper & glue, 1: tobacco & glue, 2: tobacco & paper

    printf("Supplier process [%d] started.\n", getpid());

    while (1) {
        down(agent_sem_id); // 等待上一轮抽烟结束，或者第一次开始供应

        printf("Supplier [%d]: ", getpid());
        switch (offer_type) {
            case 0: // 提供纸和胶水 (Paper & Glue)
                printf("Offering Paper and Glue. Waking Smoker with Tobacco.\n");
                up(smoker_tobacco_sem_id); // 唤醒有烟草的抽烟者
                break;
            case 1: // 提供烟草和胶水 (Tobacco & Glue)
                printf("Offering Tobacco and Glue. Waking Smoker with Paper.\n");
                up(smoker_paper_sem_id);   // 唤醒有纸的抽烟者
                break;
            case 2: // 提供烟草和纸 (Tobacco & Paper)
                printf("Offering Tobacco and Paper. Waking Smoker with Glue.\n");
                up(smoker_glue_sem_id);    // 唤醒有胶水的抽烟者
                break;
        }
        
        offer_type = (offer_type + 1) % 3; // 轮流提供
        // 供应者现在等待被唤醒 (通过 down(agent_sem_id) 在下一次循环开始时)
        // 抽烟者抽完后会 up(agent_sem_id)
        sleep(rate); // 模拟供应间隔
    }

    return EXIT_SUCCESS;
}
