#ifndef __DLIST_H
#define __DLIST_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

//定义一个enum来存放函数的返回值，可以不定义
typedef enum _Ret
{
	RET_OK = 1,
	RET_FAULT,
	RET_OOM,
}Ret;

typedef struct _DList DList;


typedef Ret (*DListVisitFunc)(void* ctx, void* data);


//提供创建和销毁函数
DList *dlist_create ();
Ret dlist_add(DList *thiz, int index, void *data);
Ret dlist_delete(DList *thiz, int index);
Ret dlist_foreach(DList *thiz, DListVisitFunc visit, void* ctx);
Ret int_print(void* ctx, void *data);
Ret sum_cb(void* ctx, void *data);
Ret max_cb(void* ctx, void* data);
Ret str_toupper(void* ctx, void* data);
Ret str_print(void* ctx, void* data);

#define return_if_fail(p) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
		__func__, __LINE__); return;}
#define return_val_if_fail(p, ret) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n",\
	__func__, __LINE__); return (ret);}

#ifdef __cplusplus
}
#endif/*__cplusplus*/
	
#endif