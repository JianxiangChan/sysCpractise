#include <stdio.h>
#include <pthread.h>
#include <assert.h>

//如果是全局变量就不会出现这种问题。
char str[] = "it is OK!";
void* start_routine(void* param)
{
	int index = *(int *)param;
	printf("%s:%d\n", __func__, index);
	return NULL;
}

#define THREADS_NR 10
void creat_test_thread()
{
	int i = 0;
	void* ret = NULL;
	pthread_t ids[THREADS_NR] = {0};
	for(i = 0;i < THREADS_NR; i++)
	{
		//因为这里是并发的，所以不知道谁先谁后 打印的值也是随机的
		pthread_create(ids +i, NULL, start_routine, &i);
		//这里阻塞了其他线程直到当前线程退出。
		pthread_join(ids[i], &ret);
	}
	return;
}

int main(int argc, char* argv[])
{
	creat_test_thread();
	
	return 0;
}