/************************************************************************
* 文件名称： List.c

* 代码功能：
*     本文件实现关于链表基本操作的功能。
*	  本项目数据均利用链表实现存储、统计、使用。

*************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../List/List.h"


/************************************************************************
* 函数名称：pList List_init(void *data)
* 主要功能：
*    链表结点初始化函数
* 形参说明：
*    void *data     传给初始化结点的数据域
* 返回值：
*       返回新申请结点的地址
*************************************************************************/

pList List_init(void* data)
{
	pList head;
	head = (pList)malloc(sizeof(struct List));
	// 申请结点空间
	if (head == NULL)
	{
		printf("Memory error.\n");
		return NULL;
	}
	memset(head, 0, sizeof(struct List));
	// 清零
	head->pData = data;
	// 数据域赋值
	return head;
}

/************************************************************************
* 函数名称：void List_print(pList head,void (*pstr)(pList))
* 主要功能：
*    链表数据打印函数
* 形参说明：
*    pList head        要打印的链表头指针
	 void (*pstr)(pList)   数据打印的函数指针
* 返回值：
*       无
*************************************************************************/

void List_print(pList head, void (*pstr)(pList))
{
	pList pt;
	pt = head->pNext;
	while (pt != NULL)
	{
		pstr(pt);
		// 函数指针，不同类型数据的打印
		pt = pt->pNext;
	}

}

/************************************************************************
* 函数名称：void List_add(pList head,void *data)
* 主要功能：
*    链表结点添加函数
* 形参说明：
*    pList head       要添加的链表头指针
	 void *data       要添加的数据
* 返回值：
*       无
*************************************************************************/

void List_add(pList head, void* data)
{
	pList pNew, pt;
	pt = head;
	pNew = List_init(data);
	// 初始化一个新结点
	while (pt->pNext != NULL)
		// 链表偏移到最后面
	{
		pt = pt->pNext;
	}
	pt->pNext = pNew;
	// 往末尾添加结点
}

/************************************************************************
* 函数名称：int  List_count(pList head)
* 主要功能：
*    链表结点数计数函数
* 形参说明：
*    pList head       要计数的链表头指针
* 返回值：
*       返回结点个数
*************************************************************************/

int  List_count(pList head)
{
	pList p1;
	int nCount = 0;
	p1 = head->pNext;
	while (p1 != NULL)
	{
		nCount++;
		p1 = p1->pNext;
	}
	return nCount;
}

/************************************************************************
* 函数名称：void List_free(pList head);
* 主要功能：
*    链表释放函数
* 形参说明：
*    pList head       要释放的链表头指针
* 返回值：
*       无
*************************************************************************/

void List_free(pList head)
{
	pList ptr = head->pNext;
	while (ptr != NULL)
	{
		head->pNext = ptr->pNext;
		free(ptr->pData);
		// 先释放数据域空间
		free(ptr);
		// 再释放结点空间
		ptr = head->pNext;
	}
	free(head);
	// 最后释放头结点
}
