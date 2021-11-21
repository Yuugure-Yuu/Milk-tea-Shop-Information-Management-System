/************************************************************************
* 文件名称： Manage.c

* 代码功能：
*     本文件实现关于经理查询的功能。

*************************************************************************/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "../Manage/Manage.h"
#include "../List/List.h"
#include "../Staff/Staff.h"
#include "../Order/Order.h"
#include "../Menu/Menu.h"


/************************************************************************
* 函数名称：int Ui_manage()
* 主要功能：
		   经理功能选择函数
* 形参说明：
*       无
* 返回值：
*        一个整型数字，用来判断是注销还是退出
*************************************************************************/

int Ui_manage()
{
	int n;
	while (1)
	{
		system("cls");
		printf("\n\n\n\t\t\t(⊙v⊙)：尊敬的经理您好！");
		printf("\n\n\n\n\t\t\t(⊙v⊙)：经理，功能选择在下面：\n\n");
		printf("\t\t\t1、营收汇总\n\n");
		printf("\t\t\t2、注销\n\n");
		printf("\t\t\t3、退出\n\n");
		printf("\t\t\t(⊙v⊙)→：经理，功能一次选一个哦：");
		n = Input_control(NULL, '1', '3', 1, 2);
		if (n == 1)
		{
			Profit_statist();
		}
		else if (n == 2)
			return 0;
		else if (n == 3)
			return 1;
	}

}

/************************************************************************
* 函数名称：void Profit_statist()
* 主要功能：
		   本函数用于实现日流水、月流水数据的统计分析。
* 形参说明：
*       无
* 返回值：
*        无
*************************************************************************/

void Profit_statist()
{
	pList pOrder, pStaff;
	pList p1, p2;
	struct Order_t* Odate;
	struct staff_t* Sdate;
	FILE* fp;
	long money, income;
	// 总金额
	long* stardate, * enddate;
	long ordernum;
	// 订单号
	money = income = 0;
	stardate = (long*)malloc(sizeof(long));
	// 开始日期
	enddate = (long*)malloc(sizeof(long));
	// 结束日期
	fp = File_open("../../Code/Data/Order/Order.txt");
	pOrder = File_read(fp, sizeof(struct Order_t));
	fp = File_open("../../Code/Data/Staff.txt");
	pStaff = File_read(fp, sizeof(struct staff_t));

	system("cls");
	printf("\n\n\t\t\t((⊙.w⊙))：（心里慌得一批~要查什么？偷瞄~~）");
	printf("\n\n\n\n\t\t\t(1):当天查询\n");
	printf("\n\t\t\t(2):历史查询\n");
	printf("\n\t\t\t((⊙o⊙))：要看这个呀~__");
	if (Input_control(NULL, '1', '2', 1, 2) == 1)
	{
		system("cls");
		*stardate = Ordernum_get(NULL, NULL);
		// 获取当前系统日期
		*enddate = *stardate;
	}
	else
	{
		system("cls");
		printf("\n\n\t\t\t((/QAQ /!))不会经营不善吧？不会吧？");
		printf("\n\n\n\t\t\t(1):本月流水\n");
		printf("\n\t\t\t(2):指定日期\n");
		printf("\n\t\t\t请输入要选择的功能：");
		if (Input_control(NULL, '1', '2', 1, 2) == 2)
		{
			Orderdate_input(stardate, enddate);
			// 输入开始和结束日期
			printf("\n");
		}
		else
		{
			system("cls");
			*stardate = Ordernum_get(NULL, "month");
			*enddate = Ordernum_get(NULL, NULL);
		}
	}
	printf("\n\n\t\t\t%-15s%s\n", "服务员", "营收");
	p1 = pStaff->pNext;
	while (p1)
	{
		Sdate = (struct staff_t*)(p1->pData);
		p2 = pOrder->pNext;
		while (p2)
		{
			Odate = (struct Order_t*)(p2->pData);
			sscanf(Odate->ordernum, "%8ld", &ordernum);
			// 获取订单号上的日期
			if ((strcmp(Sdate->acName, Odate->acname) == 0) && (ordernum <= *enddate) && (ordernum >= *stardate))
			{
				money = money + (Odate->money);
			}
			p2 = p2->pNext;
		}
		if ((Sdate->role == 0))
			// 判断是否为服务员
		{
			printf("\t\t\t%-15s%s%ld\n", Sdate->acName, "￥", money);
			income = income + money;
			// 累加每个服务员的营业额
			money = 0;
		}
		p1 = p1->pNext;
	}
	int a, month, c;
	char time[10] = { 0 };
	Ordernum_get(time, NULL);
	sscanf(time, "%4d%2d%2d", &a, &month, &c);
	printf("\n\t\t\t现在是%2d月哦((>ε<))\n\n", month);
	printf("\n\t\t\t总营业额：￥%ld\n", income);
	printf("\n\t\t\t啦啦啦~~按任意键返回...");
	getch();
}







