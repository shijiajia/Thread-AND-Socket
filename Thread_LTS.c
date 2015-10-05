/*************************************************************************
	> File Name: Thread_LTS.c
	> Author: JiaShi
	> Mail: 838357982@qq.com 
	> Created Time: 2015年10月03日 星期六 16时55分41秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define SIZE 10
pthread_key_t g_key;
typedef struct thread_data{
	int thread_no;
} thread_data_t;
void show_thread_data()
{
	thread_data_t *data=(thread_data_t*)pthread_getspecific(g_key);
	printf("Thread %d\n",data->thread_no);
}
void thread_function(void *arg)
{
	thread_data_t *data=(thread_data_t *)arg;
	printf("Start thread %d\n",data->thread_no);
	pthread_setspecific(g_key,data);
	show_thread_data();
	printf("Thread %d exit\n",data->thread_no);
	sleep(2);

}
void free_thread_data(void *arg)
{
	thread_data_t *data=(thread_data_t*)arg;
	printf("Free thread %d data\n",data->thread_no);
	free(data);
}
int main()
{
	pthread_t thread[10];
	thread_data_t *data=NULL;
	pthread_key_create(&g_key,free_thread_data);
	int i=0;
	for (i=0;i<SIZE;i++)
	{
		data=malloc(sizeof(thread_data_t));
		data->thread_no=i;
		if (0!=pthread_create(&thread[i],NULL,(void *)thread_function,data))
		{
			printf("Create thread NO.%d failed\n",i);
			return 0;
		}
	}
	for (i=0;i<SIZE;i++)
	{
		if (0!=pthread_join(thread[i],NULL))
		{
			printf("Join thread NO.%d failed\n",i);
			return 0;
		}
	}
	pthread_key_delete(g_key);
	return 0;
}
