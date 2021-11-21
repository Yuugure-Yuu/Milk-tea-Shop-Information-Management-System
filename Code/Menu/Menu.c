/************************************************************************
* 文件名称： Menu.c

* 代码功能：
*     本文件实现关于菜谱的增删改查、推荐等功能。
*	  本文件只包含功能函数，无界面函数。

*************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "../Menu/Menu.h"



/************************************************************************
* 函数名称：void Menu_print(pList pt)
* 主要功能：
		   菜谱链表打印函数
* 形参说明：
*       pList pt    菜谱的结点
* 返回值：
*        无
*************************************************************************/

void Menu_print(pList pt)
{
	static int k = 0;
	struct Menu_t* pd;
	pd = (struct Menu_t*)(pt->pData);
	if (k == 0)
	{
		system("cls");
		printf("\n\n\t\t菜单在这里呀，菜单在这里~");
		printf("\n\n\t\t%-10s%-20s%-12s\n", "菜编号", "菜名", "价格");
		k = 1;
	}
	printf("\t\t%-10s%-20s%-12d\n", pd->num, pd->name, pd->price);
	if (pt->pNext == NULL)
		k = 0;
}

/************************************************************************
* 函数名称：void *Menu_add(void *data)
* 主要功能：
		   菜谱链表结点增加函数
* 形参说明：
*       void *data    菜谱最后一个结点的数据指针
* 返回值：
*        返回新增的数据指针
*************************************************************************/

void* Menu_add(void* data)
{
	char str[8] = { 0 };
	struct Menu_t* pData, * ps;
	pData = (struct Menu_t*)malloc(sizeof(struct Menu_t));
	ps = (struct Menu_t*)data;
	if (data == NULL)
	{
		system("cls");
		strcpy(pData->num, "10000");
	}
	else
	{
		Input_control(ps->num, '0', '9', 5, 2);
		strcpy(pData->num, ps->num);
	}
	printf("\n请输入要增加的菜名：");
	Input_control(pData->name, 0, 0, 14, 1);
	printf("请输入要增加的价格：");
	pData->price = Input_control(str, '0', '9', 2, 2);
	pData->food_nums = 5.0;
	printf("\n");
	return pData;
}

/************************************************************************
* 函数名称：int Menu_del(pList pL)
* 主要功能：
		   菜谱链表结点删除函数
* 形参说明：
*       pList pL    菜谱结点
* 返回值：
*        返回成功与否标志
*************************************************************************/

int Menu_del(pList pL)
{
	struct Menu_t* pt;
	static int k = 0;
	static int id = 0;
	static char str[8] = { 0 };
	if (k == 0)
	{
		printf("请输入要删除的菜编号(5位)：");
		Input_control(str, '0', '9', 5, 2);
		k = 1;
	}
	pt = (struct Menu_t*)(pL->pData);
	if (strcmp(pt->num, str) == 0)
	{
		memset(str, 0, sizeof(char));
		k = 0;
		return 1;
	}
	else
	{
		if (pL->pNext == NULL)
		{
			memset(str, 0, sizeof(char));
			k = 0;
		}
		return 0;
	}
}


/************************************************************************
* 函数名称：int Menu_update(pList pL)
* 主要功能：
		   菜谱链表结点更新函数
* 形参说明：
*       pList pL    菜谱结点
* 返回值：
*        返回成功与否标志
*************************************************************************/

int Menu_update(pList pL)
{
	struct Menu_t* pt;
	static int k = 0;
	static char str[8] = { 0 };
	if (k == 0)
	{
		printf("请输入要修改的菜编号(5位)：");
		Input_control(str, '0', '9', 5, 2);
		k = 1;
	}
	pt = (struct Menu_t*)(pL->pData);
	if (strcmp(pt->num, str) == 0)
	{
		memset(str, 0, sizeof(char));
		printf("\n重新输入菜名：");
		Input_control(pt->name, 0, 0, 14, 1);
		printf("重新输入价格：");
		pt->price = Input_control(str, '0', '9', 2, 2);
		memset(str, 0, sizeof(char));
		k = 0;
		return 1;
	}

	else
	{
		if (pL->pNext == NULL)
		{
			memset(str, 0, sizeof(char));
			k = 0;
		}
		return 0;
	}

}

/************************************************************************
* 函数名称：void Menu_search(pList head);
* 主要功能：
		   菜谱查询函数
* 形参说明：
*       pList head    菜谱的头指针
* 返回值：
*        无
*************************************************************************/

void Menu_search(pList head)
{
	char str[8] = { 0 };
	pList ps, pL;
	struct Menu_t* data;
	pL = List_init(NULL);
	ps = head->pNext;
	if (ps == NULL)
	{
		system("cls");
		printf("\n未存有菜谱信息，请先添加！\n");
		return;
	}
	system("cls");
	printf("\n\t\t\t(1) 全部");
	printf("\n\n\t\t\t(2) 编号");
	printf("\n\n\t\t\t请输入要查询的条件：");
	if (Input_control(NULL, '1', '2', 1, 2) == 1)
	{
		List_print(head, Menu_print);
		return;
	}
	printf("\n\n\t\t\t请输入要查询的菜编号(5位)：");
	Input_control(str, '0', '9', 5, 2);
	while (ps != NULL)
	{
		data = (struct Menu_t*)(ps->pData);
		if (strcmp(data->num, str) == 0)
		{
			List_add(pL, data);
			break;
		}
		ps = ps->pNext;
	}
	if (ps != NULL)
	{
		List_print(pL, Menu_print);
	}
	else
	{
		printf("\n\n输入有误，未查询到相关信息");
	}
}


/************************************************************************
* 函数名称：float popf（int price）
* 主要功能：
           计算推荐指数
* 形参说明：
*       int price 价格
* 返回值：
*        返回推荐指数
*************************************************************************/
float popf(int price)
{
	float pop;
	//pop即为“店长推荐”指数，用于给服务员推荐时作参考
	pop = 2.0/35.0*price+50.0/7.0;
	return pop;
}

