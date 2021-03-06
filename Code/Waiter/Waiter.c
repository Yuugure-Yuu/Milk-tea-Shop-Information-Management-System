/************************************************************************
* 文件名称： Waiter.c

* 代码功能：
*     本文件实现关于服务员日常工作的功能。

*************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "../Waiter/Waiter.h"

extern  char acName[10];
//服务员登录名

/************************************************************************
* 函数名称：int Ui_waiter()
* 主要功能：
		   服务员界面功能函数
* 形参说明：
*       无
* 返回值：
*        一个整型数字，用来判断是注销还是退出
*************************************************************************/

int Ui_waiter()
{
	pList pTable;
	int n;
	FILE* fp;
	void (*pst[6])(pList pTable) = { Open_desk,Order_dishes,Settle_Accounts,turnover_search,Order_search,printPopularFood };
	fp = File_open("../../Code/Data/Table.txt");
	pTable = File_read(fp, sizeof(struct Table_t));
	while (1)
	{
		system("cls");
		printf("\n\n\t\t\t(≥3≤)づ服务员小姐姐好呀~~");
		printf("\n\n\n\t\t\t~~功能都在这里咯~~\n\n");
		printf("\t\t\t1、开桌\n\n");
		printf("\t\t\t2、点菜\n\n");
		printf("\t\t\t3、结账\n\n");
		printf("\t\t\t4、营业额查询\n\n");
		printf("\t\t\t5、已买/未买单查询\n\n");
		printf("\t\t\t6、店长推荐\n\n");
		printf("\t\t\t7、注销\n\n");
		printf("\t\t\t8、退出\n\n");
		printf("\t\t\t来选个功能叭：");
		n = Input_control(NULL, '1', '8', 1, 2);
		if (n > 0 && n < 7)
		{
			pst[n - 1](pTable);
			//分别运行Open_desk、Order_dishes、Settle_Accounts、turnover_search、Order_search、printPopularFood六个函数
		}
		else if (n == 7)
			return 0;
		else if (n == 8)
			return 1;
	}
}

/************************************************************************
* 函数名称：void Open_desk(pList pTable)
* 主要功能：
		   开桌界面功能函数
* 形参说明：
*       pList pTable   台桌链表的头指针
* 返回值：
*        无
*************************************************************************/

void  Open_desk(pList pTable)
{
	pList pt;
	int n;
	struct Table_t* ps;
	char str[8] = { 0 };
	FILE* fp;
	fp = File_open("../../Code/Data/Table.txt");

	while (1)
	{
		system("cls");
		n = Table_search(pTable, 0, 3);
		// 打印空闲和预定的台桌
		if (n == 0)
		{
			printf("暂无空闲桌子，不好意思，呜呜...按任意键返回...");
			getch();
			return;
		}
		printf("请输入要开桌的台桌号：");
		Input_control(str, '0', '9', 3, 2);
		// str存放要开桌的台桌号
		pt = pTable->pNext;
		while (pt != NULL)
		{
			ps = (struct Table_t*)(pt->pData);
			if (strcmp(ps->acNo, str) == 0)
			{
				if ((ps->state == 0) || (ps->state == 3))
					break;
			}
			pt = pt->pNext;
		}

		if (pt == NULL)
		{
			memset(str, 0, sizeof(char));
			printf("\n台桌号有误或不可用,请重新输入，按任意键继续...");
			getch();
		}
		else
			break;
	}

	if (ps->state == 3)
		// 若为预定状态，直接跳转为点菜界面
	{
		ps->state = 2;
		//占用，转到点菜界面
		File_write(fp, pTable, sizeof(struct Table_t), 0);
		// 更新台桌文件
		printf("\n开桌成功，按任意键继续...");
		getch();
		Order_dishes(pTable);
		// 跳转到点菜界面
		return;
	}
	printf("\n是否马上开始点菜(y)确定、(n)返回：");
	if (Input_control(NULL, 0, 0, 1, 1) != 'y')
	{
		ps->state = 3;
		//预定状态
		File_write(fp, pTable, sizeof(struct Table_t), 0);
		printf("\n预定成功，按任意键继续...");
		getch();
	}
	else
	{
		ps->state = 2;
		//占用，转到点菜界面
		File_write(fp, pTable, sizeof(struct Table_t), 0);
		printf("\n开桌成功，按任意键继续...");
		getch();
		Order_dishes(pTable);
		return;
	}
}

/************************************************************************
* 函数名称：void Order_dishes(pList pTable)
* 主要功能：
		   点菜界面功能函数
* 形参说明：
*       pList pTable   台桌链表的头指针
* 返回值：
*        无
*************************************************************************/

