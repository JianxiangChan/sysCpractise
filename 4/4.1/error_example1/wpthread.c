#include <stdio.h>
#include <pthread.h>
#include <assert.h>

//如果是全局变量就不会出现这种问题。
char str[] = "it is OK!";
void* start_routine(void* param)
{
	char* str = (char*)param;
	printf("%s:%s\n",__func__,str);
	return NULL;
}

pthread_t creat_test_thread()
{
	pthread_t id = 0;
	//这里把临时变量作为了线程参数
	//char str[] = "it is OK!";
	
	pthread_create(&id, NULL, start_routine, str);
	
	return id;
}

int main(int argc, char* argv[])
{
	void* ret = NULL;
	
	pthread_t id = creat_test_thread();
	
	pthread_join(id, &ret);
	
	return 0;
}