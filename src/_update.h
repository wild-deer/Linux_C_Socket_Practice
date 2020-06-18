void _update()
{
	extern int mysock_fd;
	extern struct sockaddr_in server_addr;
	extern _stu stu[MAX];
	extern int n;
	int id,i;
	int flag;
	char s[200];
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
	
	printf("请输入您要修改的学生的学生的id:");
	scanf("%d",&id);
	flag = _check(id);
	if(flag>=0)
	{	printf("请输入您要修改的信息：\n");
		sleep(1);
		//printf("id:");
		//scanf("%d",&stu[flag].id);
		printf("NAME:");
		scanf("%s",stu[flag].name);
		printf("SCORE:");
		scanf("%d",&stu[flag].score);
		printf("修改成功!\n");
		sleep(1);
		printf("ID\t\tNAME\t\tSCORE\n");
		printf("%-10d\t",stu[flag].id);
		printf("%-10s\t",stu[flag].name);
		printf("%d\n",stu[flag].score);
	}else
	{
		printf("查无此人");
	}
	
	//=======第三工程，
	if(send(mysock_fd,stu,sizeof(stu),0)==-1)
	{
		perror("send");
		exit(1);
	}
	printf("press \"yes\" to back menu!\n");
	scanf("%s",s);
		close(mysock_fd);
		_wcord();
}
