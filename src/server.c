#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"_struct.h"
#include"_record.h"
#define PORT_SERVER 8000

//接收客户端发来的数据
//int N[1]={0};
int main()
{
	pid_t ppid,pid;

//=========第五期工程：共享内存建立，让各个进程能共享数据
	int shmid;
	_stu *shmp,*shmq;
	shmid = shmget(IPC_PRIVATE,1024,IPC_CREAT|0666);
	shmq = (_stu*)shmat(shmid,0,0);//?
    _record();
//=========第四期工程：服务器运行开始先读取server_save2190.dat文件中的数据到stu数组

	
//=========第二工程：和客户端建立连接
	int server_fd,client_fd;
	int i;
	struct sockaddr_in sockaddr_server,sockaddr_client;
	int addr_length = sizeof(struct sockaddr_in);
//套接字描述符
	server_fd = socket(AF_INET,SOCK_STREAM,0);
	if(server_fd == -1)
	{
		perror("socket");
		exit(1);
	}
	printf(">>OK!TCP服务器建立套接字描述符成功！>>\n");
//结构地址
	sockaddr_server.sin_family = AF_INET;
	sockaddr_server.sin_port = htons(PORT_SERVER);
	sockaddr_server.sin_addr.s_addr = INADDR_ANY;
	bzero(&(sockaddr_server.sin_zero),8);
//绑定bind
	if(bind(server_fd,(struct sockaddr*)&sockaddr_server,sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		exit(1);
	}
	printf(">>OK!TCP服务器绑定地址结构成功！>>\n");
//监听listen
	if(listen(server_fd,10) == -1)
	{
		perror("listen");
		exit(1);
	}
	printf(">>ok!TCP服务器开启监听成功！>>\n");
	printf(">>TCP服务器等待客户端响应！\n");
//accept connect
//=========第五期工程：实现多任务编程。并发式服务器完成多客户端和服务器交互，每一个进程处理一个客户端关系
while(1)
{
	client_fd = accept(server_fd,(struct sockaddr*)&sockaddr_client,&addr_length);	
	if(client_fd == -1)
	{
		perror("accept");
		exit(1);
	}
	printf("\t>>=====有客户端和服务器建立连接！=====>>\n");
	ppid = fork();
	
	if(ppid == 0)
	{
		pid = fork();
		while(1)
		{	
			if(pid > 0)
			{	
				//=========第四工程：先将服务器备份数据发送给客户端，让客户端在这个基础上操作
				//=========第四期工程：服务器运行开始先读取server_save2190.dat文件中的数据到stu数组

				FILE *fsave,*fcount;
				fsave = fopen("server_save2190.dat","rb");
				fcount = fopen("server_count2190.dat","r");
				fscanf(fcount,"%d",&n);
				fread(shmq,sizeof(_stu),n,fsave);
				fclose(fsave);
				fclose(fcount);
				
				for(i = 0; i< MAX;i++)
				{
					stu[i].id = shmq[i].id;
					strcpy(stu[i].name,shmq[i].name);
					stu[i].score=shmq[i].score;
				}
				if(send(client_fd,stu,sizeof(stu),0)==-1)
				{
					perror("send");
					exit(1);
				}
			}
				else if(pid == 0)
				{	shmp = (_stu*)shmat(shmid,0,0);
					
					//=========第三工程：接收客户端发来的备份dat数据
					if(recv(client_fd,stu,sizeof(stu),0)<=0)
					{	
						perror("recv");
						exit(1);
					}
					
					for(i = 0; i< MAX;i++)
					{
						shmp[i].id = stu[i].id;
						strcpy(shmq[i].name,stu[i].name);
						shmp[i].score = stu[i].score;
					}
					//备份数据
						int i;
					n =0;
					for(i = 0;i < MAX ;i ++)
					{
						if(stu[i].id!=0)
						{
							n++;
						}
					}
					printf("在册学生人数 = %d\n",n);
					FILE *fp;
					FILE *fcount;
					fp = fopen("server_save2190.dat","wb");
					fcount = fopen("server_count2190.dat","w");
					fwrite(stu,sizeof(_stu),MAX,fp);
					fprintf(fcount,"%d",n);
					fclose(fcount);
					fclose(fp);
				}
			
		}
	}

	
	
	
	/*if(recv(client_fd,N,sizeof(N),0)<=0)
	{
		perror("recv");
		exit(1);
	}*/
	close(client_fd);
//备份发来的数据：和客户端子文件最后一样
}
}
