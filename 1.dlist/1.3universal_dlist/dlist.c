/********************************
*Program Assignmert: 	实现通用双向链表
*Author:				JianxiangChan
*Date:					2017/5/13
*Description:					
*********************************/
/*********************************
*Source code in:
				sysCpractise\1.dlist\1.3universal
*Function List:	
*				dlist_create	实现一个Dlist的初始化
*						
*
**********************************/

#include <stdlib.h>
//在包含assert.h之前定义，可以使assert无效
#define NDEBUG
#include <assert.h>
#include "dlist.h"


//建立通用链表的存储结构
typedef struct _DListNode
{									
		void * data;
		
		struct _DListNode *pPrev;
		struct _DListNode *pNext;
}DListNode;

typedef struct _DList
{
	DListNode *head;
	DListNode *current;
}DList;

/**********************************
*Function Name:	dlist_create
*Purpose:				实现DList结构体的初始化
*Params:				空
*Return:				DList返回初始化的地址
*Limitation			返回NULL就说明初始化失败
**********************************/
DList *dlist_create ()
{
	DList *dlist = (DList *)calloc(1, sizeof(DList));
	assert(NULL == dlist);
	if(NULL == dlist)
	{
		return NULL;
	}
	dlist->head  = (DListNode *)calloc(1,sizeof(DListNode));
	if(NULL == dlist->head)
	{
		free(dlist);
		dlist = NULL;
		return NULL;
	}
	dlist->current = dlist->head;
	return dlist;
}

/**********************************
*Function Name:	data_dlist_check
*Purpose:				检查输入指针地址是否为空
*Params:				
*							@DList *  thiz	 添加节点的对象
							@void * 	data   添加的数据地址
*Return:				DList返回初始化的地址
*Limitation			返回1：说明地址不为空，返回0说明为空。
**********************************/
static int data_dlist_check(DList *thiz, void  *data)
{
	if((NULL == data) || (NULL == thiz))
	{
		return 0;
	}
	return 1;
}

/**********************************
*Function Name:	dlist_add
*Purpose:		给双向链表添加节点和数据
*Params:				
*				@DList *  thiz	 添加节点的对象
				@int	  index  :>= 0链表的位置 <0 链表尾部
				@void *   data   添加的数据地址
*Return:		Ret
*Limitation		返回RET_OK RET_FAULT RET_OOM
**********************************/
Ret dlist_add(DList *thiz, int index, void *data)
{
	DListNode *node =NULL;
	DListNode *dlistnode = NULL;
	
	//数据检查
	//return_val_if_fail((NULL != thiz) && (NULL != data), RET_FAULT); 
	if(! (data_dlist_check(thiz, data)))
	{
		return RET_FAULT;
	}
	
	node = (DListNode *)calloc(1, sizeof(DListNode));
	if(node == NULL)
	{
		return RET_OOM;
	}
	node->data = data;
	
	dlistnode = thiz->head;
	//找到index节点位置,或者找到链表尾部
	while((0 < index)&&(NULL != dlistnode->pNext) )
	{
		dlistnode = dlistnode->pNext;
		index--;
	}
	
	if((NULL == dlistnode->pNext) && (0 <  index))
	{
		//说明index已经跑到链表最大长度外面了
		printf("error:index beyond the MAX size of the list.\n");
		return RET_OOM;
	}
	else if((NULL != dlistnode->pNext) && (0 == index))
	{
		//中间节点
		node->pNext = dlistnode->pNext;
		node->pPrev = dlistnode;
		dlistnode->pNext->pPrev = node;
		dlistnode->pNext = node;
		return RET_OK;
	}
	else 
	{
		//尾部节点(只有头节点没有其他节点，也放在尾部节点里面)
		thiz->current->pNext = node;
		node->pPrev = thiz->current;
		thiz->current = node;
		return RET_OK;
	}
	return RET_FAULT;
} 

