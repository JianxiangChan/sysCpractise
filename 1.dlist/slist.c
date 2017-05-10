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
	struct node *p =pH;	//用来指向当前节点
	struct node *pPREV = NULL;	//用来指向当前节点的前一个节点
	while(NULL != p->pNext)		//遍历，走到尾节点处推出循环
	{
		prev = p;
		p = p->pNext;
		if(p->)
	}
}


int main (void)
{	
	struct node *pHeader =creat_node(0);
	insert_tail(pHeader,creat_node(1));
	insert_tail(pHeader,creat_node(2));
	insert_tail(pHeader,creat_node(3));
	insert_head(pHeader,creat_node(4));
	//printf("node1 data: %d.\n",pHeader->data);
	
	printf("node1 data: %d.\n",pHeader->pNext->data);
	printf("node2 data: %d.\n",pHeader->pNext->pNext->data);
	printf("node3 data: %d.\n",pHeader->pNext->pNext->pNext->data);
	printf("node4 data: %d.\n",pHeader->pNext->pNext->pNext->pNext->data);
	list_for_each(pHeader);
	return 0;
}

