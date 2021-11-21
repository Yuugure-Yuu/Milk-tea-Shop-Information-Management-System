/************************************************************************
* 文件名称： Order.c

* 代码功能：
*     本文件实现关于点餐的功能。

*************************************************************************/
#include <windows.h>
#include <string.h>
#include <time.h>
#include "../Order/Order.h"
#include "../Menu/Menu.h"

extern  char acName[10];
//服务员登录名

/************************************************************************
* 函数名称：void Order_add(int count1,struct Order_t *pNew,pList pTitle,pList pOrder,pList pMenu,char tabpath[])
* 主要功能：
		   加菜功能函数
* 形参说明：
*       int count1              菜谱链表的个数
		struct Order_t *pNew    对应的订单数据指针
		pList pTitle            详单链表的头指针
		pList pOrder            订单链表的头指针
		pList pMenu             菜谱链表的头指针
		char tabpath[]          详单的中间存放路径
* 返回值：
*       无
*************************************************************************/

void Order_add(int count1, struct Order_t* pNew, pList pTitle, pList pOrder, pList pMenu, char tabpath[])
{
	/************************************/
	
	/**************************************/
	FILE* fp;
	pList ps, ps1;
	int t;
	int count;
	// conut计数第几道菜
	struct Menu_t* data;
	struct Title_t* DATA;
	char str[8];
	while (1)
	{
		JR_EmptyRaw(count1 + 3, count1 + 12);
		JR_SetCursor(count1 + 11, 0);
		printf("\t\t\t\t\t\t\t按<Esc>键退出...");
		JR_SetCursor(count1 + 3, 0);
		memset(str, 0, sizeof(char));
		printf("\t\t请输入要增加的菜编号：");
		Input_control(str, '0', '9', 5, 2); 
		// str存着菜编号
		if (strcmp(str, "0") == 0)
		{
			return;
		}
		printf("\n\t\t请输入要增加的份数：");
		t = Input_control(NULL, '1', '9', 1, 2);
		// t存着菜的份数
		count = 0;
		ps = pMenu->pNext;
		while (ps != NULL)
		{
			count++;
			// 计数第几道菜
			data = (struct Menu_t*)(ps->pData);
			if (strcmp(data->num, str) == 0)
				//找到菜谱中对应的菜信息
			{
				//data->food_nums = (data->food_nums) + t;
				break;
			}
			ps = ps->pNext;
		}
		
		if (ps == NULL)
		{
			printf("\n\t\t菜编号输入有误，请重新输入，按任意键继续...");
			getch();
		}
		else
			break;
	}
	printf("\n\n\t\t是否确认加菜(y)确定、(n)返回:");
	if (Input_control(NULL, 0, 0, 1, 1) == 'n')
	{
		printf("\n\t\t加菜失败，按任意键返回...");
		getch();
		return;
	}
	ps1 = pTitle->pNext;
	while (ps1 != NULL)
	{
		DATA = (struct Title_t*)(ps1->pData);
		if (strcmp(DATA->pMenu.num, str) == 0)
			// 判断详单中是否有点菜此道菜
		{
			DATA->amount = t + (DATA->amount);
			// 点过的菜，份数增加t

			JR_SetCursor(count, 0);
			// 光标定位到点过的菜那行
			printf("\t\t*%-11s%-12s￥%-10d%-12d", DATA->pMenu.num, DATA->pMenu.name,
				DATA->pMenu.price, DATA->amount);
			// 重新打印此行的菜信息
			
			break;
		}
		ps1 = ps1->pNext;
	}
	if (ps1 == NULL)
	{
		List_add(pTitle, Title_init(pNew, data, t));
		// 没点过，新点的菜添加到详单链表中 
		JR_SetCursor(count, 0);
		// 光标定位到没点过的菜那行
		printf("\t\t*%-11s%-12s￥%-10d%-12d", data->num, data->name, data->price, t);
		// 重新打印
	}
	fp = File_open(tabpath);
	File_write(fp, pTitle, sizeof(struct Title_t), 0);
	//加菜结果写入到详单中间文件中
	Order_statist(pNew, pTitle);
	// 订单信息也跟着更新
	fp = File_open("../../Code/Data/Cache/Order.txt");
	File_write(fp, pOrder, sizeof(struct Order_t), 0);
	// 订单更新写入到中间文件
	JR_SetCursor(count1 + 1, 0);
	printf("\t\t\t\t\t%-4s:%-5d%-4s:%d\n", "总金额", pNew->money, "总份数", pNew->amount);
	JR_SetCursor(count1 + 7, 0);
	printf("\t\t加菜成功");
	printf("\n\t\t是否继续加菜，(y)确定、(n)返回：");
	if (Input_control(NULL, 0, 0, 1, 1) == 'y')
		Order_add(count1, pNew, pTitle, pOrder, pMenu, tabpath);
	// 是否继续加菜
	struct Menu_t *food;
}

