/*************************************************************************
	> File Name: Threadtest.c
	> Author: JiaShi
	> Mail: 838357982@qq.com 
	> Created Time: 2015年10月03日 星期六 09时08分53秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
char message[]="Hello World";
void thread_function(void *arg)
{
	printf("Thread_functionf is running. Argument was %s\n",(char *)arg);
	sleep(3);
	strcpy(message,"Bye");
	pthread_exit("Thank you for your CPU time\0");
}
int main()
{
	pthread_t thread;
	void *thread_result;
	int tmp;
	if(0!=(tmp=pthread_create(&thread,NULL,(void *)thread_function,(void*)message)))
	{
		printf("Thread create failed\n");
		return 0;
	}
	if(0!=(tmp=pthread_join(thread,&thread_result)))
	{
		printf("Thread join failed\n");
		return 0;
	}
	printf("Thread joined, it returned %s\n",(char *)thread_result);
	printf("Message is now %s\n",message);
	return 0;
}
