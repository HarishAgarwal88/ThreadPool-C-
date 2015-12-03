/*
 * TaskThread.h
 *
 *  Created on: 22-Nov-2015
 *      Author: harry
 */

#ifndef TASKTHREAD_H_
#define TASKTHREAD_H_

#include <iostream>
#include <pthread.h>
#include <queue>
#include <semaphore.h>
#include "Task.h"
#include "ThreadpoolCommon.h"

class TaskThread
{
private:
    static int Count;
    int threadNum;
    sem_t semAssign;
    bool bThreadIdle;
    Task *t1;
    pthread_t threadId;
public:
    TaskThread();
    ~TaskThread(){}
    void SemAssign(eSemOperation flag);
    void UpdateStatus(eThreadStatus flag);
    int GetThreadNum() { return threadNum; }
    pthread_t GetThreadId() { return threadId; }
    bool isThreadIdle() { return (bThreadIdle == E_THREAD_IDLE) ? true : false ; }
    void AssignTask(Task *task) { t1 = task; SemAssign(E_SEM_POST);} //APPROACH 2
    bool ProcessTask() { return t1->ExecuteTask();}
    void SetIdleThreadQueue(std::queue<TaskThread*>  *threadQueue) {idleThreadQueue = threadQueue;} //APPROACH 2

    std::queue<TaskThread* >  *idleThreadQueue; //APPROACH 2
};


#endif /* TASKTHREAD_H_ */