/************************************************************************
* 函数名称：void Order_del(int count1,struct Order_t *pNew,pList pTitle,pList pMenu,pList pOrder,char tabpath[])
* 主要功能：
		   减菜功能函数
* 形参说明：
*       int count1               菜谱链表的个数
		struct Order_t *pNew    对应的订单数据指针
		pList pTitle            详单链表的头指针
		pList pOrder            订单链表的头指针
		pList pMenu             菜谱链表的头指针
		char tabpath[]          详单的中间存放路径
* 返回值：
*       无
*************************************************************************/

void Order_del(int count1, struct Order_t* pNew, pList pTitle, pList pMenu, pList pOrder, char tabpath[])
{
	FILE* fp;
	pList ps, pt;
	int t;
	struct Title_t* DATA;
	char str[8];
	int count;
	// 记录输入的菜的位置
	JR_EmptyRaw(count1 + 3, count1 + 12);
	JR_SetCursor(count1 + 11, 0);
	printf("\t\t\t\t\t\t\t按<Esc>键退出...");
	JR_SetCursor(count1 + 3, 0);
	memset(str, 0, sizeof(char));
	printf("\t\t请输入退掉的菜编号：");
	Input_control(str, '0', '9', 5, 2);
	if (strcmp(str, "0") == 0)
	{
		return;
	}
	printf("\n\t\t请输入要退掉的份数：");
	t = Input_control(NULL, '1', '9', 1, 2);
	count = 0;
	ps = pMenu->pNext;
	while (ps != NULL)
	{
		count++;
		// 计数第几道菜
		if (strcmp(((struct Menu_t*)(ps->pData))->num, str) == 0)
			//找到菜谱中对应的菜信息
		{
			break;
		}
		ps = ps->pNext;
	}
	pt = pTitle;
	ps = pTitle->pNext;
	while (ps != NULL)
	{
		DATA = (struct Title_t*)(ps->pData);
		if (strcmp(DATA->pMenu.num, str) == 0)
			// 判断详单中是否有点菜此道菜
		{
			if (t > DATA->amount)
				// 要退的份数大于实际点过的份数
			{
				printf("\n\t\t输入份数超过实际份数，按任意键继续...");
				getch();
				break;
			}
			else
			{
				printf("\n\n\t\t是否确认退菜(y)确定、(n)返回:");
				if (Input_control(NULL, 0, 0, 1, 1) == 'n')
				{
					printf("\n\t\t退菜失败，按任意键继续...");
					getch();
					return;
				}
				DATA->amount = (DATA->amount) - t;
				// 更新份数
				if (DATA->amount == 0)
					// 退的份数是否等于点过的
				{
					JR_SetCursor(count, 0);
					printf("\t\t%-12s%-12s￥%-10d%-12d", DATA->pMenu.num,
						DATA->pMenu.name, DATA->pMenu.price, DATA->amount);
					// 重新打印,去掉*号
					pt->pNext = ps->pNext;
					// 释放详单中这道菜的结点
					free(ps);
					fp = fopen(tabpath, "w+");
				}
				else
				{
					fp = File_open(tabpath);
					JR_SetCursor(count, 0);
					printf("\t\t*%-11s%-12s￥%-10d%-12d", DATA->pMenu.num,
						DATA->pMenu.name, DATA->pMenu.price, DATA->amount);
					// 份数不为0，重新打印，
				}

				File_write(fp, pTitle, sizeof(struct Title_t), 0);
				// 把退菜结果写入中间文件
				Order_statist(pNew, pTitle);
				// 更新订单信息
				fp = File_open("../../Code/Data/Cache/Order.txt");
				File_write(fp, pOrder, sizeof(struct Order_t), 0);
				// 订单更新写入到中间文件
				JR_SetCursor(count1 + 1, 0);
				printf("\t\t\t\t\t%-4s:%-5d%-4s:%d\n", "总金额", pNew->money, "总份数", pNew->amount);
				JR_SetCursor(count1 + 6, 0);
				printf("\n\t\t退菜成功，按任意键继续...");
				getch();
				return;
			}
		}
		pt = ps;
		ps = ps->pNext;
	}
	if (ps == NULL)
	{
		printf("\n\t\t此道菜未点或不存在，无法退菜，按任意键继续...");
		getch();
	}

}

