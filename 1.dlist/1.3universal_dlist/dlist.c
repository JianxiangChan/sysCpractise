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

#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

#define return_val_if_fail(p, val) /
    if(!(p)) {printf("%s:%d"#p" failed./n", __func__, __LINE__); return val;}
	
//建立通用链表的存储结构
typedef struct _DListNode
{									
		void * data;
		Node *pPrev;
		Node *pNext;
}DListNode;

typedef struct _DList
{
	DListNode *head;
	DListNode *current;
}DList;

//定义一个enum来存放函数的返回值，可以不定义
typedef enum _Ret
{
	RET_OK = 1,
	RET_FAULT,
	RET_OOM,
}Ret;

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
	if(NULL == DList)
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
int data_dlist_check(DList *thiz, void  *data)
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
	return_val_if_fail((NULL != thiz) && (NULL != data), RET_FAULT); 
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
		return RET_OK
	}
	else 
	{
		//尾部节点(只有头节点没有其他节点，也放在尾部节点里面)
		thiz->current->pNext = node;
		node->pPrev = thiz->current;
		thiz->current = node;
		return RET_OK
	}
	return RET_FAULT
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
	return_val_if_fail(NULL != thiz, RET_FAULT); 
	if(! (data_dlist_check(thiz, 1)))
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
		return RET_OK
	}
	else 
	{
		//尾部节点(只有头节点没有其他节点，也放在尾部节点里面)
		if(NULL != thiz->current->pPrev)
		{
			//说明不是头结点
			thiz->current = dlistnode->pPrev;
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
	return RET_FAULT
}




/**********************************
*Function Name:	dlist_display
*Purpose:		显示链表内容
*Params:				
*				@DList *  thiz	 显示链表的对象
				@int	  index  <0 链表的位置 
								 <0 链表尾部 
								 =0 删除整个链表
				@void *   data   添加的数据地址
*Return:		Ret
*Limitation		返回RET_OK RET_FAULT RET_OOM
**********************************/





/* static Node * note_list_all(Node *thiz)
{
	
	Node *p = thiz;
	if(NULL == p)
	{
		return NULL;
	}
	printf("--------------begin-------------\n");
	while(NULL != p->pNext)
	{
		p = p->pNext;
		printf("_Node data: %d.\n", p->data);
	}
	printf("--------------end-------------\n");
	return p;
}

//逆向遍历
static void note_list_all_reverse(Node *pTail)
{
	Node *p = pTail;
	printf("--------------begin-------------\n");
	while( NULL != p->pPrev)
	{
		printf("_Node data: %d.\n", p->data);
		p = p->pPrev;
	}
	printf("--------------end-------------\n");
}

char note_list(Node *thiz, int index)
{
	Node *p = thiz;
	if(-1 > index)
	{
		printf("error: illegal input");
		return -1;
	}
	switch (index){
	case -1:
		while(NULL != p->pNext)
		{
			p = p->pNext;
			//printf("_Node data: %d.\n", p->data);
		}
		note_list_all_reverse(p);
		break;
	case 0:
		note_list_all(p);
		break;
	default:
		while((index--) && (0 != (p->pNext)))
		{
			p = p->pNext;
		}
		if(0 != (index+1))
		{
			printf("error: index is beyond the MAX size of the list\n");
			return -1;
		}
		else
		{
			printf("node data of the index is %d.\n",p->data);
		}
	
	}
	return 0;
	
} */



