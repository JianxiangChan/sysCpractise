#include "dlist.h"

int main (void)
{
	Node *pHeader = node_create(0);
	note_insert_all(pHeader, node_create(1), 0);
	note_insert_all(pHeader, node_create(2), 1);
	note_insert_all(pHeader, node_create(3), 2);
	note_insert_all(pHeader, node_create(4), 3);
	note_insert_all(pHeader, node_create(5), 2); 
	note_insert_all(pHeader, node_create(6), 0);
	note_list(pHeader, 0);
	note_delete(pHeader, 6);
	note_list(pHeader, -1);

	return 0;
}