/************************************************************************
* 函数名称：void Order_print(pList pMenu,pList pTitle,struct Order_t *pNew)
* 主要功能：
		   订单打印函数
* 形参说明：
*       pList pMenu            菜谱的头指针
		pList pTitle           详单的头指针
		struct Order_t *pNew   订单数据的指针
* 返回值：
*        无
*************************************************************************/

void Order_print(pList pMenu, pList pTitle, struct Order_t* pNew)
{

	pList pt, ps;
	struct Title_t* data;
	struct Menu_t* pM;
	system("cls");
	printf("\t\t%-12s%-12s%-12s%-12s\n", "菜编号", "菜名", "价格", "份数");
	pt = pMenu->pNext;
	while (pt)
	{
		ps = pTitle->pNext;
		pM = (struct Menu_t*)(pt->pData);
		while (ps)
		{
			data = (struct Title_t*)(ps->pData);
			if (strcmp(data->pMenu.num, pM->num) == 0)
				//判断详单中是否存有这道菜
			{
				printf("\t\t%c", '*');
				// 为点过的菜编号前打印*
				printf("%-11s%-12s%s%-10d%-12d\n", data->pMenu.num, data->pMenu.name,
					"￥", data->pMenu.price, data->amount);
				break;
			}
			ps = ps->pNext;
		}
		if (ps == NULL)
		{
			printf("\t\t%-12s%-12s%s%-10d%-12d\n", pM->num, pM->name, "￥", pM->price, 0);
		}
		pt = pt->pNext;

	}
	printf("\t\t\t\t\t%-4s:%-5d%-4s:%d\n", "总金额", pNew->money, "总份数", pNew->amount);
}

/************************************************************************
* 函数名称：void Order_statist(struct Order_t *pNew,pList pTitle)
* 主要功能：
		   订单的总金额、总份数统计函数
* 形参说明：
*       struct Order_t *pNew     订单数据的指针
		pList pTitle             详单链表的头指针
* 返回值：
*        无
*************************************************************************/

void Order_statist(struct Order_t* pNew, pList pTitle)
{
	struct Title_t* Data;
	pList pt;
	int money, copies;
	money = copies = 0;
	pt = pTitle->pNext;
	while (pt)
	{
		Data = (struct Title_t*)(pt->pData);
		money = money + (Data->pMenu.price) * (Data->amount);
		//详单的金额累加
		copies = copies + (Data->amount);
		// 详单的份数累加
		pt = pt->pNext;

	}
	pNew->amount = copies;
	// 总金额存入订单中
	pNew->money = money;
	// 总份数存入订单中
}

/************************************************************************
* 函数名称：struct Order_t *Order_init(char str[])
* 主要功能：
		   订单结构体初始化函数
* 形参说明：
*       char str[]  点菜的台桌号
* 返回值：
*        返回初始化的订单结点指针
*************************************************************************/

struct Order_t* Order_init(char str[])
{
	struct Order_t* pNew;
	pNew = (struct Order_t*)malloc(sizeof(struct Order_t));
	memset(pNew, 0, sizeof(struct Order_t));
	strcpy(pNew->tablenum, str);
	// 存入订单结构体的台桌号
	Ordernum_get(pNew->ordernum, str);
	// 自动获得订单号

	return pNew;

}

/************************************************************************
* 函数名称：struct Title_t *Title_init(struct Order_t *pNew,struct Menu_t *data,int n)
* 主要功能：
		   详单结构体初始化函数
* 形参说明：
*       struct Order_t *pNew     点菜中台桌对应的订单数据的指针
		struct Menu_t *data      新增的菜谱数据
		int n                    菜的份数
* 返回值：
*        返回初始化的详单结点指针
*************************************************************************/

