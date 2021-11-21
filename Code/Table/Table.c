/************************************************************************
* 文件名称： Table.c

* 代码功能：
*     本文件实现关于台桌的增删改查功能。

*************************************************************************/
#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include "../Table/Table.h"



/************************************************************************
* 函数名称：void Table_print(pList pt)
* 主要功能：
		   台桌信息打印函数
* 形参说明：
*       pList pt    台桌结点指针
* 返回值：
*        无
*************************************************************************/

void Table_print(pList pt)
{
	static int k = 0;
	char stat[4][10] = { "空闲","维修","占用","预定" };
	struct Table_t* pd;
	pd = (struct Table_t*)(pt->pData);
	if (k == 0)
	{
		system("cls");
		printf("\n\n\t\t((︶_︶))：对盏莫嫌，可绫罗绸缎，可粗茶淡饭");
		printf("\n\n\t\t%-10s%-14s%-13s\n", "台桌号", "状态", "位置");
		k = 1;
	}
	printf("\t\t%-10s%-14s%-13s\n", pd->acNo, stat[pd->state], pd->seat);
	if (pt->pNext == NULL)
		k = 0;
}

/************************************************************************
* 函数名称：void *Table_add(void *data)
* 主要功能：
		   台桌结点添加函数
* 形参说明：
*       void *data    台桌最后一个结点数据指针
* 返回值：
*        返回新增台桌数据指针
*************************************************************************/

void* Table_add(void* data)
{
	struct Table_t* pData, * ps;
	pData = (struct Table_t*)malloc(sizeof(struct Table_t));
	ps = (struct Table_t*)data;
	if (data == NULL)
	{
		system("cls");
		strcpy(pData->acNo, "100");
	}
	else
	{
		Input_control(ps->acNo, '0', '9', 4, 2);
		// 类型转换，并加1
		strcpy(pData->acNo, ps->acNo);
		// 把递增后的编号复制给新编号
	}
	printf("\n请输入要增加的台桌状态(0-空闲、1-维修、2-占用)：");
	pData->state = Input_control(NULL, '0', '2', 1, 2);
	printf("\n请输入要增加的台桌位置(中文)：");
	Input_control(pData->seat, 0, 0, 14, 1);
	return pData;
}

/************************************************************************
* 函数名称：int Table_remove(pList pL)
* 主要功能：
		   台桌假删除函数
* 形参说明：
*       pList pt    台桌结点指针
* 返回值：
*        返回成功与否标志
*************************************************************************/

int Table_remove(pList pL)
{
	struct Table_t* pt;
	static int k = 0;
	static char str[8] = { 0 };
	if (k == 0)
	{
		printf("请输入要删除的台桌编号(3位)：");
		Input_control(str, '0', '9', 3, 2);
		// str为要假删除的编号
		k = 1;
	}
	pt = (struct Table_t*)(pL->pData);
	if (strcmp(pt->acNo, str) == 0)
	{
		memset(str, 0, sizeof(char));
		pt->state = 1;
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
* 函数名称：int Table_update(pList pL)
* 主要功能：
		   台桌数据更新函数
* 形参说明：
*       pList pt    台桌结点指针
* 返回值：
*        返回成功与否标志
*************************************************************************/

int Table_update(pList pL)
{
	struct Table_t* pt;
	static int k = 0;
	static char str[8] = { 0 };

	if (k == 0)
	{
		printf("请输入要修改的台桌编号(3位)：");
		Input_control(str, '0', '9', 3, 2);
		k = 1;
	}
	pt = (struct Table_t*)(pL->pData);
	if (strcmp(pt->acNo, str) == 0)
	{
		memset(str, 0, sizeof(char));
		printf("\n重新输入状态(0-空闲、1-维修、2-占用)：");
		pt->state = Input_control(NULL, '0', '2', 1, 2);
		printf("\n重新输入位置(中文)：");
		Input_control(pt->seat, 0, 0, 14, 1);
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
* 函数名称：int Table_search(pList head,int n,int m)
* 主要功能：
		   台桌查询函数
* 形参说明：
*       pList head     台桌链表的头指针
		int n          台桌状态
		int m          台桌状态
* 返回值：
*        返回成功与否标志
*************************************************************************/

int Table_search(pList head, int n, int m)
{
	pList pL, ps;
	struct Table_t* data;
	pL = List_init(NULL);
	if (n > 2)
	{
		system("cls");
		printf("\n\t\t\t(1) 全部");
		printf("\n\n\t\t\t(2) 状态");
		printf("\n\n\t\t\t请输入要查询的条件：");
		if (Input_control(NULL, '1', '2', 1, 2) == 1)
		{
			List_print(head, Table_print);
			return 0;
		}
		else
			printf("\n\n\t\t\t请输入要查询的台桌状态(0-空闲、1-维修、2-占用)：");
		n = Input_control(NULL, '0', '2', 1, 2);
	}
	ps = head->pNext;
	if (ps == NULL)
	{
		system("cls");
		printf("\n未存有台桌信息，请先添加！\n");
		return 0;
	}
	while (ps != NULL)
	{
		data = (struct Table_t*)(ps->pData);
		if ((data->state == n) || (data->state == m))
		{
			List_add(pL, data);
			// 符合条件的加入新链表中
		}

		ps = ps->pNext;
	}

	if (pL->pNext != NULL)
	{
		List_print(pL, Table_print);
		// 打印符合条件的结点
		return 1;
	}
	else
	{
		printf("\n\n未查询到相关信息");
		return 0;
	}

}



