/*
功能：显示当前所有学生信息
函数名：_info()
形参: void
返回值: void
*/
void _info()
{	extern int mysock_fd;
	extern struct sockaddr_in server_addr;
	char flag[100];
	extern _stu stu[MAX];
	extern int n;
	int i;
	if(recv(mysock_fd,stu,sizeof(stu),0)<=0)
	{
		perror("recv");
		exit(1);
	}
	
	n =0;
	for(i = 0;i < MAX ;i ++)
	{
		if(stu[i].id!=0)
		{
			n++;
		}
	}
	_wcord();
	//input print
	printf("ID\t\tNAME\t\tSCORE\n");
	for(i=0;i<38;i++)
	{
		printf("=");
	}
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("%-10d\t",stu[i].id);
		printf("%-10s\t",stu[i].name);
		printf("%d\n",stu[i].score);
	}
	//press any key to back!
	
//	=========第四工程
if(send(mysock_fd,stu,sizeof(stu),0)==-1)
	{
		perror("send");
		exit(1);
	}
	printf("press \"yes\" to back menu!");
	scanf("%s",flag);
		close(mysock_fd);
_wcord();
}