struct Title_t* Title_init(struct Order_t* pNew, struct Menu_t* data, int n)
{
	struct Title_t* pTemp;
	pTemp = (struct Title_t*)malloc(sizeof(struct Title_t));
	memset(pTemp, 0, sizeof(struct Title_t));
	strcpy(pTemp->ordernum, pNew->ordernum);
	// 往详单中存入订单号
	pTemp->pMenu = *data;
	// 新增的某一道菜谱
	pTemp->amount = n;
	// 菜的份数

	return pTemp;

}

/************************************************************************
* 函数名称：long Ordernum_get(char num[],char str[])
* 主要功能：
		   自动生成订单号的函数
* 形参说明：
*       char num[]    订单结构体中的订单号成员变量
		char str[]    点菜的台桌号
* 返回值：
*        返回订单号
*************************************************************************/

long Ordernum_get(char num[], char str[])
{
	int year, month, day;
	char s[6] = { 0 };
	time_t t;
	//时间类型
	struct tm* data;
	//时间结构体
	time(&t);
	//获取时间，存于rawtime
	data = localtime(&t);
	//转换为当地时间
	year = 1900 + data->tm_year;
	// 取得系统当前日期
	month = data->tm_mon + 1;
	day = data->tm_mday;
	if (num == NULL&&str == "month")
	{
		return((year * 100 + month) * 100);
	}
	if (num == NULL && str == NULL)
	{
		return ((year * 100 + month) * 100 + day);
		// 返回整型的日期
	}
	convert(s, year, 4);
	// 转换日期为字符串
	strcat(num, s);
	// 组合成订单号
	convert(s, month, 2);
	strcat(num, s);
	convert(s, day, 2);
	strcat(num, s);
	if (num != NULL && str == NULL)
		// num获取字符型的日期
	{
		return 0;
	}
	strcat(num, str);
	// num获取订单号，订单号后面为台桌号str
	return 0;

}


void convert(char s[], int data, int n)
{
	int t, i = 0;
	t = data;
	while (t != 0)
	{
		s[n - 1 - i] = t % 10 + 48;
		// 整型转换为字符型
		t = t / 10;
		i++;
		if (data < 10 && n == 2)
			// 小于10的月份和天数，前面加字符0
		{
			s[0] = '0';
		}
	}
	s[n] = '\0';
}


/************************************************************************
* 函数名称：void Order_search_unbuy(pList pOrder,pList pTable)
* 主要功能：
		   未买订单查询函数
* 形参说明：
*      pList pOrder     订单的头指针

* 返回值：
*        无
*************************************************************************/

void Order_search_unbuy(pList pOrder)
{
	pList pt;
	struct Order_t* data;
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

}

/************************************************************************
* 函数名称：void Order_search_buy()
* 主要功能：
		   已买订单查询函数
* 形参说明：
*        无
* 返回值：
*        无
*************************************************************************/

void Order_search_buy()
{
	FILE* fp;
	struct Order_t* data;
	pList pt, pOrder;
	int count = 0;
	long* stardate, * enddate;
	long ordernum;// 订单号
	fp = File_open("../../Code/Data/Order/Order.txt");
	// 打开已买单的文件
	pOrder = File_read(fp, sizeof(struct Order_t));
	// 读出已买单的链表
	stardate = (long*)malloc(sizeof(long));
	// 开始日期
	enddate = (long*)malloc(sizeof(long));
	// 结束日期

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
		Orderdate_input(stardate, enddate);
		// 输入开始和结束日期
		printf("\n");
	}
	printf("\t\t%-16s%-11s%-11s%-11s\n", "订单号", "金额", "状态", "服务员");
	pt = pOrder->pNext;
	while (pt)
	{
		data = (struct Order_t*)(pt->pData);
		sscanf(data->ordernum, "%8ld", &ordernum);
		if ((ordernum <= *enddate) && (ordernum >= *stardate))
		{
			count++;
			printf("\t\t%-16s%s%-9d%-11s%-11s\n", data->ordernum, "￥", data->money, "已结账", data->acname);
		}
		pt = pt->pNext;
	}
	if (count == 0)
	{
		system("cls");
		printf("\n此日期内未查询到相关订单，请按任意键返回...");
	}
	else
		printf("\n\t\t请按任意键返回...");
	List_free(pOrder);
}


/************************************************************************
* 函数名称：void Title_print(pList pTitle,struct Order_t *pOrder)
* 主要功能：
		   详单打印函数
* 形参说明：
*      pList pTitle             详单的头指针
	   struct Order_t *pOrder   订单数据的指针
* 返回值：
*        无
*************************************************************************/

