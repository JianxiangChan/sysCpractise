#include "typedef.h"
#include <stdlib.h>

typedef struct _FifoRing
{
	int r_cursor;
	int w_cursor;
	size_t length;
	void* data[0];
}FifoRing;

FifoRing* fifo_ring_create(size_t length)
{
	FifoRing* thiz = NULL;
	return_val_if_fail(length > 1, NULL);
	
	thiz = (FifoRing*)malloc(sizeof(FifoRing*) + length*sizeof(void*));
	
	if(thiz != NULL)
	{
		thiz->r_cursor = 0;
		thiz->w_cursor = 0;
		thiz->length = length;
	}
	
	return thiz;
}


Ret fifo_ring_push(FifoRing* thiz, void* data)
{
	int w_cursor = 0;
	Ret ret = RET_FAIL;
	return_val_if_fail(thiz != NULL, RET_FAIL);
	
	w_cursor = (thiz->w_cursor +1)%thiz->length;
	
	//边界判断
	if(w_cursor != thiz->r_cursor)
	{
		thiz->data[thiz->w_cursor] = data;
		thiz->w_cursor = w_cursor;
		
		ret = RET_OK;
	}
	
	return ret;
}

Ret fifo_ring_pop(FifoRing* thiz, void** data)
{
	Ret ret = RET_FAIL;
	return_val_if_fail(thiz != NULL && data != NULL , RET_FAIL);
	
	if(thiz->r_cursor != thiz->w_cursor)
	{
		*data = thiz->data[thiz->r_cursor];
		thiz->r_cursor = (thiz->r_cursor + 1)%thiz->length;
		
		ret = RET_OK;
	}
	
	return ret;
}

void fifo_ring_destroy(FifoRing* thiz)
{
	SAFE_FREE(thiz);
}

#ifdef FIFO_RING_TEST

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //包含了许多UNIX系统服务的函数原型
#include <assert.h>

#define NR 10000
static void* thread_push(void* param)
{
	int i = 0;
	FifoRing* fifo = (FifoRing*)param;
	
	while(i < NR)
	{
		if(fifo_ring_push(fifo, (void*)i) == RET_OK)
		{
			i ++;
		}
		else
		{
			usleep(10);
		}
		
		return NULL;
	}

}

static void* thread_pop(void* param)
{
	int i = 0;
	void* data = 0;
	
	FifoRing* fifo = (FifoRing*)param;
	
	while(i < NR)
	{
		if(fifo_ring_pop(fifo, (void **)&data) == RET_OK)
		{
			assert(i == (int)data);
			i ++;
		}
		else
		{
			usleep(10);
		}
	}
	
	return NULL;
}

void push_pop_test(size_t fifo_length)
{
	pthread_t push_tid = 0;
	pthread_t pop_tid = 0;
	FifoRing* fifo = fifo_ring_create(fifo_length);
	pthread_create(&push_tid, NULL, thread_push, fifo);
	pthread_create(&pop_tid, NULL, thread_pop, fifo);
	pthread_join(push_tid, NULL);
	pthread_join(pop_tid, NULL);
	
	fifo_ring_destroy(fifo);
	
	return;
}

int main(int argc, char* argv[])
{
	
	push_pop_test(2);
	
	push_pop_test(20);
	push_pop_test(200);
	
	push_pop_test(2000);
	
}

#endif











