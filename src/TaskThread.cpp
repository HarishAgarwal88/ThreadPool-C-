/*
 * TaskThread.cpp
 *
 *  Created on: 22-Nov-2015
 *      Author: harry
 */

#include "Headers/TaskThread.h"
#include "Headers/Threadpool.h"
#include <iostream>
#include <stdlib.h>
#include <pthread.h>

int TaskThread::Count = 0;
void* func(void* arg);

TaskThread::TaskThread()
{
    threadNum = Count;
    bThreadIdle = E_THREAD_IDLE;
    Count++;
    t1 = NULL;

    int thRet = sem_init(&semAssign, 0, 0);
    if(thRet != 0)
    {
        std::cout << "Sem  Init Fail : " << threadNum <<  std::endl;
        exit(EXIT_FAILURE);
    }

    thRet = pthread_create(&threadId, NULL, func, (void*)(this));
    if(thRet != 0)
    {
        std::cout << "Thread  creation failed : " << threadNum << std::endl;
        exit(EXIT_FAILURE);
    }
}

void TaskThread::SemAssign(eSemOperation flag)
{
    if(flag == E_SEM_WAIT)
    {
    	sem_wait(&semAssign);
    }
    else if(flag == E_SEM_POST)
    {
    	sem_post(&semAssign);
    }
    else
    {
    	std::cout << "Not Valid sem operation " << std::endl;
    }
}

void TaskThread::UpdateStatus(eThreadStatus flag)
{
    if(flag == E_THREAD_IDLE)
    {
    	bThreadIdle = true;
    }
    else if(flag == E_THREAD_BUSY)
    {
    	bThreadIdle = false;
    }
    else
    {
        std::cout << "Not valid update status flag " << std::endl;
    }
}

void* func(void* arg)
{
	TaskThread* thread = reinterpret_cast<TaskThread*>(arg);
    while(1)
    {
    	thread->SemAssign(E_SEM_WAIT);
    	bool bthreadFuncExecuted = false;
        std::cout << "func " << thread->GetThreadNum() <<  std::endl;
        bthreadFuncExecuted = thread->ProcessTask();
        pthread_mutex_lock(&(ThreadPool::mutThreadQueue));
        if(bthreadFuncExecuted)
        {
        	thread->UpdateStatus(E_THREAD_IDLE);
        	thread->idleThreadQueue->push(thread);
        	pthread_cond_signal(&(ThreadPool::condThreadQueueWait));
        }
        pthread_mutex_unlock(&(ThreadPool::mutThreadQueue));
    }
}

