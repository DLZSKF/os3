/*
 *    Filename           : smoker_paper.c
 *    Function           : 模拟拥有纸的抽烟者 (需要烟草和胶水)
 */
#include "ipc.h"



int main(int argc, char *argv[]) {
    int rate;
    if (argv[1] != NULL) rate = atoi(argv[1]);
    else rate = 4;

    sem_flg = IPC_CREAT | 0644;

    agent_sem_id = set_sem(KEY_AGENT_SEM, 1, sem_flg);
    smoker_paper_sem_id = set_sem(KEY_SMOKER_PAPER_SEM, 0, sem_flg);

    printf("Smoker with Paper (needs Tobacco & Glue) [%d] started.\n", getpid());

    while (1) {
        printf("Smoker with Paper [%d]: Waiting for Tobacco and Glue...\n", getpid());
        down(smoker_paper_sem_id); // 等待烟草和胶水

        printf("Smoker with Paper [%d]: Got Tobacco and Glue. Making and smoking cigarette...\n", getpid());
        sleep(rate);

        printf("Smoker with Paper [%d]: Finished smoking. Signaling supplier.\n", getpid());
        up(agent_sem_id); // 通知供应者
    }

    return EXIT_SUCCESS;
}