void Order_dishes(pList pTable)
{
	FILE* fd;
	int n, count1;
	pList pMenu, pOrder, pTitle, pt;
	struct Order_t* pNew, * pdata;
	char txt[] = ".txt";
	char str[8] = { 0 };
	char tabpath[30] = "../../Code/Data/Cache/";
	// 详单的相对路径

	fd = File_open("../../Code/Data/Menu.txt");
	pMenu = File_read(fd, sizeof(struct Menu_t));
	fd = File_open("../../Code/Data/Cache/Order.txt");
	pOrder = File_read(fd, sizeof(struct Order_t));

	while (1)
	{
		system("cls");
		n = Table_search(pTable, 2, 4);
		// 判断是否有可用桌子
		if (n == 0)
		{
			printf("，暂无可用桌子，按任意键继续...");
			getch();
			return;
		}
		printf("请输入要点菜的台桌号：");
		Input_control(str, '0', '9', 3, 2);
		strcat(tabpath, str);
		strcat(tabpath, txt);
		// 获取详单的路径
		pt = pOrder->pNext;
		while (pt)
		{
			pdata = (struct Order_t*)(pt->pData);
			if (strcmp(pdata->tablenum, str) == 0)
				// 判断当前未买订单中是否存在此台桌的订单
			{
				pNew = pdata;
				fd = File_open(tabpath);
				pTitle = File_read(fd, sizeof(struct Title_t));
				break;
			}
			pt = pt->pNext;
		}

		if (pt == NULL)
			// 未买订单不存在输入台桌的订单
		{
			pt = pTable->pNext;
			while (pt)
			{
				if (strcmp(((struct Table_t*)(pt->pData))->acNo, str) == 0)
				{
					if (((struct Table_t*)(pt->pData))->state == 2)
					{
						pNew = Order_init(str);
						// 初始化一个订单结点
						List_add(pOrder, pNew);
						File_write(fd, pOrder, sizeof(struct Order_t), 0);
						// 写入未买订单文件
						fd = fopen(tabpath, "w+");
						// 以w+方式打开详单文件，便于开始点菜
						pTitle = File_read(fd, sizeof(struct Title_t));
						break;
					}
					else if (((struct Table_t*)(pt->pData))->state == 0)
					{
						printf("\n此桌号为空闲需先开桌才能点菜，是否开桌，(y)开桌、(n)返回：");
						if (Input_control(NULL, 0, 0, 1, 1) == 'y')
							Open_desk(pTable);
						// 跳转到开桌界面
						return;
					}

				}
				pt = pt->pNext;

			}
			if (pt == NULL)
			{
				memset(str, 0, sizeof(char));
				strcpy(tabpath, "../../Code/Data/Cache/");
				printf("\n输入的桌号有误或者处于维修状态，请重新输入，按任意键继续...");
				getch();
			}
			else
				break;
		}
		else
			break;
	}
	Order_print(pMenu, pTitle, pNew);
	count1 = List_count(pMenu);
	// 获取菜谱的个数
	while (1)
	{
		JR_EmptyRaw(count1 + 3, count1 + 12);
		// 清空菜谱下面的几行信息
		JR_SetCursor(count1 + 3, 0);
		printf("\t\t(1)：点菜\n");
		printf("\t\t(2)：退菜\n");
		printf("\t\t(3)：返回\n");
		printf("\t\t请输入要操作的功能：");
		n = Input_control(NULL, '1', '3', 1, 2);
		switch (n)
		{
		case 1:
		{
			Order_add(count1, pNew, pTitle, pOrder, pMenu, tabpath);
			// 加菜功能函数
			break;
		}
		case 2:
		{
			Order_del(count1, pNew, pTitle, pMenu, pOrder, tabpath);
			// 减菜功能函数
			break;
		}
		case 3:
			break;
		}

		if (n == 3)
		{
			break;
		}

	}
	List_free(pOrder);
	List_free(pMenu);
	List_free(pTitle);
}

/************************************************************************
* 函数名称：void turnover_search(pList pTable)
* 主要功能：
		   营业额查询界面功能函数
* 形参说明：
*       pList pTable   台桌链表的头指针
* 返回值：
*        无
*************************************************************************/

