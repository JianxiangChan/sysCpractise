#ifndef __DLIST_H
#define __DLIST_H
//#include "malloc.h"
//#include <stdio.h>

//ֻ�ṩ���������ṹ������֣���������֪�����Ĵ�С
//�ⲿ���Է��ʽṹ��ָ�룬���ǲ��������ṹ�ı�����
//�ṩ���������ٺ���
struct _Node;
typedef struct _Node Node;

//�ṩ���������ٺ���
Node *node_create (int data);
char note_delete(Node *thiz, int data);
char note_insert_all(Node *thiz, Node *new, int index);
char note_list(Node *thiz, int index);
#endif