#ifndef __DLIST_H
#define __DLIST_H
//#include "malloc.h"
//#include <stdio.h>

//只提供给编译器结构体的名字，编译器不知道他的大小
//外部可以访问结构的指针，但是不能声明结构的变量，
//只给出结构体的接口，访问结构体，只能通过对应的函数来访问
//禁止定义全局变量来降低系统的耦合
struct _Node;
typedef struct _Node Node;

//提供创建和销毁函数
Node *node_create (int data);
char note_delete(Node *thiz, int data);
char note_insert_all(Node *thiz, Node *new, int index);
char note_list(Node *thiz, int index);
#endif