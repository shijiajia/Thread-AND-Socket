/*************************************************************************
	> File Name: Thread_mutex.c
	> Author: JiaShi
	> Mail: 838357982@qq.com 
	> Created Time: 2015年10月03日 星期六 10时53分57秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<string.h>
#define SIZE 1024;
char buffer[1024];
pthread_mutex_t mutex;
void thread_function()
{
	sleep(1);
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("The string you input is %s\n",buffer);
		pthread_mutex_unlock(&mutex);
		if (strncmp(buffer,"end",3)==0) break;
		sleep(1);
	};
}
int main()
{
	pthread_t thread;
	int tid=pthread_self();
	printf("the tid is %d\n",tid);
	if (0!=pthread_mutex_init(&mutex,NULL))
	if (0!=pthread_create(&thread,NULL,(void *)thread_function,NULL))
	{
		printf("thread_create failde!!!!!!!!!!!!!!!!!!!!\n");
		return 0;
	}
	while(1)
	{
		pthread_mutex_lock(&mutex);
		scanf("%s",buffer);
		pthread_mutex_unlock(&mutex);
		if (strncmp(buffer,"end",3)==0)
		{
			printf("Fininsh!!!!!!!!!!!!!!!!!!!!!\n");
			break;
		}
		sleep(1);
	}
	
	if (0!=pthread_join(thread,NULL))
	{
		printf("thread_join failed!!!!!!!!!!!!!!!!!!!!\n");
		return 0;
	}
	pthread_mutex_destroy(&mutex);

	return 0;
}
