/************************************************************************
* 文件名称： Log_in.c

* 代码功能：
*     本文件实现关于登录界面和初始化的功能。

*************************************************************************/
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "../Log_in/Log_in.h"


char acName[10] = { 0 };
// 存放登陆用户名

/************************************************************************
* 函数名称：void JR_EmptyRaw(int r1,int r2)
* 主要功能：
		   清空指定行的函数
* 形参说明：
*    int r1    开始行
	 int r2	   结束行
* 返回值：
*        无
*************************************************************************/

void JR_EmptyRaw(int r1, int r2)
{
	int i, j;
	for (i = r1; i <= r2; i++)
	{
		JR_SetCursor(i, 0);
		for (j = 0; j <= 80; j++)
			printf("%c", ' ');
		// 用空格来清空每行
	}
}

/************************************************************************
* 函数名称：void JR_SetCursor(int x, int y)
* 主要功能：
		   光标定位函数
* 形参说明：
*    int x   行坐标
	 int y   列坐标
* 返回值：
*        无
*************************************************************************/

void JR_SetCursor(int x, int y)
{

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { y, x };
	SetConsoleCursorPosition(hOut, pos);
}

/************************************************************************
* 函数名称：int Log_in(pList head)
* 主要功能：
		   登录函数
* 形参说明：
*    pList head    员工链表的头指针
* 返回值：
*        员工的角色标志
*************************************************************************/

int Log_in(pList head)
{
	int a, b, c;
	char time[10] = { 0 };
	pList pt;
	struct staff_t* data;
	char name[10] = { 0 };
	// 存放输入的用户名
	char psd[8] = { 0 };
	// 存放输入的密码
	char role[3][10] = { "服务员","经理","管理员" };
	Ordernum_get(time, NULL);
	sscanf(time, "%4d%2d%2d", &a, &b, &c);
	while (1)
	{
		system("cls");
		system("color F1");
		printf("\n\n\t\t\t\t\t小黑＆小白·童话日常(*^o^)/\\(^o^*)");
		printf("\n\n\n\n\n\t\t\t∮登·录·界·面∮");
		printf("\t\t\t\t\t美丽海滨~~欢迎就餐~~\n\n\n\n\n");
		printf("\t\t\t%-19s", "★用户名：");
		printf("\n\n\t\t\t%-19s", "★密码：");
		printf("(6位)");
		printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t当前日期：%4d-%02d-%02d", a, b, c);
		printf("\n\n\n\n\t\t\t\(*^▽^*)/：欢迎欢迎~~小哥哥小姐姐请先登录哟~~");

		JR_SetCursor(12, 33);
		// 光标定位到用户名输入的位置
		Input_control(name, 0, 0, 10, 1);
		// 控制输入函数，只能输入字母
		JR_SetCursor(14, 31);
		// 定位到密码输入的位置
		Input_control(psd, '0', '9', 6, 2);
		//只能输入数字 
		pt = head->pNext;
		while (pt)
		{
			data = (struct staff_t*)(pt->pData);
			if ((strcmp(data->acName, name) == 0) && (strcmp(data->psd, psd) == 0))
			{
				strcpy(acName, data->acName);
				// 存储登陆用户名
				printf("\n\n\t\t\t登录成功，身份为：%s，按任意键继续...", role[data->role]);
				getch();
				return data->role;
				// 返回员工角色标志
			}
			pt = pt->pNext;
		}
		printf("\n\n\t\t\t密码输入错误，请重新输入，按任意键继续...");
		memset(psd, 0, sizeof(char));
		getch();
	}
}

/************************************************************************
* 函数名称：void Login_init(FILE *fp,pList head)
* 主要功能：
		   登录初始化函数，创建管理员admin用户
* 形参说明：
*    FILE *fp    员工文件指针
	 pList head  员工链表的头指针
* 返回值：
*        无
*************************************************************************/

void Login_init(FILE* fp, pList head)
{
	struct staff_t* data;
	data = (struct staff_t*)malloc(sizeof(struct staff_t));
	data->acNO = 1000;
	// 初始化管理员的参数
	strcpy(data->acName, "admin");
	strcpy(data->psd, "123456");
	data->role = 2;
	// 管理员身份
	data->flag = 1;
	List_add(head, data);
	// 添加到链表
	File_write(fp, head, sizeof(struct staff_t), 0);
	// 写入文件   

}
/************************************************************************
* 函数名称：void Login_initManager(FILE *fp,pList head)
* 主要功能：
			登录初始化函数，创建管理员manager用户
* 形参说明：
*		FILE *fp    经理文件指针
		pList head  经理链表的头指针
* 返回值：
*        无
*************************************************************************/
void Login_initManager(FILE* fp, pList head)
{
	struct staff_t* data;
	data = (struct staff_t*)malloc(sizeof(struct staff_t));
	data->acNO = 10000;
	//初始化经理的参数
	strcpy(data->acName, "manager");
	strcpy(data->psd, "666666");
	data->role = 1;
	//经理身份
	data->flag = 1;
	List_add(head, data);
	//添加到链表
	File_write(fp, head, sizeof(struct staff_t), 0);
    //写入文件
}