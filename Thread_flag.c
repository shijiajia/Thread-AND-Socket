/*************************************************************************
	> File Name: Thread_flag.c
	> Author: JiaShi
	> Mail: 838357982@qq.com 
	> Created Time: 2015年10月03日 星期六 09时48分51秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
int flag=1;
void thread_function()
{
	int count=1;
	while(count++<20)
	{
		if (flag==1)
		{
			printf("Thread 2 printed falg = 1\n");
			flag=2;
		}else
		{	
			sleep(2);
		}
	}
}
int main()
{
	pthread_t thread;
	if(0!=pthread_create(&thread,NULL,(void *)thread_function,NULL))
	{
		printf("Thread created failed\n");
		return 0;
	}
	int count=1;
	while(count++<20)
	{
	   if (flag==2)
		{
			printf("Thread 1 printed flag = 2 \n");
			flag=1;
		}else
		{
			sleep(2);
		}
	}
	if (0!=pthread_join(thread,NULL))
	{
		printf("Thread joined faild\n");
		return 0;
	}
	return 0;
}
