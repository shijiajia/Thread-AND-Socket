/*************************************************************************
	> File Name: s_unix.c
	> Author: JiaShi
	> Mail: 838357982@qq.com 
	> Created Time: 2015年10月06日 星期二 10时54分20秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include <unistd.h>
#define UNIX_DOMAIN "/tmp/UNIX.domain"
int main()
{
	socklen_t clt_addr_len;
	int listen_fd;
	int com_fd;
	int i;
	static char recv_buf[1024];
	int len;
	struct sockaddr_un clt_addr;
	struct sockaddr_un srv_addr;
	listen_fd=socket(PF_UNIX,SOCK_STREAM,0);
	if(listen_fd<0)
	{
		printf("Create communication socket failed!\n");
		return 0;
	}
	srv_addr.sun_family=AF_UNIX;
	strncpy(srv_addr.sun_path,UNIX_DOMAIN,sizeof(srv_addr.sun_path)-1);
	unlink(UNIX_DOMAIN);
	if (-1==bind(listen_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr)))
	{
		printf("Bind failed!\n");
		close(listen_fd);
		unlink(UNIX_DOMAIN);	
		return 0;
	}
	if(-1==listen(listen_fd,1))
	{
		printf("Listen failed\n");
		close(listen_fd);
		unlink(UNIX_DOMAIN);
		return 0;
	}
	clt_addr_len=sizeof(clt_addr);
	com_fd=accept(listen_fd,(struct sockaddr*)&clt_addr,&clt_addr_len);
	if (com_fd<0)
	{
		printf("accept failed\n");
		close(listen_fd);
		unlink(UNIX_DOMAIN);
		return 0;
	}
	printf("/n==============info===============\n");
	for (i=0;i<4;i++)
	{
		memset(recv_buf,0,1024);
		int num = read(com_fd,recv_buf,sizeof(recv_buf));
		if (strcmp(recv_buf,"")!=0)
		printf("Message from client (%d):%s\n",num,recv_buf);
	}
	close(com_fd);
	close(listen_fd);
	unlink(UNIX_DOMAIN);
	return 0;
}
