/*
功能：记录查重，重复返回下标，无重复记录返回-1
函数名：_check()
形参: int id
返回值: int
*/
int _check(int id)
{
	int i;
	extern _stu stu[MAX];
	extern int n;
	for(i=n-1;i>=0;i--)
	{
		if(stu[i].id == id) break;//存在重复记录
	}
	return i;
}
