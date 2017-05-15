#ifndef __DLIST_H
#define __DLIST_H

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



//提供创建和销毁函数
DList *dlist_create ();
Ret dlist_add(DList *thiz, int index, void *data);
Ret dlist_delete(DList *thiz, int index);
Ret dlist_print(DList *thiz, DListDataPrintFunc print);
Ret print_int(void * data);
#endif