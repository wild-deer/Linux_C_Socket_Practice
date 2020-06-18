#define MAX 50
typedef struct student
{
	int id;
	char name[50];
	int score;
}_stu;
_stu stu[MAX];
//学员信息数组
int n = 0;//当前系统人数
typedef struct username
{
	
	char username[20];//用户名
	char password[20];
	int limit;//权限
}_USER;
_USER user[MAX];
int limit;//全局权限标识

