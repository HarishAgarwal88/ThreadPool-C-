//============================================================================
// Name        : Threadpool.cpp
// Author      : Harish Agarwal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <map>
#include <stdlib.h>
#include <unistd.h>
#include "Headers/ThreadpoolCommon.h"
#include "Headers/Task.h"
#include "Headers/TaskThread.h"
#include "Headers/Threadpool.h"

void* func(void* arg);
void* AssignTask(void* arg);
pthread_cond_t ThreadPool::condThreadQueueWait; //APPROACH 2
pthread_mutex_t ThreadPool::mutThreadQueue; //APPROACH 2

ThreadPool::ThreadPool(int n)
{
    threads = new TaskThread [n];
    for(int i = 0; i < n; i++)
    {
    	idleThreadsQueue.push(&threads[i]);
    }
    for(int i = 0; i < n; i++)
    {
    	threads[i].SetIdleThreadQueue(&idleThreadsQueue);
    }

    int thRet = 0;

    thRet = pthread_mutex_init(&mutJob, NULL);
    if(thRet != 0)
    {
        std::cout << "Mutex Init Fail" << std::endl;
        exit(EXIT_FAILURE);
    }

    thRet = sem_init(&semJob, 0, 0);
    if(thRet != 0)
    {
        std::cout << "Sem Init Fail" << std::endl;
        exit(EXIT_FAILURE);
    }

//APPROACH 2 start
    thRet = pthread_mutex_init(&(ThreadPool::mutThreadQueue), NULL);
    if(thRet != 0)
    {
        std::cout << "Thread Queue Mutex Init Fail" << std::endl;
        exit(EXIT_FAILURE);
    }

    thRet = pthread_cond_init(&(ThreadPool::condThreadQueueWait), NULL);
    if(thRet != 0)
    {
        std::cout << "Conditional Var Thread Queue  Init Fail" << std::endl;
        exit(EXIT_FAILURE);
    }
//APPROACH 2 End
    thRet = pthread_create(&thAssign, NULL, AssignTask,(void*)(this));
    if(thRet != 0)
    {
        std::cout << "Assign Task Thread create Fail" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ThreadPool::ProcessTask(Task* t1)
{
    pthread_mutex_lock(&mutJob);
    std::cout << "Processing" << std::endl;
    tasks.push(t1);
    sem_post(&semJob);
    pthread_mutex_unlock(&mutJob);
}

void ThreadPool::JoinThread(int threadNum)
{
    void* result;
    pthread_join(threads[threadNum].GetThreadId(), &result);
}

void* AssignTask(void* arg)
{
    bool bJobAsnd;
    ThreadPool *pool = reinterpret_cast<ThreadPool*>(arg);
    while(1)
    {
    	sem_wait(&(pool->semJob));
    	pthread_mutex_lock(&(ThreadPool::mutThreadQueue));
    	if(!((pool->idleThreadsQueue).empty()))
    	{
    		//pthread_mutex_unlock(&(ThreadPool::mutThreadQueue));
			pthread_mutex_lock(&(pool->mutJob));
			((pool->idleThreadsQueue).front())-> AssignTask((pool->tasks).front());
			(pool->tasks).pop();
			(pool->idleThreadsQueue).pop();
			pthread_mutex_unlock(&(pool->mutJob));
			pthread_mutex_unlock(&(ThreadPool::mutThreadQueue));

    	}
    	else
    	{
			pthread_cond_wait(&(ThreadPool::condThreadQueueWait), &(ThreadPool::mutThreadQueue));
			pthread_mutex_unlock(&(ThreadPool::mutThreadQueue));

			pthread_mutex_lock(&(pool->mutJob));
			((pool->idleThreadsQueue).front())-> AssignTask((pool->tasks).front());
			(pool->tasks).pop();
			(pool->idleThreadsQueue).pop();
			pthread_mutex_unlock(&(pool->mutJob));
    	}
    }
}

