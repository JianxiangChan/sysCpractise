#include "locker.h"

#ifndef RW_LOCKER_H
#define RW_LOCKER_H



struct _RwLocker;
typedef struct _RwLocker RwLocker;

Ret rw_locker_wrlock(RwLocker* thiz);
Ret rw_locker_rdlock(RwLocker* thiz);

Ret rw_locker_unlock(RwLocker* thiz);
void rw_locker_destory(RwLocker* thiz);


#endif