void turnover_search(pList  pTable)
{
	FILE* fp;
	pList pOrder, pt;
	struct Order_t* data;
	long* stardate, * enddate;
	long ordernum;
	// 订单号
	int a, b, c;
	// 用来打印年月日
	long money = 0;
	// 总营业额
	stardate = (long*)malloc(sizeof(long));
	// 开始日期
	enddate = (long*)malloc(sizeof(long));
	// 结束日期
	fp = File_open("../../Code/Data/Order/Order.txt");
	pOrder = File_read(fp, sizeof(struct Order_t));
	// 读出已买订单链表

	system("cls");
	printf("\n\t\t\t(1):当天查询\n");
	printf("\n\t\t\t(2):历史查询\n");
	printf("\n\t\t\t请输入要选择的功能：");
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
		printf("\n\t\t\t(1):本月流水\n");
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

	printf("\t\t%-16s%-18s%-11s\n", "订单号", "时间", "金额");
	pt = pOrder->pNext;
	while (pt)
	{
		data = (struct Order_t*)(pt->pData);
		sscanf(data->ordernum, "%8ld", &ordernum);
		// 字符串转化成长整型
		if ((strcmp(data->acname, acName) == 0) && ((ordernum <= *enddate) && (ordernum >= *stardate)))//
		{
			money = money + (data->money);
			// 营业额累加
			sscanf(data->ordernum, "%4d%2d%2d", &a, &b, &c);
			//分别取出年月日
			printf("\t\t%-16s%d%s%2d%s%2d%-6s%s%d\n", data->ordernum, a, "年", b, "月", c, "日", "￥", data->money);
		}
		pt = pt->pNext;
	}
	int x, month, y;
	char time[10] = { 0 };
	Ordernum_get(time, NULL);
	sscanf(time, "%4d%2d%2d", &x, &month, &y);
	printf("\n\t\t\t当下月份为：%2d月\n\n", month);
	printf("\n\t\t营业额总额：￥%ld\n", money);
	List_free(pOrder);
	printf("\n\t\t按任意键返回...");
	getch();
}

/************************************************************************
* 函数名称：void Order_search(pList pTable)
* 主要功能：
		   已买/未买单查询界面功能函数
* 形参说明：
*       pList pTable   台桌链表的头指针
* 返回值：
*        无
*************************************************************************/

void Order_search(pList  pTable)
{
	int n;
	FILE* fp;
	pList pOrder;
	fp = File_open("../../Code/Data/Cache/Order.txt");
	pOrder = File_read(fp, sizeof(struct Order_t));
	// 读出未买单链表
	while (1)
	{
		system("cls");
		printf("\n\n\n\t\t\t已买/未买单查询界面\n\n");
		printf("\t\t\t1、未买单查询\n\n");
		printf("\t\t\t2、已买单查询\n\n");
		printf("\t\t\t3、退出\n\n");
		printf("\t\t\t请输入您所要选择的功能：");
		n = Input_control(NULL, '1', '3', 1, 2);
		switch (n)
		{
		case 1:
			Order_search_unbuy(pOrder);
			// 未买单查询函数 
			getch();
			break;
		case 2:
			Order_search_buy();
			// 已买单查询函数
			getch();
			break;
		case 3:

			break;
		}
		if (n == 3)
		{
			break;
		}

	}
	List_free(pOrder);
	// 释放链表
}

/************************************************************************
* 函数名称：Settle_Accounts(pList pTable);
* 主要功能：
		   台桌订单结账查询界面功能函数
* 形参说明：
*       pList pTable   台桌链表的头指针
* 返回值：
*        无
*************************************************************************/

