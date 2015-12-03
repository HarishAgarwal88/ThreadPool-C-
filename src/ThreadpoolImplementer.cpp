/*
 * ThreadpoolImplementer.cpp
 *
 *  Created on: 22-Nov-2015
 *      Author: harry
 */

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

class MyTask : public Task
{
private:
    int taskNum;
public:
    MyTask(int n = 0) : taskNum (n) {}
    ~MyTask(){}
    bool ExecuteTask()
    {
		std::cout << "TASK EXECUTED : " << taskNum << std::endl;
		usleep(taskNum*1000000);
		return true;
    }
};

int main()
{
    Task *t1 = new MyTask(4);
    Task *t2 = new MyTask(3);
    Task *t3 = new MyTask(1);
    Task *t4 = new MyTask(2);
    Task *t5 = new MyTask(6);
    Task *t6 = new MyTask(7);
    Task *t7 = new MyTask(8);
    Task *t8 = new MyTask(1);
    Task *t9 = new MyTask(2);
    Task *t10 = new MyTask(5);
    Task *t11 = new MyTask(0);

    ThreadPool *pool = new ThreadPool;
    pool->ProcessTask(t1);
    pool->ProcessTask(t2);
    pool->ProcessTask(t3);
    pool->ProcessTask(t4);
    pool->ProcessTask(t5);
    pool->ProcessTask(t6);
    pool->ProcessTask(t7);
    pool->ProcessTask(t8);
    pool->ProcessTask(t9);

    pool->JoinThread(0);
    std::cout << "Main exit " << std::endl;
}


