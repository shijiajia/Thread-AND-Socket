/*************************************************************************
	> File Name: Thread_sem.c
	> Author: JiaShi
	> Mail: 838357982@qq.com 
	> Created Time: 2015年10月03日 星期六 10时18分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>
#define SIZE 1024
char buffer[SIZE];
sem_t sem;
void thread_function()
{
	sem_wait(&sem);
	while (strcmp(buffer,"end")!=0)
	{
		printf("Your input string is %s\n",buffer);
		sem_wait(&sem);
	}
}
int main()
{
	pthread_t thread;
	sem_init(&sem,0,0);
	if (0!=pthread_create(&thread,NULL,(void*)thread_function,NULL))
	{
		printf("Thread created failed!!!!!!!!!!!!!!\n");
		return 0;
	}
	while(scanf("%s",buffer))
	{
		sem_post(&sem);
		if(strncmp(buffer,"end",3)==0)
		{
			printf("Finish!!!!!!!!!!!!!!!!!!\n");
			break;
		}
	}

	if (0!=pthread_join(thread,NULL))
	{
		printf("Thread joined failed!!!!!!!!!!!!!!\n");
		return 0;
	}
	sem_destroy(&sem);
	return 0;
}