void Settle_Accounts(pList pTable)
{
	FILE* fp;
	int money;
	pList pt, pTitle, pOrder, ps;
	struct Order_t* data;
	char txt[] = ".txt";
	char str[6] = { 0 };
	char str1[6] = { 0 };
	char tabpath[30] = "../../Code/Data/Cache/";
	// 未结详单路径
	fp = File_open("../../Code/Data/Cache/Order.txt");
	// 打开未买订单文件
	pOrder = File_read(fp, sizeof(struct Order_t));
	while (1)
	{
		system("cls");
		pt = pOrder->pNext;
		if (pt == NULL)
			//判断当前是否有未买订单
		{
			printf("\n目前没有未买订单，按任意键返回...");
			return;
		}
		printf("\t\t%12s%12s%11s%11s\n", "订单号", "台桌号", "金额", "状态");
		while (pt)
		{
			data = (struct Order_t*)(pt->pData);
			printf("\t\t%12s%12s%11d%11s\n", data->ordernum, data->tablenum, data->money, "未支付");
			// 打印所有未结订单信息
			pt = pt->pNext;
		}
		printf("\n请输入要结账的台桌号(3位)：");
		Input_control(str, '0', '9', 3, 2);
		ps = pOrder;
		pt = pOrder->pNext;
		while (pt)
		{
			data = (struct Order_t*)(pt->pData);
			if (strcmp(data->tablenum, str) == 0)
				// 找出要结账的订单结点
				break;
			ps = pt;
			pt = pt->pNext;
		}
		if (pt == NULL)
			// 未找到订单，作提示
		{
			printf("\n\n台桌号无订单或有误，按<Esc>键返回、其他键重新输入：");
			if (getch() == 27)
				return;
			memset(str, 0, sizeof(char));
		}
		else
			break;
	}
	strcat(tabpath, str);
	// 获取详单的路径
	strcat(tabpath, txt);
	fp = File_open(tabpath);
	// 打开将结账的详单文件
	pTitle = File_read(fp, sizeof(struct Title_t));
	// 读出未买详单链表
	Title_print(pTitle, data);
	// 打印未买详单信息
	printf("\n订单号为%s是否结账，(y)确定、(n)返回：", data->ordernum);
	if (Input_control(NULL, 0, 0, 1, 1) == 'y')
	{
		printf("\n实收金额：");
		money = Input_control(str1, '0', '9', 5, 2);
		// 输入金额
		if (money < data->money)
			// 实收金额不可小于订单金额
		{
			printf("\n实收金额小于订单金额，无法结账，按任意键返回...");
			getch();
			return;
		}
		printf("\n回找金额：%d", money - (data->money));
		fp = File_open("../../Code/Data/Title/Title.txt");
		File_write(fp, pTitle, sizeof(struct Title_t), 2);
		//写入已结详单链表

		fp = File_open("../../Code/Data/Order/Order.txt");
		fseek(fp, 0, 2);
		strcpy(data->acname, acName);
		//写入结账服务员登录名到订单结构体中
		fwrite(data, sizeof(struct Order_t), 1, fp);
		//写入已结订单的结点到另一个文件
		fflush(fp);

		ps->pNext = pt->pNext;
		// 删除结点
		free(pt);
		//释放已结订单的结点
		fp = fopen("../../Code/Data/Cache/Order.txt", "w+");
		File_write(fp, pOrder, sizeof(struct Order_t), 0);
		//刷新未结订单的文件

		pt = pTable->pNext;
		while (pt)
		{
			if (strcmp(((struct Table_t*)(pt->pData))->acNo, str) == 0)
				// 找到已结账台桌结点
			{
				((struct Table_t*)(pt->pData))->state = 0;
				// 桌子状态改为空闲
				fp = File_open("../../Code/Data/Table.txt");
				File_write(fp, pTable, sizeof(struct Table_t), 0);
				// 更新台桌信息文件
				break;
			}
			pt = pt->pNext;
		}
		printf("\n结账成功");
	}
	else
		printf("\n结账失败");
	printf("，按任意键返回...");
	getch();
	List_free(pTitle);
	List_free(pOrder);
}


/************************************************************************
* 函数名称：void printPopularFood(pList pTable)
* 主要功能：
		   打印最受欢迎的食物
* 形参说明：
*       pList pTable   台桌链表的头指针
* 返回值：
*        无
*************************************************************************/

void printPopularFood(pList pTable)
{
	char str[8] = { 0 };
	pList ps, pL;
	struct Menu_t* data;
	pL = List_init(NULL);
	ps = pTable->pNext;
	if (ps == NULL)
	{
		system("cls");
		printf("\n未存有菜谱信息，请先添加！\n");
		return;
	}
	system("cls");
	printf("\n\t\t\t(1) 全部");
	printf("\n\n\t\t\t请输入要查询的条件：");
	if (Input_control(NULL, '1', '2', 1, 2) == 1)
	{
		char dirname[] = "../../Code/Data/Menu.txt";
		FILE* fp;
		pList head1;
		int n;
		fp = File_open(dirname);
		head1 = File_read(fp, sizeof(struct Menu_t));
		pList pt;
		pt = head1->pNext;
		while (pt != NULL)
		{
			static int k = 0;
			struct Menu_t* pd;
			pd = (struct Menu_t*)(pt->pData);
			if (k == 0)
			{
				system("cls");
				printf("\n\n\t\t★门∫面∫担∫当★");
				printf("\n\n\t\t%-10s%-20s%-12s\n", "菜编号", "菜名", "店长推荐");
				//“店长推荐”指数其实是算出来的
				k = 1;
			}
			float pop;
			pop = popf(pd->price);
			printf("\t\t%-10s%-20s%-12.1f分\n", pd->num, pd->name, pop);
			if (pt->pNext == NULL)
				k = 0;
			pt = pt->pNext;
		}
		/**************************/

		printf("按任意键继续");
		getch();
		return;
	}
	
	system("pause");
}