#include "locker.h"

#ifndef LOCKE_NEST__H
#define LOCKE_NEST__H

DECLS_BEGIN


typedef int (*TaskSelfFunc)(void); //因为这个是平台相关的，所以用一个回调函数抽象它
Locker* locker_nest_creat(Locker* real_locker, TaskSelfFunc task_self);

DECLS_END


#endif