/*************************************************************************
	> File Name: threadtest.c
	> Author: JiaShi
	> Mail: 838357982@qq.com 
	> Created Time: 2015年10月02日 星期五 18时40分58秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void thread1(void *b)
{
	int i;
	int *a=(int *)b;
	for (i=0;i<10;i++)
	{
	    (*a)++;
	    printf("thread1 print a = %d\n",*a);
		sleep(4);
	}
}
void thread2(void *b)
{
	int i=0;
	int *a=(int *)b;
	for (i=0;i<10;i++)
	{
    	(*a)++;
//    	printf("thread2 print a = %d\n",*a);
		sleep(1);
	}
}
int main()
{
	pthread_t id1,id2;
	int ret = 0;
	int a=0;
	ret =pthread_create(&id1,NULL,(void*)thread1,&a);
	ret =pthread_create(&id2,NULL,(void*)thread2,&a);
	printf("main thread print a = %d\n",a);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	printf("main thread print a = %d\n",a);
	return 0;
}



















