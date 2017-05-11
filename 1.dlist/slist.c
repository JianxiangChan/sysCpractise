#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "string.h" 
//定义一个链表结构体
struct node 
{
	int data;
	struct node *pNext;
};

//创建一个节点并且初始化
struct node * creat_node(int data)
{
	struct node *p =(struct node *)malloc(sizeof(struct node));
	if(NULL == p)
	{
		printf("malloc error.\n");
	}
	bzero(p,sizeof(struct node));
	p->data =data;
	p->pNext = NULL; 
	return p;
}

void insert_tail(struct node *pH,struct node *new)
{
	//查找最后一个指针
	struct node *p = pH;
	while (NULL != p->pNext)
	{
		p = p->pNext;
	}
	//插入指针	
	p->pNext = new;
} 

void insert_head(struct node *pH,struct node *new)
{
	new->pNext = pH->pNext;
	pH->pNext = new;
}

void list_for_each(struct node* pH)
{
	struct node *p =pH;
	printf("--------------begin-------------\n");
	while(NULL != p->pNext)
	{
		p = p->pNext;
		printf("node data: %d.\n",p->data);
	}
	printf("--------------end-------------\n");
}

int delete_node(struct node *pH, int data)
{
	struct node *p =pH;				//用来指向当前节点
	struct node *pPrev = NULL;		//用来指向当前节点的前一个节点
	while(NULL != p->pNext)			//遍历，走到尾节点处推出循环
	{
		pPrev = p;					//跟随p移动，指向p的前一个节点
		p = p->pNext;				//走到下一个节点，也就是循环变量
		if(p->data == data)			//找到了要删除的节点
		{							
			if(NULL == p->pNext)	//尾节点
		                       	{					
				pPrev->pNext = NULL;//删除尾节点
				free(p);			//释放摘除的节点内存
			}
			else
			{
				pPrev->pNext = p->pNext;
				free(p);
			}
			return 0;				//删除成功
		}
	}
	printf("没找到需要删除的节点\n");
	return -1;
}

void reverse_list(struct node *pH)
{
	struct node *p =pH->pNext; 			//p指向第一个有效节点
	struct node *pBack;					//保存当前节点的后一个节点地址
	//当链表没有有效节点的话或者只有一个有效节点，逆序不用做任何操作
	if( (NULL ==p) || (NULL == p->pNext) )
	return;
	while(NULL != p->pNext)
	{
		pBack = p->pNext;
		if(p == pH->pNext)
		{
			p->pNext = NULL;
		}
		else
		{
			p->pNext = pH->pNext;
		}
		pH->pNext = p;
		p = pBack;
	
	}
	insert_head(pH,p);
	//return p;
}

int main (void)
{
	struct node *pHeader =creat_node(0);
	insert_head(pHeader,creat_node(4));
	insert_tail(pHeader,creat_node(1));
	insert_tail(pHeader,creat_node(2));
	insert_tail(pHeader,creat_node(3));
	list_for_each(pHeader);
	delete_node(pHeader,4);
	list_for_each(pHeader);
	reverse_list(pHeader);
	list_for_each(pHeader);
	/* printf("node1 data: %d.\n",pHeader->pNext->data);
	printf("node2 data: %d.\n",pHeader->pNext->pNext->data);
	printf("node3 data: %d.\n",pHeader->pNext->pNext->pNext->data);
	printf("node4 data: %d.\n",pHeader->pNext->pNext->pNext->pNext->data); */
	return 0;
}

