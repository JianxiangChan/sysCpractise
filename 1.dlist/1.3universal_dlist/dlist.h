#ifndef __DLIST_H
#define __DLIST_H

//typedef enum _Ret Ret;
//����һ��enum����ź����ķ���ֵ�����Բ�����
typedef enum _Ret
{
	RET_OK = 1,
	RET_FAULT,
	RET_OOM,
}Ret;

typedef struct _DList DList;
typedef Ret (*DListDataPrintFunc)(void* data);



//�ṩ���������ٺ���
DList *dlist_create ();
Ret dlist_add(DList *thiz, int index, void *data);
Ret dlist_delete(DList *thiz, int index);
Ret dlist_print(DList *thiz, DListDataPrintFunc print);
Ret print_int(void * data);
#endif