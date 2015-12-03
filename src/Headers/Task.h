/*
 * Task.h
 *
 *  Created on: 22-Nov-2015
 *      Author: harry
 */

#ifndef TASK_H_
#define TASK_H_

class Task
{
public:
   virtual bool ExecuteTask() = 0;
   virtual ~Task(){};
};

#endif /* TASK_H_ */
