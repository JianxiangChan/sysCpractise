#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"

//将功能类似的代码（如宏定义、类型定义、函数声明、和全局变量）放在一起，和其他的部分使用空行分隔
#define MAX_PATH 260					//宏定义：单词大写，多个单词下划线分隔

//空行分隔一行就够了，不然显得空空荡荡的

//C语言双链表的实现
//构建一个双链表节点类型
//结构体/枚举/联合名声明使用空行分隔（这里是声明之间空行，还是内部成员之间空行？）
struct Node								//结构体/枚举/联合名 首字母大写							
{										//多个单词连写
		int data;
		struct Node *pPrev;
		struct Node *pNext;
};

//创建一个双向链表
struct Node *node_create (int data)		//函数名小写，多个单词用下划线分隔
{										//面对对象的命名方式：采用主语+谓语的形式来命名
										//取代传统的 谓语+宾语方式
										//对象都有自己的生命周期，所以需要创建对于的销毁函数

	struct Node *p = (struct Node *)malloc(sizeof(struct Node));
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
//函数体之间使用空格
//双向链表尾部插入
void node_insert_tail (struct Node *thiz, struct Node *new) //第一个参数为对象，并用thiz命名
{
	//第一步：找到链表的尾节点
	struct Node *p = thiz;
	while (NULL != p->pNext)
	{
		p -> pNext;
	}
	
	//第二步：将新的节点插入到原来尾部节点的后面
	p->pNext = new;
	new->pPrev = p;
}

//双向链表头部插入
void note_insert_head_middle(struct Node *thiz, struct Node *new)
{
	new->pNext = thiz->pNext;								//新节点的next指针指向原来的节点1的地址
	//只有表头节点不能让第一个节点指向新节点，这样会导致内存错误
	if(NULL != thiz->pNext)		
		thiz->pNext->pPrev = new;
	thiz->pNext = new;
	new->pPrev = thiz;
	
}

/* //双向链表中间插入
void insert_middle(struct node *thiz, struct node *new)
{
	struct node *p  = thiz;
	struct node *temp = thiz->pNext;
	p->pNext = new;
	new->pPrev = p;
	new->pNext = temp;
	temp->pPrev = new;
} */

//插入双向链表中的任意一个节点
//合理使用空格 参数之间用空格 
char note_insert_all(struct Node *thiz, struct Node *new, int index)
{
	//等号之间用空格
	struct Node *p = thiz;
	if(0 > index)
	{	
					//语句末的分号和前面内容不要加空格
		printf("error: illegal input of index.\n");
		return 0;
	}
	
	//第一步，找到index节点
	//if(0 != index)
	//{
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
			node_insert_tail(p, new);
		}
	//}
/* 	else
	{
		insert_head(p, new);
	} */
	return 1;
}

//正向遍历
struct Node * note_list_all(struct Node *thiz)
{
	
	struct Node *p = thiz;
	if(NULL == p)
	{
		return NULL;
	}
	printf("--------------begin-------------\n");
	while(NULL != p->pNext)
	{
		p = p->pNext;
		printf("Node data: %d.\n", p->data);
	}
	printf("--------------end-------------\n");
	return p;
}

//逆向遍历
void note_list_all_reverse(struct Node *pTail)
{
	struct Node *p = pTail;
	printf("--------------begin-------------\n");
	while( NULL != p->pPrev)
	{
		printf("Node data: %d.\n", p->data);
		p = p->pPrev;
	}
	printf("--------------end-------------\n");
}

char note_delete(struct Node *thiz, int data)
{
	struct Node *p = thiz;
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
	struct Node *pHeader = node_create(0);
	note_insert_all(pHeader, node_create(1), 0);
	note_insert_all(pHeader, node_create(2), 1);
	note_insert_all(pHeader, node_create(3), 2);
	note_insert_all(pHeader, node_create(4), 3);
	note_insert_all(pHeader, node_create(5), 2); 
	note_insert_all(pHeader, node_create(6), 0);

	printf("正向遍历： \n");
	struct Node *pTail = note_list_all(pHeader);
	printf("逆向遍历： \n");
	note_list_all_reverse(pTail);
	note_delete(pHeader, 1);
	printf("正向遍历： \n");
	note_list_all(pHeader);
	return 0;
}
