/********************************
*Program Assignmert: 		实现通用双向链表
*Author:							JianxiangChan
*Date:								2017/5/13
*Description:					
*********************************/
/*********************************
*Source code in:
					sysCpractise\1.dlist\1.3universal
*Function List:	
*						dlist_create	实现一个Dlist的初始化
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
*Function Name:	dlist_len
*Purpose:				查看链表的长度
*Params:				
*							@DList *  thiz	 插座链表的对象
*Return:				int 返回链表的长度值
*Limitation			
**********************************/
int dlist_len(DList *thiz)
{
	return_val_if_fail(thiz != NULL,RET_FAULT);
	int len = 0;
	DListNode *dlistnode = NULL;
	dlistnode = thiz->head;
	while(dlistnode->head != NULL)
	{
		dlistnode = dlistnode->next;
		len = len + 1;
	}
	return len;
}

/**********************************
*Function Name:	dlist_add
*Purpose:				给双向链表添加节点和数据
*Params:				
*							@DList *  thiz	 添加节点的对象
							@int			index 添加节点的位置
							@void * 	data   添加的数据地址
*Return:				Ret
*Limitation			返回RET_OK RET_FAULT RET_OOM
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
	
	dlistnode = thiz;
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

Ret dlist_delete(DList *thiz, int index)
{
	DListNode *dlistnode = NULL;
	
	//数据检查
	return_val_if_fail(NULL != thiz, RET_FAULT); 
	if(! (data_dlist_check(thiz, 1)))
	{
		return RET_FAULT;
	}
	
	dlistnode = thiz;
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
		thiz->current
		return RET_OK
	}
	return RET_FAULT
}


/*
//函数体之间使用空格
//双向链表尾部插入
static void node_insert_tail (Node *thiz, Node *new) //第一个参数为对象，并用thiz命名
{
	//第一步：找到链表的尾节点
	Node *p = thiz;
	while (NULL != p->pNext)
	{
		p -> pNext;
	}
	
	//第二步：将新的节点插入到原来尾部节点的后面
	p->pNext = new;
	new->pPrev = p;
}

//双向链表头部插入
static void note_insert_head_middle(Node *thiz, Node *new)
{
	new->pNext = thiz->pNext;								//新节点的next指针指向原来的节点1的地址
	//只有表头节点不能让第一个节点指向新节点，这样会导致内存错误
	if(NULL != thiz->pNext)		
		thiz->pNext->pPrev = new;
	thiz->pNext = new;
	new->pPrev = thiz;
	
}

 //双向链表中间插入
void insert_middle(struct node *thiz, struct node *new)
{
	struct node *p  = thiz;
	struct node *temp = thiz->pNext;
	p->pNext = new;
	new->pPrev = p;
	new->pNext = temp;
	temp->pPrev = new;
} 

//插入双向链表中的任意一个节点
//合理使用空格 参数之间用空格 
char note_insert_all(Node *thiz, Node *new, int index)
{
	//等号之间用空格
	Node *p = thiz;
	if(0 > index)
	{	
					//语句末的分号和前面内容不要加空格
		printf("error: illegal input of index.\n");
		return 0;
	}
	
	//第一步，找到index节点
	
		//用括号分隔表达式，不要靠默认优先级来判断
		while((index --) && (NULL != p->pNext))
		{
			//括号分隔if/while/for等语句的代码块，哪怕只有一行
			p = p->pNext;
		}
		//用tab缩进，如果代码层次过多（超过三层），说明可能代码设计上出了问题
		if((NULL == p->pNext) && (0 != (index+1)))
		{
			printf("error:index beyond the MAX size of the list.\n");
			return 0;
		}
		else if((NULL != p->pNext) && (0 == (index+1)))
		{
			note_insert_head_middle(p,new);
		}
		else
		{
			node_insert_tail(p,new);
		}

	return 1;
}

//正向遍历
static Node * note_list_all(Node *thiz)
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
	
}

char note_delete(Node *thiz, int data)
{
	Node *p = thiz;
	if(NULL == p)
	return -1;

	while(NULL != p->pNext)
	{
		p = p->pNext;
		if(p->data == data)
		{
			if(NULL == p->pNext)
			{
				p->pPrev->pNext = NULL;
			}
			else
			{
				p->pPrev->pNext = p->pNext;
				p->pNext->pPrev = p->pPrev;
			}
			free(p);
			return 0;
		}
	}
	printf("未找到要删除的节点.\n");
	return -1;
}
*/

