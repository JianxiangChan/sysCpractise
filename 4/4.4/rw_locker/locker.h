#include "typedef.h"

#ifndef LOCKER_H
#define LOCKER_H

DECLS_BEGIN

struct _Locker;
typedef struct _Locker Locker;
typedef Ret (*LockerLockFunc)(Locker* thiz);
typedef Ret (*LockerUnlockFunc)(Locker* thiz);
typedef void (*LockerDestroyFucn)(Locker* thiz);

struct _Locker
{
	//1.足够抽象，不依赖任何具体的实现
	//2.只能通过具体的实现来创建，但是需要有自己的销毁函数
	
	LockerLockFunc lock;
	LockerUnlockFunc unlock;
	LockerDestroyFucn destroy;
	//这样只需要一次分配内存，且能够分配刚好够用的长度。
	//因为这种定义方法，分配到内存是连续的，所以只需要一次分配，也只需要一次释放
	char priv[0];
};

static inline Ret locker_lock(Locker* thiz)
{
	return_val_if_fail(thiz != NULL && thiz->lock != NULL, RET_INVALID_PARAMS);
	
	return thiz->lock(thiz);
}

static inline Ret locker_unlock(Locker* thiz)
{
	return_val_if_fail(thiz != NULL && thiz->unlock != NULL, RET_INVALID_PARAMS);
	return thiz->unlock(thiz);
}

static inline void locker_destroy(Locker* thiz)
{
	return_if_fail(thiz != NULL && thiz->destroy != NULL)
	thiz->destroy(thiz);
}

DECLS_END

#endif/* locker.h*/