#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "string.h" 
//定义一个链表结构体
struct Node 	//结构体、枚举和联合名 首字母大写，多个单词下划线分隔
{
	int data;
	struct Node *pNext;
};

//创建一个节点并且初始化
struct Node * creat_node(int data)
{
	struct Node *p =(struct Node *)malloc(sizeof(struct Node));
	if(NULL == p)
	{
		printf("malloc error.\n");
	}
	bzero(p,sizeof(struct Node));
	p->data =data;
	p->pNext = NULL; 
	return p;
}

void insert_tail(struct Node *pH,struct Node *new)
{
	//查找最后一个指针
	struct Node *p = pH;
	while (NULL != p->pNext)
	{
		p = p->pNext;
	}
	//插入指针	
	p->pNext = new;
} 

void insert_head_middle(struct Node *pH,struct Node *new)
{
	new->pNext = pH->pNext;
	pH->pNext = new;
}
//在链表中间第index节点后插入一个节点
//index 大于等于 0
char insert_all(struct Node *pH,struct Node *new,int index)
{
	struct Node *p = pH;
	//用于存储index节点后面一个节点的地址
	struct Node *pBack;
	if(0 > index)
	{
		printf("error:illegal input of index\n");
		return 0;
	}
	//第一步，找到index节点
	if(0 != index)
	{
		while( (index --)&&(NULL != p->pNext) )
		{
			p=p->pNext;
		}
		pBack = p->pNext;
		if( (NULL == p->pNext)&&( 0 != (index+1) ) )
		{
			printf("error:index beyond the MAX size of the list.\n");
			return 0;
		}
		else if((NULL != p->pNext)&&( 0 == (index+1) ))
		{
/* 			//printf("i am here1\n");
			pBack = p->pNext;
			//index节点指向新节点
			p->pNext = new;
			//新节点指向index+1
			new->pNext = pBack; */
			insert_head_middle(p,new);
		}
		else
		{
			insert_tail(p,new);
		}
	}
/* 	else
	{
		insert_head(p,new);
	} */
	return 1;
	
}


int delete_Node(struct Node *pH, int data)
{
	struct Node *p =pH;				//用来指向当前节点
	struct Node *pPrev = NULL;		//用来指向当前节点的前一个节点
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

void list_for_each(struct Node* pH)
{
	struct Node *p =pH;
	printf("--------------begin-------------\n");
	while(NULL != p->pNext)
	{
		p = p->pNext;
		printf("Node data: %d.\n",p->data);
	}
	printf("--------------end-------------\n");
}

void reverse_list(struct Node *pH)
{
	struct Node *p =pH->pNext; 			//p指向第一个有效节点
	struct Node *pBack;					//保存当前节点的后一个节点地址
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
	insert_head_middle(pH,p);
	//return p;
}

int main (void)
{
	struct Node *pHeader =creat_node(0);
 	insert_head_middle(pHeader,creat_node(4));
	insert_tail(pHeader,creat_node(1));
	insert_tail(pHeader,creat_node(2));
	insert_tail(pHeader,creat_node(3)); 
	list_for_each(pHeader);
	delete_Node(pHeader,4);
	list_for_each(pHeader);
	reverse_list(pHeader);
	list_for_each(pHeader);
	insert_all(pHeader,creat_node(5),0);
	list_for_each(pHeader);
	/* printf("Node1 data: %d.\n",pHeader->pNext->data);
	printf("Node2 data: %d.\n",pHeader->pNext->pNext->data);
	printf("Node3 data: %d.\n",pHeader->pNext->pNext->pNext->data);
	printf("Node4 data: %d.\n",pHeader->pNext->pNext->pNext->pNext->data); */
	return 0;
}

