#include "rw_locker.h"
#include <stdlib.h>
#include <assert.h>

typedef enum _RwLokcerMode
{
	RW_LOCKER_NONE,
	RW_LOCKER_WR,
	RW_LOCKER_RD,
	RW_LOCKER_NR
}RwLockerMode;

struct _RwLocker{
	int readers;
	RwLockerMode mode;
	Locker* rw_locker;
	Locker* rd_locker;
};

RwLocker* rw_locker_create(Locker* rw_locker, Locker* rd_locker)
{
	RwLocker* thiz = NULL;
	return_val_if_fail(rw_locker != NULL && rd_locker != NULL, NULL);
	
	thiz = (RwLocker*)malloc(sizeof(RwLocker));
	if(thiz != NULL)
	{
		thiz->readers = 0;
		thiz->mode = RW_LOCKER_NONE;
		thiz->rw_locker = rw_locker;
		thiz->rd_locker = rd_locker;
	}
	
	return thiz;
}

Ret rw_locker_wrlock(RwLocker* thiz)
{
	Ret ret = RET_OK;
	return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);
	
	if((ret = locker_lock(thiz->rw_locker)) == RET_OK)
	{
		thiz->mode = RW_LOCKER_WR;
	}
	
	return ret;
}

Ret rw_lock_rdlock(RwLocker* thiz)
{
	Ret ret = RET_OK;
	return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);
	
	if(ret = locker_lock(thiz->rd_locker) == RET_OK)
	{
		thiz->readers++;
		if(thiz->readers == 1)
		{
			ret = locker_lock(thiz->rw_locker);
			thiz->mode = RW_LOCKER_RD;
		}
		locker_unlock(thiz->rd_locker);
	}
	
	return ret;
}

Ret rw_locker_unlock(RwLocker* thiz)
{
	Ret ret = RET_OK;
	return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);
	
	if(thiz->mode == RW_LOCKER_WR)
	{
		thiz->mode = RW_LOCKER_NONE;
		ret = locker_unlock(thiz->rw_locker);
	}
	else
	{
		assert(thiz->mode == RW_LOCKER_RD);
		if((ret = locker_lock(thiz->rd_locker)) == RET_OK);
		{
			thiz->readers--;
			if(thiz->readers == 0)
			{
				thiz->mode = RW_LOCKER_NONE;
				ret = locker_unlock(thiz->rw_locker);
			}
			locker_unlock(thiz->rd_locker);
		}
	}
	return ret;
}
