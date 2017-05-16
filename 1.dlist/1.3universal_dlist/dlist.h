#ifndef __DLIST_H
#define __DLIST_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
//typedef enum _Ret Ret;
//定义一个enum来存放函数的返回值，可以不定义
typedef enum _Ret
{
	RET_OK = 1,
	RET_FAULT,
	RET_OOM,
}Ret;

typedef struct _DList DList;
typedef Ret (*DListDataPrintFunc)(void* data);
typedef Ret (*DListVisitFunc)(void* ctx, void* data);


//提供创建和销毁函数
DList *dlist_create ();
Ret dlist_add(DList *thiz, int index, void *data);
Ret dlist_delete(DList *thiz, int index);
//Ret dlist_print(DList *thiz, DListDataPrintFunc print);
//Ret print_int(void * data);
Ret dlist_foreach(DList *thiz, DListVisitFunc visit, void* ctx);
Ret int_print(void* ctx, void *data);
Ret sum_cb(void* ctx, void *data);
Ret max_cb(void* ctx, void* data);
Ret str_toupper(void* ctx, void* data);
Ret str_print(void* ctx, void* data);

#endif