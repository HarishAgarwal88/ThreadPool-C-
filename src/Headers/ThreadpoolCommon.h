/*
 * ThreadpoolCommon.h
 *
 *  Created on: 22-Nov-2015
 *      Author: harry
 */

#ifndef THREADPOOLCOMMON_H_
#define THREADPOOLCOMMON_H_

enum eSemOperation {
E_SEM_WAIT = 0,
E_SEM_POST = 1
};

enum eThreadStatus {
E_THREAD_IDLE = 0,
E_THREAD_BUSY = 1
};

#endif /* THREADPOOLCOMMON_H_ */
