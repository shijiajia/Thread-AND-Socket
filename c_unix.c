/*************************************************************************
	> File Name: c_unix.c
	> Author: JiaShi
	> Mail: 838357982@qq.com 
	> Created Time: 2015年10月06日 星期二 11时22分16秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/un.h>
#define UNIX_DOMAIN "/tmp/UNIX.domain"
int main()
{
	int connect_fd;
	char snd_buf[1024];
	int i;
	static struct sockaddr_un srv_addr;
	connect_fd=socket(PF_UNIX,SOCK_STREAM,0);
	if (connect_fd<0)
	{
		printf("Create communication socket failed\n");
		return 0;
	}
	srv_addr.sun_family=AF_UNIX;
	strcpy(srv_addr.sun_path,UNIX_DOMAIN);
	if (-1==connect(connect_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr)))
	{
		printf("connect failed\n");
		close(connect_fd);
		return 0;
	}
	memset(snd_buf,0,1024);
	strcpy(snd_buf,"message from client");
	for (i=0;i<4;i++)
		write(connect_fd,snd_buf,sizeof(snd_buf));
	close(connect_fd);
	return 0;
}
