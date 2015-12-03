/*
 * Threadpool.h
 *
 *  Created on: 22-Nov-2015
 *      Author: harry
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <iostream>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include "TaskThread.h"
#include "Task.h"

class ThreadPool
{
private:
    TaskThread *threads;
    pthread_mutex_t mutJob;
    sem_t semJob;
    pthread_t thAssign;
    std::queue<Task*> tasks;
    std::queue<TaskThread*> idleThreadsQueue; //APPROACH 2
public:
    ThreadPool(int n = 5);
    ~ThreadPool(){}

    void JoinThread(int threadNum);
    void ProcessTask(Task* t1);
    friend void* AssignTask(void* arg);

    static pthread_cond_t condThreadQueueWait; //APPROACH 2
    static pthread_mutex_t mutThreadQueue; //APPROACH 2
};

#endif /* THREADPOOL_H_ */
