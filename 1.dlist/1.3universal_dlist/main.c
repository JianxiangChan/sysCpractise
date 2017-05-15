#include "dlist.h"

int main (void)
{
	DList *p = dlist_create();
	int data[6] ={1,2,3,4,5,6};
	dlist_add(p, -1, (void *)data[0]);
	dlist_add(p, -1, (void *)data[1]);
	dlist_add(p, -1, (void *)data[2]);
	dlist_add(p, 0, (void *)data[3]);
	dlist_add(p, 1, (void *)data[0]);
	dlist_print(p, print_int);
	dlist_delete(p, 2);
	dlist_print(p, print_int);
	return 0;
}


