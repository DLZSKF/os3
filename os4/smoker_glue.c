/*
 *    Filename           : smoker_glue.c
 *    Function           : 模拟拥有胶水的抽烟者 (需要烟草和纸)
 */
#include "ipc.h"



int main(int argc, char *argv[]) {
    int rate;
    if (argv[1] != NULL) rate = atoi(argv[1]);
    else rate = 4;

    sem_flg = IPC_CREAT | 0644;

    agent_sem_id = set_sem(KEY_AGENT_SEM, 1, sem_flg);
    smoker_glue_sem_id = set_sem(KEY_SMOKER_GLUE_SEM, 0, sem_flg);

    printf("Smoker with Glue (needs Tobacco & Paper) [%d] started.\n", getpid());

    while (1) {
        printf("Smoker with Glue [%d]: Waiting for Tobacco and Paper...\n", getpid());
        down(smoker_glue_sem_id); // 等待烟草和纸

        printf("Smoker with Glue [%d]: Got Tobacco and Paper. Making and smoking cigarette...\n", getpid());
        sleep(rate);

        printf("Smoker with Glue [%d]: Finished smoking. Signaling supplier.\n", getpid());
        up(agent_sem_id); // 通知供应者
    }

    return EXIT_SUCCESS;
}
