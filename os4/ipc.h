/*
 *    Filename           : ipc.h
 *    copyright          : (C) 2006 by zhonghonglie (modified for Smoker's Problem)
 *    Function           : 声明IPC机制的函数原型和全局变量 (for Smoker's Problem)
 */
#ifndef IPC_H
#define IPC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#define BUFSZ 256

// 建立或获取ipc的一组函数的原型说明
int get_ipc_id(char *proc_file, key_t key);
char *set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_msq(key_t msq_key, int msq_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int down(int sem_id);
int up(int sem_id);

/* 信号灯控制用的共同体 */
typedef union semuns {
    int val;
} Sem_uns;

/* 消息结构体 (not used in this version of smoker's problem) */
typedef struct msgbuf {
    long mtype;
    char mtext[1];
} Msg_buf;

// 为抽烟者问题定义的信号量键值
#define KEY_AGENT_SEM          500
#define KEY_SMOKER_TOBACCO_SEM 501
#define KEY_SMOKER_PAPER_SEM   502
#define KEY_SMOKER_GLUE_SEM    503

// 信号量ID (这些变量会在每个进程的main函数中被赋值)
extern int agent_sem_id;  // 使用 extern 声明
extern int smoker_tobacco_sem_id;
extern int smoker_paper_sem_id;
extern int smoker_glue_sem_id;

// 公用的标志位
extern int sem_flg;       // 使用 extern 声明

#endif // IPC_H
