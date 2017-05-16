#include "dlist.h"

int main (void)
{
	
/* 	long long sum = 0;
	int max = 0;
	DList *p = dlist_create();
	int data[6] ={1,2,3,4,5,6};
	dlist_add(p, -1, (void *)data[0]);
	dlist_add(p, -1, (void *)data[1]);
	dlist_add(p, -1, (void *)data[2]);
	dlist_add(p, 0, (void *)data[3]);
	dlist_add(p, 1, (void *)data[0]);
	dlist_foreach(p, int_print, NULL);
	dlist_delete(p, 2);
	dlist_foreach(p, int_print, NULL);
	dlist_foreach(p, sum_cb, &sum);
	printf("sum = %lld\n",sum);
	dlist_foreach(p, max_cb, &max);
	printf("sum = %d\n",max); */
	
	DList *p_str = dlist_create();
	//注意 这里的strdup函数 是调用了malloc的，所以正常的使用时候需要用free()
	dlist_add(p_str, -1, strdup("It"));
	dlist_add(p_str, -1, strdup("is"));
	dlist_add(p_str, -1, strdup("OK"));
	dlist_add(p_str, -1, strdup("!"));
	
	dlist_foreach(p_str, str_toupper, NULL);
	dlist_foreach(p_str, str_print, NULL);

	return 0;
}