/**********************************
*Function Name:	dlist_delete
*Purpose:		给双向链表删除节点和数据
*Params:				
*				@DList *  thiz	 删除节点的对象
				@int	  index  >0链表的位置 
								 <0 链表尾部 
								 =0 删除整个链表
				@void *   data   添加的数据地址
*Return:		Ret
*Limitation		返回RET_OK RET_FAULT RET_OOM
**********************************/
Ret dlist_delete(DList *thiz, int index)
{
	DListNode *dlistnode = NULL;
	
	//数据检查
	//return_val_if_fail(NULL != thiz, RET_FAULT); 
	if(NULL == thiz)
	{
		return RET_FAULT;
	}
	
	dlistnode = thiz->head;
	
	if(0 == index)
	{
		//删除整个链表
		while(NULL == thiz->current->pPrev)
		{
			thiz->current = thiz->current->pPrev;
			thiz->current->pNext->pPrev = NULL;
			thiz->current->pNext->data = NULL;
			free(thiz->current->pNext);
			thiz->current->pNext = NULL;
		}
		free(thiz->current);
		free(thiz->head);
		thiz->current = NULL;
		thiz->head = NULL;
		free(thiz);
		thiz = NULL;
	}
	//找到index节点位置,或者找到链表尾部
	while((0 < index)&&(NULL != dlistnode->pNext))
	{
		dlistnode = dlistnode->pNext;
		index--;
	}
	
	if((NULL == dlistnode->pNext) && (0 <  index))
	{
		//说明index已经跑到链表最大长度外面了
		printf("error:index beyond the MAX size of the list.\n");
		return RET_OOM;
	}
	else if((NULL != dlistnode->pNext) && (0 == index))
	{
		//中间节点
		dlistnode->pPrev->pNext = dlistnode->pNext;
		dlistnode->pNext->pPrev = dlistnode->pPrev;
		dlistnode->data = NULL;
		dlistnode->pPrev = NULL;
		dlistnode->pNext = NULL;
		free(dlistnode);
		dlistnode = NULL;
		return RET_OK;
	}
	else 
	{
		//尾部节点(只有头节点没有其他节点，也放在尾部节点里面)\
		//这里dlistnode没有走到尾部，不能使用
		if(NULL != thiz->current->pPrev)
		{
			//说明不是头结点
			dlistnode = thiz->current;
			thiz->current = thiz->current->pPrev;
			thiz->current->pNext = NULL;
			dlistnode->pPrev = NULL;
			dlistnode->pNext = NULL;
			free(dlistnode);
			dlistnode = NULL;
			return RET_OK;

		}
		else
		{
			printf("error:no tail node to delete.\n");
			return RET_FAULT;
		}
	}
	return RET_FAULT;
}

/**********************************
*Function Name:	dlist_foreach
*Purpose:		对链表进行遍历，并进行各种操作
*Params:				
*					@DList*  thiz	 		  进行遍历的对象
					@DListVisitFunc visit 对应的操作函数
					@voide* ctx      		  操作函数的上下文
*Return:		Ret
*Limitation		返回RET_OK RET_FAULT RET_OOM
**********************************/
Ret dlist_foreach(DList *thiz, DListVisitFunc visit, void* ctx)
{
	DListNode* iter = thiz->head;
	while(NULL != iter)
	{
		visit(ctx, iter->data);
		iter = iter->pNext;
	}
	return RET_OK;
}

/**********************************
*Function Name:	sum_cb
							print_int
							max_cb
							str_toupper
*Purpose:		求和函数
*Params:				
*					@void*  ctx	 		  操作对象
					@void*  data      	  操作函数的数据
*Return:		Ret
*Limitation		返回RET_OK RET_FAULT RET_OOM
**********************************/

//链表求和
Ret sum_cb(void* ctx, void *data)
{
	long long * result = ctx;
	*result += (int)data;
	return RET_OK;
}

//整形打印链表
Ret int_print(void* ctx, void *data)
{
	printf("%d\n", (int)data);
	return RET_OK;
}

//求链表最大值
Ret max_cb(void* ctx, void* data)
{
	int * result = ctx;
	if((int)data > *result)
	{
		*result = (int)data;
	}
}
 
 //字符串大小写转换
Ret str_toupper(void* ctx, void* data)
{
	//头结点的data为0 所以第一次进来先判断 让其第一次不执行
	if(NULL == data)
	{
		return RET_OK;
	}
	while('\0' != *(char*)data)
	{
		*(char *)data = toupper(*(char *)data);
		(char*)data ++;
	}
}

//打印链表字符串
Ret str_print(void* ctx, void* data)
{
	if(NULL == data)
	{
		return RET_OK;
	}
	while('\0' != *(char*)data)
	{
		printf("%c",*(char*)data);
		(char*)data ++;
	}
	printf("\n");
}
