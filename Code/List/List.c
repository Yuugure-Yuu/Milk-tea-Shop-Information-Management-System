/************************************************************************
* �ļ����ƣ� List.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ���������������Ĺ��ܡ�
*	  ����Ŀ���ݾ���������ʵ�ִ洢��ͳ�ơ�ʹ�á�

*************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../List/List.h"


/************************************************************************
* �������ƣ�pList List_init(void *data)
* ��Ҫ���ܣ�
*    �������ʼ������
* �β�˵����
*    void *data     ������ʼ������������
* ����ֵ��
*       ������������ĵ�ַ
*************************************************************************/

pList List_init(void* data)
{
	pList head;
	head = (pList)malloc(sizeof(struct List));
	// ������ռ�
	if (head == NULL)
	{
		printf("Memory error.\n");
		return NULL;
	}
	memset(head, 0, sizeof(struct List));
	// ����
	head->pData = data;
	// ������ֵ
	return head;
}

/************************************************************************
* �������ƣ�void List_print(pList head,void (*pstr)(pList))
* ��Ҫ���ܣ�
*    �������ݴ�ӡ����
* �β�˵����
*    pList head        Ҫ��ӡ������ͷָ��
	 void (*pstr)(pList)   ���ݴ�ӡ�ĺ���ָ��
* ����ֵ��
*       ��
*************************************************************************/

void List_print(pList head, void (*pstr)(pList))
{
	pList pt;
	pt = head->pNext;
	while (pt != NULL)
	{
		pstr(pt);
		// ����ָ�룬��ͬ�������ݵĴ�ӡ
		pt = pt->pNext;
	}

}

/************************************************************************
* �������ƣ�void List_add(pList head,void *data)
* ��Ҫ���ܣ�
*    ��������Ӻ���
* �β�˵����
*    pList head       Ҫ��ӵ�����ͷָ��
	 void *data       Ҫ��ӵ�����
* ����ֵ��
*       ��
*************************************************************************/

void List_add(pList head, void* data)
{
	pList pNew, pt;
	pt = head;
	pNew = List_init(data);
	// ��ʼ��һ���½��
	while (pt->pNext != NULL)
		// ����ƫ�Ƶ������
	{
		pt = pt->pNext;
	}
	pt->pNext = pNew;
	// ��ĩβ��ӽ��
}

/************************************************************************
* �������ƣ�int  List_count(pList head)
* ��Ҫ���ܣ�
*    ����������������
* �β�˵����
*    pList head       Ҫ����������ͷָ��
* ����ֵ��
*       ���ؽ�����
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
* �������ƣ�void List_free(pList head);
* ��Ҫ���ܣ�
*    �����ͷź���
* �β�˵����
*    pList head       Ҫ�ͷŵ�����ͷָ��
* ����ֵ��
*       ��
*************************************************************************/

void List_free(pList head)
{
	pList ptr = head->pNext;
	while (ptr != NULL)
	{
		head->pNext = ptr->pNext;
		free(ptr->pData);
		// ���ͷ�������ռ�
		free(ptr);
		// ���ͷŽ��ռ�
		ptr = head->pNext;
	}
	free(head);
	// ����ͷ�ͷ���
}
