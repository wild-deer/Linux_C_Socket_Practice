/*
功能：同步程序操作到文件
函数名：_wcord()
形参: void
返回值: void
*/
void _wcord()
{
	extern _stu stu[MAX];
	extern int n;
	FILE *fsave,*fcount;
	//打开_save.dat学员记录数据文件，权限：wb 二进制写
	fsave = fopen("_save.dat","wb");
	//打开_count.dat人数数据文件，权限: w写
	fcount = fopen("_count.dat","w");
	//将更新后的人数同步到文件
	fprintf(fcount,"%d",n);
	//将更新后的学生记录更新到文件
	fwrite(stu,sizeof(_stu),n,fsave);
	//关闭文件指针
	fclose(fsave);
	fclose(fcount);

}