void Title_print(pList pTitle, struct Order_t* pOrder)
{
	pList pt;
	struct Title_t* data;
	system("cls");
	printf("\t\t%-12s%-12s%-12s%-12s\n", "菜编号", "菜名", "价格", "份数");
	pt = pTitle->pNext;
	while (pt)
	{
		data = (struct Title_t*)(pt->pData);
		printf("\t\t%c", '*');
		printf("%-11s%-12s%s%-10d%-12d\n", data->pMenu.num, data->pMenu.name, "￥", data->pMenu.price, data->amount);
		pt = pt->pNext;
	}
	printf("\n\t\t%-4s:￥%-4d%-4s:%d\n", "总金额", pOrder->money, "总份数", pOrder->amount);
}

/************************************************************************
* 函数名称：void Orderdate_input(long *stardate,long *enddate)
* 主要功能：
		   开始日期和结束日期的输入函数
* 形参说明：
*       long *stardate    开始日期的指针
		long *enddate     结束日期的指针
* 返回值：
*        无
*************************************************************************/

void Orderdate_input(long* stardate, long* enddate)
{
	char str[6] = { 0 };
	int n;
	long curdate = 0;
	// 当前日期
	curdate = Ordernum_get(NULL, NULL);
	// 获取当前系统日期
	while (1)
	{
		system("cls");
		printf("开始日期：     -  -  ");
		JR_SetCursor(0, 10);
		*stardate = Input_control(str, '0', '9', 4, 2);
		if (*stardate < 2020)
		{
			printf("\n年份不可低于2020哦，小店是20年开张的~~按任意键重新输入...");
			getch();
			memset(str, 0, sizeof(char));
			// 清零str
			continue;
			// 跳过本次循环
		}
		JR_SetCursor(0, 16);
		memset(str, 0, sizeof(char));
		n = Input_control(str, '0', '9', 2, 2);
		if (n > 12 || n == 0)
		{
			printf("\n月份需在1-12月内，按任意键重新输入...");
			getch();
			memset(str, 0, sizeof(char));
			// 清零str
			continue;
			// 跳过本次循环		
		}
		*stardate = (*stardate) * 100 + n;
		JR_SetCursor(0, 19);
		memset(str, 0, sizeof(char));
		n = Input_control(str, '0', '9', 2, 2);
		if (n > 31 || n == 0)
		{
			printf("\n宁是俺带哥，呜呜天数要在1-31日啊，按任意键重新输入...");
			getch();
			memset(str, 0, sizeof(char));
			// 清零str
			continue;
			// 跳过本次循环
		}
		*stardate = (*stardate) * 100 + n;
		memset(str, 0, sizeof(char));

		printf("\n结束日期：     -  -  ");
		JR_SetCursor(1, 10);
		*enddate = Input_control(str, '0', '9', 4, 2);
		if (*enddate < 2020)
		{
			printf("\n年份不可低于2020，按任意键重新输入...");
			getch();
			memset(str, 0, sizeof(char));
			// 清零str
			continue;
			// 跳过本次循环
		}
		JR_SetCursor(1, 16);
		memset(str, 0, sizeof(char));
		n = Input_control(str, '0', '9', 2, 2);
		if (n > 12 || n == 0)
		{
			printf("\n月份需在1-12月内，无力吐槽...按任意键重新输入...");
			getch();
			memset(str, 0, sizeof(char));
			// 清零str
			continue;
			// 跳过本次循环
		}
		*enddate = (*enddate) * 100 + n;
		JR_SetCursor(1, 19);
		memset(str, 0, sizeof(char));
		n = Input_control(str, '0', '9', 2, 2);
		if (n > 31 || n == 0)
		{
			printf("\n天数需在1-31日内，按任意键重新输入...");
			getch();
			memset(str, 0, sizeof(char));
			// 清零str
			continue;
			// 跳过本次循环
		}
		*enddate = (*enddate) * 100 + n;
		memset(str, 0, sizeof(char));
		if (*stardate > * enddate)
		{
			printf("\n开始日期不可大于结束日期，按任意键重新输入...");
			getch();
		}
		else if (*enddate > curdate)
		{
			printf("\n超出当前系统日期，按任意键重新输入...");
			getch();
		}
		else
			break;
	}

}