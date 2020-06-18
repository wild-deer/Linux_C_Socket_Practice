/*
功能：是否继续的验证，返回0，则继续点名，返回1则退出点名系统
函数名：_continue()
形参: void
返回值: int
*/
int _continue()
{
	char flag[100];
	printf("input \"yes\" to continue! input \"no\" to EXIT!\n:");
	scanf("%s",flag);
	if(strcmp(flag,"no")==0 || strcmp(flag,"NO")==0) return 1;
	else return 0;
}

