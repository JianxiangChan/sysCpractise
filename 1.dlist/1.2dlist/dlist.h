#ifndef __DLIST_H
#define __DLIST_H
//#include "malloc.h"
//#include <stdio.h>

//只提供给编译器结构体的名字，编译器不知道他的大小
//外部可以访问结构的指针，但是不能声明结构的变量，
//提供创建和销毁函数
struct _Node;
typedef struct _Node Node;

//提供创建和销毁函数
Node *node_create (int data);
char note_delete(Node *thiz, int data);
char note_insert_all(Node *thiz, Node *new, int index);
char note_list(Node *thiz, int index);
#endif