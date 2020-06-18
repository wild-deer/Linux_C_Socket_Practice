/*
功能：
登陆

*/

//#include "_struct.h"
void _login()
{
	FILE *fland;
	int n;//用户个数
	int i;
	extern int limit;//记录当前用户权限
	extern _USER user[MAX];
	//登陆输入用户名，密码
	char username[20];
	char password[20];
	printf("username:");
	scanf("%s",username);
	printf("password:");
	scanf("%s",password);
	//以读打开_username.dat
	fland = fopen("_username.dat","r");
	//读_username.dat中用户个数
	fscanf(fland,"%d",&n);
	//读取_username.dat中的用户信息及权限
	for(i=0;i<n;i++)
	{
		fscanf(fland,"%s",user[i].username);
		fscanf(fland,"%s",user[i].password);
		fscanf(fland,"%d",&user[i].limit);
	}
	//比对
	for(i=0;i<n;i++)
	{
		//username存在
		if(strcmp(user[i].username,username)==0)
		{
			//且password正确
			if(strcmp(user[i].password,password)==0)
			{
				//提取权限
				limit = user[i].limit;
			}
		}
	}
	//不是 1 2就无登陆权限
	if(!limit==1||!limit==2) 
	{
		printf("无此用户，请核对后尝试登陆！\n");
		exit(0);
	}
}
/*
功能：提供登陆框
*/


int _user()
{	
	
	int choose;
	//用户登陆菜单
	while(1)
	{
		printf("\033c");
		printf("\t\t|===============|\n");
		printf("\t\t|======user=====|\n");
		printf("\t\t|====1.login====|\n");
		printf("\t\t|====2.exit=====|\n");
		printf("\t\t|===============|\n");
		printf("选择操作：");
		scanf("%d",&choose);
		switch(choose)
		{	
			case 1:_login();return;//return返回主调函数，主函数
			case 2:printf("EXIT!\n");exit(0);
			default: printf("error!\n");exit(0);
		}
	}
}


