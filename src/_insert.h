/*
功能：增加1条学生记录
        1，必要验证
        2，验证通过insert
        3，记录存储同步到文件
函数名：_insert()
形参: voit
返回值: void
*/
void _insert()
{	extern int mysock_fd;
	extern struct sockaddr_in server_addr;
	extern _stu stu[MAX];
	extern int n;
	//extern int N[1];
	int id,i;
	//更新_record的记录和_count的人数
	
	//==接受服务端信息
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
	
	//1,============check部分
	//验证：人满返回主函数
	if(n >= MAX) 
	{
		printf("人数以满!\n");return ;
	}
	//调用_check()函数查重,无记录返回-1，有记录返回其下标
	while(1)
	{
		printf("input ID:");
		scanf("%d",&id);
		if(_check(id) == -1)//是新记录，insert
		{
			break;
		}
		else//信息重复，重新输入
		{
			printf("记录重复，请核对!\n");
			//调用判断继续函数，继续返回0，退出返回1
			if(_continue() == 0) {continue;}
			else
			{
			if(send(mysock_fd,stu,sizeof(stu),0)==-1)
			{
				perror("send");
				exit(1);
			}
			 return ;
			 }
		}
	}
	//2,===============insert部分
	stu[n].id = id;//验证成功，就直接把id赋入结构体成员
	printf("请输入学生姓名:");
	scanf("%s",stu[n].name);
	printf("请输入学生成绩:");
	scanf("%d",&stu[n].score);
	printf("添加学员信息成功！\n");
	n++;//实际人数增加
	//N[0] = n;
	
	//=========第三工程：和服务器收发数据


	if(send(mysock_fd,stu,sizeof(stu),0)==-1)
	{
		perror("send");
		exit(1);
	}
	/*if(send(mysock_fd,N,sizeof(N),0)==-1)
	{
		perror("send");
		exit(1);
	}*/
	//3，=============记录存储同步
	close(mysock_fd);
	_wcord();
	sleep(1);//延迟1秒
}
