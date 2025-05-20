#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

// 定义三种材料
#define TOBACCO 0  // 烟草
#define PAPER 1    // 纸
#define GLUE 2     // 胶水

// 全局信号量
sem_t supplier_sem;      // 供应者信号量
sem_t smoker_sem[3];      // 三个抽烟者信号量
pthread_mutex_t mutex;    // 互斥锁

// 供应者线程函数
void* supplier(void* arg) {
    while (1) {
        // 获取供应者信号量
        sem_wait(&supplier_sem);
        
        pthread_mutex_lock(&mutex);
        
        // 随机选择提供的两种材料组合
        int combination = rand() % 3;
        if (combination == 0) {
            printf("供应者提供了: 纸和胶水\n");
            // 通知有烟草的抽烟者
            sem_post(&smoker_sem[TOBACCO]);
        } else if (combination == 1) {
            printf("供应者提供了: 烟草和胶水\n");
            // 通知有纸的抽烟者
            sem_post(&smoker_sem[PAPER]);
        } else {
            printf("供应者提供了: 烟草和纸\n");
            // 通知有胶水的抽烟者
            sem_post(&smoker_sem[GLUE]);
        }
        
        pthread_mutex_unlock(&mutex);
        
        // 延迟一段时间
        sleep(rand() % 2 + 1);
    }
    
    return NULL;
}

// 抽烟者线程函数
void* smoker(void* arg) {
    int smoker_id = *(int*)arg;
    char* material_names[] = {"烟草", "纸", "胶水"};
    char* smoker_name = material_names[smoker_id];
    
    while (1) {
        // 等待自己的信号量
        sem_wait(&smoker_sem[smoker_id]);
        
        pthread_mutex_lock(&mutex);
        
        printf("拥有%s的抽烟者拿到了缺失材料，开始卷烟...\n", smoker_name);
        // 模拟卷烟和抽烟过程
        sleep(rand() % 2 + 1);
        printf("拥有%s的抽烟者抽完了烟，通知供应者继续供应\n\n", smoker_name);
        
        pthread_mutex_unlock(&mutex);
        
        // 通知供应者可以继续供应
        sem_post(&supplier_sem);
    }
    
    return NULL;
}

int main() {
    // 初始化随机数种子
    srand(time(NULL));
    
    // 初始化信号量
    sem_init(&supplier_sem, 0, 1);  // 供应者信号量初始为1
    for (int i = 0; i < 3; i++) {
        sem_init(&smoker_sem[i], 0, 0);  // 抽烟者信号量初始为0
    }
    
    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);
    
    // 创建线程
    pthread_t supplier_thread;
    pthread_t smoker_threads[3];
    int smoker_ids[3] = {TOBACCO, PAPER, GLUE};
    
    // 创建供应者线程
    pthread_create(&supplier_thread, NULL, supplier, NULL);
    
    // 创建三个抽烟者线程
    for (int i = 0; i < 3; i++) {
        pthread_create(&smoker_threads[i], NULL, smoker, &smoker_ids[i]);
    }
    
    // 等待线程结束
    pthread_join(supplier_thread, NULL);
    for (int i = 0; i < 3; i++) {
        pthread_join(smoker_threads[i], NULL);
    }
    
    // 销毁信号量和互斥锁
    sem_destroy(&supplier_sem);
    for (int i = 0; i < 3; i++) {
        sem_destroy(&smoker_sem[i]);
    }
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

