/************************************************************************
* 文件名称： Admin.c

* 代码功能：
*     本文件实现关于管理员（老板）管理数据的功能。

*************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "../File/File.h"
#include "../Admin/Admin.h"
#include "../List/List.h"
#include "../Staff/Staff.h"
#include "../Table/Table.h"
#include "../Menu/Menu.h"
#include "../Input_Control/Input_Control.h"



/************************************************************************
* 函数名称：int Ui_admin()
* 主要功能：
		   管理员功能选择函数
* 形参说明：
*       无
* 返回值：
*        一个整型数字，用来判断是注销还是退出
*************************************************************************/

int Ui_admin()
{
	int n;
	void (*pst[4])() = { Table_manage,Menu_manage,Staff_manage };
	while (1)
	{
		system("cls");
		printf("\n\n\n\t\t\t─=≡Σ(((つ·ω·)つ：老板，在这里选功能！\n\n");
		printf("\t\t\t1、台桌管理\n\n");
		printf("\t\t\t2、菜谱管理\n\n");
		printf("\t\t\t3、人员管理\n\n");
		printf("\t\t\t4、注销\n\n");
		printf("\t\t\t5、退出\n\n");
		printf("\t\t\t(。⊙ v ⊙。):(加薪~加薪~加薪~重要的事情默念3遍!!!)");
		printf("\n\n\n\t\t\t(≥ o ≤)→：老板~这里输入序号，只能选1个哦：");

		n = Input_control(NULL, '1', '5', 1, 2);
		if (n > 0 && n < 4)
		{
			pst[n - 1]();
			//分别运行Table_manage、Menu_manage、Staff_manage三个函数
		}
		else if (n == 4)
			return 0;
		else if (n == 5)
			return 1;
	}

}


/************************************************************************
* 函数名称：void Staff_manage()
* 主要功能：
		   员工管理选择函数
* 形参说明：
*       无
* 返回值：
*        无
*************************************************************************/

void Staff_manage()
{
	char dirname[] = "../../Code/Data/Staff.txt";
	FILE* fp;
	pList head;
	int n;
	fp = File_open(dirname);
	head = File_read(fp, sizeof(struct staff_t));

	while (1)
	{
		system("cls");
		//清屏
		printf("\n\n\n\t\t\t((·_·;|)):(心里有种不祥的预感.jpg)\n\n");
		printf("\t\t\t1、增加员工\n\n");
		printf("\t\t\t2、删除员工\n\n");
		printf("\t\t\t3、修改员工\n\n");
		printf("\t\t\t4、查询员工\n\n");
		printf("\t\t\t5、返回\n\n");
		printf("\t\t\t请输入功能，谨慎修改！！：");
		n = Input_control(NULL, '1', '5', 1, 2);
		switch (n)
		{
		case 1:
			List_print(head, staff_print);
			File_add(fp, head, sizeof(struct staff_t), staff_add);
			List_print(head, staff_print);
			break;
		case 2:
			List_print(head, staff_print);
			File_remove(fp, head, sizeof(struct staff_t), staff_remove);
			head = File_read(fp, sizeof(struct staff_t));
			List_print(head, staff_print);
			break;
		case 3:
			List_print(head, staff_print);
			File_updata(fp, head, sizeof(struct staff_t), staff_update);
			head = File_read(fp, sizeof(struct staff_t));
			List_print(head, staff_print);
			break;
		case 4:
			staff_search(head);
			break;
		case 5:
			break;
		}
		if (n == 5)
		{
			break;
		}
		else
		{
			printf("\n按<Esc>键返回...");
			while (getch() != 27)
			{
			}
			//当读入不为<Esc>键时不返回，防止误触返回
		}

	}
	List_free(head);
}


/************************************************************************
* 函数名称：void Table_manage()
* 主要功能：
		   台桌管理选择函数
* 形参说明：
*       无
* 返回值：
*        无
*************************************************************************/

void Table_manage()
{
	char dirname[] = "../../Code/Data/Table.txt";
	FILE* fp;
	pList head;
	int n;
	fp = File_open(dirname);
	head = File_read(fp, sizeof(struct Table_t));
	while (1)
	{
		system("cls");
		printf("\n\n\t\t\t((·*·))/嘤嘤嘤~您要的功能都在哦~");
		printf("\n\n\n\t\t\t台桌管理界面\n\n");
		printf("\t\t\t1、增加台桌\n\n");
		printf("\t\t\t2、删除台桌\n\n");
		printf("\t\t\t3、修改台桌\n\n");
		printf("\t\t\t4、查询台桌\n\n");
		printf("\t\t\t5、返回\n\n");
		printf("\t\t\t功能写在这里叭：");
		n = Input_control(NULL, '1', '5', 1, 2);
		switch (n)
		{
		case 1:
			List_print(head, Table_print);
			File_add(fp, head, sizeof(struct Table_t), Table_add);
			head = File_read(fp, sizeof(struct Table_t));
			List_print(head, Table_print);
			break;
		case 2:
			List_print(head, Table_print);
			File_remove(fp, head, sizeof(struct Table_t), Table_remove);
			head = File_read(fp, sizeof(struct Table_t));
			List_print(head, Table_print);
			break;
		case 3:
			List_print(head, Table_print);
			File_updata(fp, head, sizeof(struct Table_t), Table_update);
			head = File_read(fp, sizeof(struct Table_t));
			List_print(head, Table_print);
			break;
		case 4:
			Table_search(head, 3, 4);
			break;
		case 5:
			break;
		}
		if (n == 5)
		{
			break;
		}
		else
		{
			printf("\n按<Esc>键返回...");
			while (getch() != 27)
			{
			}
		}

	}
	List_free(head);
}



/************************************************************************
* 函数名称：void Menu_manage()
* 主要功能：
		   菜谱管理选择函数
* 形参说明：
*       无
* 返回值：
*        无
*************************************************************************/

void Menu_manage()
{
	char dirname[] = "../../Code/Data/Menu.txt";
	FILE* fp;
	pList head;
	int n;
	fp = File_open(dirname);
	head = File_read(fp, sizeof(struct Menu_t));
	while (1)
	{
		system("cls");
		printf("\n\n\n\t\t\t((^Δ^))/：老板来看菜谱啦~\n\n");
		printf("\t\t\t1、增加菜谱\n\n");
		printf("\t\t\t2、删除菜谱\n\n");
		printf("\t\t\t3、修改菜谱\n\n");
		printf("\t\t\t4、查询菜谱\n\n");
		printf("\t\t\t5、返回\n\n");
		printf("\t\t\t功能都在这里哦，选一个叭：");
		n = Input_control(NULL, '1', '5', 1, 2);
		switch (n)
		{
		case 1:
			List_print(head, Menu_print);
			File_add(fp, head, sizeof(struct Menu_t), Menu_add);
			head = File_read(fp, sizeof(struct Menu_t));
			List_print(head, Menu_print);
			break;
		case 2:
			List_print(head, Menu_print);
			File_del(fp, dirname, head, sizeof(struct Menu_t), Menu_del);
			List_print(head, Menu_print);
			break;
		case 3:
			List_print(head, Menu_print);
			File_updata(fp, head, sizeof(struct Menu_t), Menu_update);
			head = File_read(fp, sizeof(struct Menu_t));
			List_print(head, Menu_print);
			break;
		case 4:

			Menu_search(head);
			break;
		case 5:
			break;
		}
		if (n == 5)
		{
			break;
		}
		else
		{
			printf("\n按<Esc>键返回...");
			while (getch() != 27)
			{
			}
		}

	}
	List_free(head);
}



