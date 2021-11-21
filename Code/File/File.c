/************************************************************************
* 文件名称： File.c

* 代码功能：
*     本文件实现关于文件操作的所有功能。

*************************************************************************/
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <windows.h>
#include "../File/File.h"
#include "../Input_Control/Input_Control.h"



/************************************************************************
* 函数名称：FILE *File_open(char *dirname)
* 主要功能：
*    文件夹创建，打开文件函数
* 形参说明：
*    char *dirname   文件名
* 返回值：
*    返回打开文件的指针
*************************************************************************/

FILE* File_open(char* dirname)
{
	FILE* fp;
	fp = fopen(dirname, "rb+");
	// 文件存在，用r+打开
	if (fp == NULL)
	{
		fp = fopen(dirname, "wb+");
		// 文件不存在，用w+打开
		if (fp == NULL)
		{
			printf("File open failed.\n");
			// 打开不成功，作提示
			// 一般会在路径出错时提示，可删
		}
	}

	return fp;
}

/************************************************************************
* 函数名称：int File_write(FILE *fp,pList head,int size,int n)
* 主要功能：
*    链表写入文件函数
* 形参说明：
*    FILE *fp         要写入文件的文件指针
	 pList head       要写入链表的头指针
	 int size         要写入的结构体大小
	 int n             要写入的起始位置
* 返回值：
*    写入的数据个数
*************************************************************************/

int File_write(FILE* fp, pList head, int size, int n)
{
	pList pt;
	int count = 0;
	fseek(fp, 0, n);
	// 文件指针偏移到n指定的位置
	pt = head->pNext;
	while (pt != NULL)
	{
		count++;
		fwrite(pt->pData, size, 1, fp);
		// 从n指定的位置写入链表
		fflush(fp);
		// 更新文件
		pt = pt->pNext;
	}
	return count;
}


/************************************************************************
* 函数名称：pList File_read(FILE *fp,int size)
* 主要功能：
*    文件数据读出函数
* 形参说明：
*    FILE *fp    要读出的文件指针
	 int size    要读出的结构体大小
* 返回值：
*    读出的链表头指针
*************************************************************************/

pList File_read(FILE* fp, int size)
{
	pList head;
	int flag;
	void* p1;
	fseek(fp, 0, SEEK_SET);
	//定位到文件头
	head = List_init(NULL);
	p1 = malloc(size);
	flag = fread(p1, size, 1, fp);
	// flag反映是否成功读出
	while (flag)
	{
		List_add(head, p1);
		p1 = malloc(size);
		// 每次开辟一个新空间，存放每次读出来的数据
		flag = fread(p1, size, 1, fp);
	}
	return head;
	//返回读出链表的头指针
}

/************************************************************************
* 函数名称：void File_remove(FILE *fp,pList head,int size,int (*p)(pList))
* 主要功能：
*    文件数据删除函数，员工和台桌的假删除
* 形参说明：
*    FILE *fp      要删除的文件指针
	 pList head    要删除的头结点
	 int size      要删除的结构体大小
	 int (*p)(pList)   删除的函数指针
* 返回值：
*    无
*************************************************************************/

void File_remove(FILE* fp, pList head, int size, int (*prem)(pList))
{

	pList pt;
	int count;
	count = 0;
	pt = head->pNext;
	while (pt != NULL)
	{
		count++;
		// 记录结点的位置
		if (prem(pt))
			// 查询要操作的结点数据
			break;
		pt = pt->pNext;
	}

	if (pt == NULL)
		printf("\n未查到此条信息");

	else
	{

		printf("\n是否确认删除(y)是、(n)不:");
		if (Input_control(NULL, 0, 0, 1, 1) == 'y')
			// 提示是否确定删除
		{
			fseek(fp, (count - 1) * size, SEEK_SET);
			// 定位到要假删除的结点位置
			fwrite(pt->pData, size, 1, fp);
			// 覆盖旧数据
			fflush(fp);
			printf("\n删除成功");
		}
		else
			printf("\n删除失败");
	}

	printf("，按任意键继续...");
	getch();
}

