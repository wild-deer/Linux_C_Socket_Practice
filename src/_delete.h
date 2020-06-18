void _delete()
{
	//引入全局变量,其他变量
	extern int mysock_fd;
	extern struct sockaddr_in server_addr;
	extern _stu stu[MAX];
	extern int n;
	int id;
	int flag;//删除时，验证后返回value 标记
	int ok;//确认是否删除标记
	int i;
	//服务器通信
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
	//输入要删除的id号
	printf("INPUT DELETE ID:");
	scanf("%d",&id);
	//1,============如果找到返回下标，未找到返回-1
	flag = _check(id);
	if(flag == -1)//无记录
	{
		printf("查无此人!\n");
		sleep(1);
		return ;
	}
	else //有记录，执行删除
	{
		printf("学号\t姓名\t成绩\n");
		printf("%d\t%s\t%d\n",stu[flag].id,stu[flag].name,stu[flag].score);
		//是否删除提示：
		printf("是否确认删除？1--确认，0--取消!\n");
		scanf("%d",&ok);
		if(ok == 1)
		{	
			//2,========删除--从被删除处开始，用后面结构体成员对前面结构体成员覆盖
			for(i=flag;i<n-1;i++)
			{
				stu[i] = stu[i+1];
			}
			for(;i< MAX;i++)
			{
				stu[i].id = 0;
			}
			n--;
			printf("删除完毕!\n");
			sleep(1);
		}
		
	}
	//备份，同步数据到文件
	//=========第三工程：和服务器收发数据
	if(send(mysock_fd,stu,sizeof(stu),0)==-1)
	{
		perror("send");
		exit(1);
	}
		close(mysock_fd);
	_wcord();
	sleep(1);
}







