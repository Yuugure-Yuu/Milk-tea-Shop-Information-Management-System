/************************************************************************
* 文件名称： main.c

* 代码功能：
*     本文件为主函数入口，实现系统的运行。

*************************************************************************/
#include <windows.h>
#include "./Staff/Staff.h"
#include "./File/File.h"
#include "./Log_in/Log_in.h"
#include "./Admin/Admin.h"
#include "./Waiter/Waiter.h"
#include "./Manage/Manage.h"

int main()
{
	pList head, p;
	char staff[] = "../../Code/Data/Staff.txt";
	int (*pFile[3])() = { Ui_waiter, Ui_manage, Ui_admin };
	//光标放在上一行的三个函数变量上可看到相关文档
	//其他函数同理，也都有相关文档
	
	FILE* fp;
	fp = File_open(staff);
	head = File_read(fp, sizeof(struct staff_t));
	p = head;
	if (p->pNext == NULL)
	{
		Login_initManager(fp, head);
		//若职工文件问空，则初始化管理员账户
/************************************************************************
*本项目附带的职工文件含三名职工，对应三个层级

*管理员（老板）账号为admin，密码为123456
*服务员账号为waiter，密码为111111
*经理账号为manager，密码为666666

*不同层级用户使用不同用户界面，调用不同系统模块
*************************************************************************/
	}
	p = p->pNext;
	if (p->pNext == NULL)
	{
		Login_init(fp, head);
		//接着初始化经理账户
	}
	
	while(1)
	{
		fclose(fp);
		if (pFile[Log_in(head)]() == 1)
			//运行用户界面
			//若返回1，则用户已选择注销
		{
			break;
		}

		fp = File_open(staff);
		head = File_read(fp, sizeof(struct staff_t));
	}
	system("cls");
	//清屏
	printf("\n\n\n\t\t\t已退出系统");
	return 0;
}