/************************************************************************
* 函数名称：void File_add(FILE *fp,pList head,int size,void *(*pstr)(void *data))
* 主要功能：
*    文件数据增加函数
* 形参说明：
*    FILE *fp      要增加的文件指针
	 pList head    要增加的头结点
	 int size      要增加的结构体大小
	 void *(*pstr)(void *data)   数据增加的函数指针，返回新增数据
* 返回值：
*    无
*************************************************************************/

void File_add(FILE* fp, pList head, int size, void* (*padd)(void* data))
//添加一个成员
{
	pList pNew, pt;
	pt = head;
	while (pt->pNext != NULL)
	{
		pt = pt->pNext;
	}
	pNew = List_init(padd(pt->pData));
	printf("是否确认增加(y)是、(n)不:");
	if (Input_control(NULL, 0, 0, 1, 1) == 'y')
		// 提示是否确定增加
	{
		pt->pNext = pNew;
		fseek(fp, 0, SEEK_END);
		//定位到文件末尾添加数据  
		fwrite(pNew->pData, size, 1, fp);
		// 加入新增的数据
		fflush(fp);
		printf("\n增加成功");
	}
	else
		printf("\n增加失败");

	printf("，按任意键继续...");
	getch();
}

/************************************************************************
* 函数名称：void File_del(FILE *fp,char dir[],pList head,int size,int (*pdel)(pList))
* 主要功能：
*    文件数据删除函数，菜谱真删除
* 形参说明：
*    FILE *fp      要删除的文件指针
	 char dir[]    文件路径
	 pList head    要删除的头结点
	 int size      要删除的结构体大小
	 int (*pdel)(pList)   删除的函数指针
* 返回值：
*    无
*************************************************************************/

void File_del(FILE* fp, char dir[], pList head, int size, int (*pdel)(pList))
{

	pList pt, ps;
	ps = head;
	pt = head->pNext;
	while (pt != NULL)
	{
		if (pdel(pt))
		{

			printf("\n是否确认删除(y)是、(n)不:");
			if (Input_control(NULL, 0, 0, 1, 1) == 'y')
			{
				ps->pNext = pt->pNext;
				free(pt);
				// 释放要删除的结点
				fclose(fp);
				fp = fopen(dir, "w+");
				// 已W+方式重新打开文件
				File_write(fp, head, size, 0);
				// 重新把链表写入文件
				printf("\n删除成功");
			}
			else
				printf("\n删除失败");
			break;
		}
		ps = pt;
		pt = pt->pNext;
	}
	if (pt == NULL)
		printf("\n未找到此条信息");
	printf("，按任意键继续...");
	getch();
}

/************************************************************************
* 函数名称：void File_updata(FILE *fp,pList head,int size,int (*p)(pList))
* 主要功能：
*    文件数据修改函数
* 形参说明：
*    FILE *fp     要修改的文件指针
	 pList head   要修改的头结点
	 int size     要修改的结构体大小
	 int (*p)(pList)  修改的函数指针
* 返回值：
*    无
*************************************************************************/

void File_updata(FILE* fp, pList head, int size, int (*p)(pList))
//在链表中修改信息，同时更新到文件中
{
	pList pt;
	int count;
	count = 0;
	pt = head->pNext;
	while (pt != NULL)
	{
		count++;
		// 记录要更新的数据在链表中的位置
		if (p(pt))
			// 查找要更新的数据
		{
			break;
		}
		pt = pt->pNext;
	}

	if (pt == NULL)
		printf("\n未查到此条信息");

	else
	{
		printf("\n是否确认修改(y)是、(n)不:");
		if (Input_control(NULL, 0, 0, 1, 1) == 'y')
		{
			fseek(fp, (count - 1) * size, SEEK_SET);
			// 定位到要更新的结点位置
			fwrite(pt->pData, size, 1, fp);
			// 覆盖旧数据
			fflush(fp);
			printf("\n修改成功");
		}
		else
			printf("\n修改失败");
	}
	printf("，按任意键继续...");
	getch();
}

