#include <stdio.h>
#include <pthread.h>
#include <assert.h>

void* start_routine(void* param)
{
	char* str = (char*)param;
	printf("%s:%s\n",__func__,str);
	return NULL;
}

pthread_t creat_test_thread()
{
	pthread_t id = 0;
	char str[] = "it is OK!";
	
	pthread_creat(&id, NULL, start_routine, str);
	
	return id;
}

int main(int argc, char* argv[])
{
	void* ret = NULL;
	
	pthread_t id = creat_test_thread();
	
	pthread_join(id, &ret);
	
	return 0;
}