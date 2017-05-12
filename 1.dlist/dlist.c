#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
//C语言双链表的实现
//构建一个双链表节点类型
struct node
{
		int data;
		struct node *pPrev;
		struct node *pNext;
};

//创建一个双向链表
struct node *creat_node (int data)
{

	struct node *p = (struct node *)malloc(sizeof(struct node));
	if(NULL == p)
	{
		printf("malloc error.\n");
		return NULL;
	}
	p->data  = data;
	p->pPrev = NULL;
	p->pNext = NULL;
	return p;
}

//双向链表尾部插入
void insert_tail (struct node *pH,struct node *new)
{
	//第一步：找到链表的尾节点
	struct node *p = pH;
	while (NULL != p->pNext)
	{
		p -> pNext;
	}
	
	//第二步：将新的节点插入到原来尾部节点的后面
	p->pNext = new;
	new->pPrev = p;
}

//双向链表头部插入
void insert_head_middle(struct node *pH,struct node *new)
{
	new->pNext = pH->pNext;								//新节点的next指针指向原来的节点1的地址
	//只有表头节点不能让第一个节点指向新节点，这样会导致内存错误
	if(NULL != pH->pNext)		
		pH->pNext->pPrev = new;
	pH->pNext = new;
	new->pPrev = pH;
	
}
/* //双向链表中间插入
void insert_middle(struct node *pH,struct node *new)
{
	struct node *p  = pH;
	struct node *temp = pH->pNext;
	p->pNext = new;
	new->pPrev = p;
	new->pNext = temp;
	temp->pPrev = new;
} */
//插入双向链表中的任意一个节点
char insert_all(struct node *pH,struct node *new,int index)
{
	struct node *p  = pH;
	if(0 > index)
	{
		printf("error: illegal input of index.\n");
		return 0;
	}
	
	//第一步，找到index节点
	//if(0 != index)
	//{
		while( (index --)&&(NULL != p->pNext) )
		{
			p=p->pNext;
		}
		
		if( (NULL == p->pNext)&&( 0 != (index+1) ) )
		{
			printf("error:index beyond the MAX size of the list.\n");
			return 0;
		}
		else if((NULL != p->pNext)&&( 0 == (index+1) ))
		{
			insert_head_middle(p,new);
		}
		else
		{
			insert_tail(p,new);
		}
	//}
/* 	else
	{
		insert_head(p,new);
	} */
	return 1;
}
//正向遍历
struct node * list_for_each(struct node *pH)
{
	
	struct node *p =pH;
	if(NULL == p)
	{
		return NULL;
	}
	printf("--------------begin-------------\n");
	while(NULL != p->pNext)
	{
		p = p->pNext;
		printf("node data: %d.\n",p->data);
	}
	printf("--------------end-------------\n");
	return p;
}

//逆向遍历
void list_for_each_reverse(struct node *pTail)
{
	struct node *p = pTail;
	printf("--------------begin-------------\n");
	while( NULL != p->pPrev)
	{
		printf("node data: %d.\n",p->data);
		p = p->pPrev;
	}
	printf("--------------end-------------\n");
}

char delete_node(struct node *pH,int data)
{
	struct node *p = pH;
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
int main (void)
{
	struct node *pHeader = creat_node(0);
	insert_all(pHeader,creat_node(1),0);
	insert_all(pHeader,creat_node(2),1);
	insert_all(pHeader,creat_node(3),2);
	insert_all(pHeader,creat_node(4),3);
	insert_all(pHeader,creat_node(5),2);
	insert_all(pHeader,creat_node(6),0);

	printf("正向遍历： \n");
	struct node *pTail = list_for_each(pHeader);
	printf("逆向遍历： \n");
	list_for_each_reverse(pTail);
	delete_node(pHeader,1);
	printf("正向遍历： \n");
	list_for_each(pHeader);
	return 0;
}
