/*
 *    Filename           : smoker_tobacco.c
 *    Function           : 模拟拥有烟草的抽烟者 (需要纸和胶水)
 */
#include "ipc.h"

// 在ipc.h中已声明


int main(int argc, char *argv[]) {
    int rate;
    if (argv[1] != NULL) rate = atoi(argv[1]);
    else rate = 4; // 默认3秒

    sem_flg = IPC_CREAT | 0644; // 通常由supplier创建，这里确保能获取

    // 获取信号量ID (这些信号量应该已由supplier创建并初始化)
    // 如果supplier未运行，set_sem会尝试创建它们，但初始值可能不符合预期
    // 最好先运行supplier来正确初始化信号量
    agent_sem_id = set_sem(KEY_AGENT_SEM, 1, sem_flg); // 获取，supplier将其设为1或0
    smoker_tobacco_sem_id = set_sem(KEY_SMOKER_TOBACCO_SEM, 0, sem_flg); // 获取，supplier将其设为0

    printf("Smoker with Tobacco (needs Paper & Glue) [%d] started.\n", getpid());

    while (1) {
        printf("Smoker with Tobacco [%d]: Waiting for Paper and Glue...\n", getpid());
        down(smoker_tobacco_sem_id); // 等待纸和胶水

        printf("Smoker with Tobacco [%d]: Got Paper and Glue. Making and smoking cigarette...\n", getpid());
        sleep(rate); // 模拟制作和抽烟

        printf("Smoker with Tobacco [%d]: Finished smoking. Signaling supplier.\n", getpid());
        up(agent_sem_id); // 通知供应者可以放下一轮原料
    }

    return EXIT_SUCCESS;
}
