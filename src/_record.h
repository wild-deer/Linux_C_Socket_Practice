/*
功能：初始化同步程序数据，将文件数据读到程序
函数名：_record()
形参: void
返回值: void
*/
void _record()
{
	extern _stu stu[MAX];
	extern int n;
	FILE *fsave,*fcount;
	//打开_save.dat学员记录数据文件，权限：rb 二进制读
	fsave = fopen("_save.dat","rb");
	//打开_count.dat人数数据文件，权限: r读
	fcount = fopen("_count.dat","r");
	//将人数同步到程序的全局变量n
	fscanf(fcount,"%d",&n);
	//将学生记录同步到程序的全局结构体stu[MAX]
	fread(stu,sizeof(_stu),n,fsave);
	//关闭文件指针
	fclose(fsave);
	fclose(fcount);
	
}
