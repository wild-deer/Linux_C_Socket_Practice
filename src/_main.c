#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#define PORT_SERVER 8000
#include "_struct.h"
#include "_userlogin.h"
#include "_menu.h"     //菜单样式文件
  //结构体设置
#include "_record.h"   //记录读取同步
#include "_wcord.h"    //记录存储同步
#include "_check.h"    //唯一性验证
#include "_continue.h" //是否继续判断
#include "_insert.h"
#include "_delete.h"
#include "_update.h"
#include "_select.h"
#include "_info.h"     //show
int mysock_fd;
struct sockaddr_in server_addr;
//int N[1]={0};
int main(int argc, char *argv[])
{	
if(argc < 2)
	{
		printf("错误：参数不够\n");
		printf("例子：./main 127.0.0.1 \n");
		exit(1);
	}
	int choose;
	//初始化，文件中记录读取到程序，同步
	//更改业务关系，写入server服务器端了。以前是从_save.dat中读出来的数据/
	_record();
	//char username[20];
	_user();
	while(limit==2)
	{	
		//=k========第二工程：和服务器建立连接=================
//建立套接字
	mysock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(mysock_fd == -1)
	{
		perror("socket");
		exit(1);
	}
//地址结构
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000);
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	bzero(&(server_addr.sin_zero),8);
//connect
	if(connect(mysock_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(1);
	}
	//=k========第四工程：开始运行时，先接收服务器发来的基础数据
	if(recv(mysock_fd,stu,sizeof(stu),0)<=0)
	{
		perror("recv");
		exit(1);
	}
	int i;
	n =0;
	for(i = 0;i < MAX ;i ++)
	{
		if(stu[i].id!=0)
		{
			n++;
		}
	}
	//_wcord();
	printf("OK！客户端数据与服务器同步！\n");
	sleep(1);
	printf("OK！同步完成！\n");
	printf("当前在册学生人数：%d",n);
	sleep(1);
//=s=========================================
	
		printf("\033c");//清屏后显示菜单，每次返回菜单清屏
		_menu();         //调用菜单样式函数
		scanf("%d",&choose);
		
		//选择菜单调用各函数
		switch(choose)
		{
			case 1:_insert();break;//增加1条记录
			case 2:_delete();break;//删除1条记录
			case 3:_update();break;//更新1条记录
			case 4:_select();break;//查找1条记录
			case 5:_info();break;  //显示全部再册学员信息
			case 6:exit(0);        //退出管理系统
		}
}
	while(limit==1)
	{	
		//=k========第二工程：和服务器建立连接=================
//建立套接字
	mysock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(mysock_fd == -1)
	{
		perror("socket");
		exit(1);
	}
//地址结构
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000);
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	bzero(&(server_addr.sin_zero),8);
//connect
	if(connect(mysock_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(1);
	}
	//=k========第四工程：开始运行时，先接收服务器发来的基础数据
	if(recv(mysock_fd,stu,sizeof(stu),0)<=0)
	{
		perror("recv");
		exit(1);
	}
	int i;
	n =0;
	for(i = 0;i < MAX ;i ++)
	{
		if(stu[i].id!=0)
		{
			n++;
		}
	}
	//_wcord();
	printf("OK！客户端数据与服务器同步！\n");
	sleep(1);
	printf("OK！同步完成！\n");
	printf("当前在册学生人数：%d",n);
	sleep(1);
//=s=========================================
	
		printf("\033c");//清屏后显示菜单，每次返回菜单清屏
		_menu1();         //调用菜单样式函数
		scanf("%d",&choose);
		
		//选择菜单调用各函数
		switch(choose)
		{
			//case 1:_insert();break;//增加1条记录
			//case 2:_delete();break;//删除1条记录
			//case 3:_update();break;//更新1条记录
			case 1:_select();break;//查找1条记录
			case 2:_info();break;  //显示全部再册学员信息
			case 3:exit(0);        //退出管理系统
		}
	}
	return 0;
}
