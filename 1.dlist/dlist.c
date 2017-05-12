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

struct node *creat_node (int data)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if(NULL == P)
	{
		printf("malloc error.\n");
		return NULL;
	}
	P->data  = data;
	P->pPrev = NULL;
	P->pNext = NULL;
	return p;
}


int main (void)
{
	struct node *pHeader = creat_node(0);
	
	
}
