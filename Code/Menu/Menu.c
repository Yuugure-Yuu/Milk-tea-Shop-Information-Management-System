/************************************************************************
* �ļ����ƣ� Menu.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ��ڲ��׵���ɾ�Ĳ顢�Ƽ��ȹ��ܡ�
*	  ���ļ�ֻ�������ܺ������޽��溯����

*************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "../Menu/Menu.h"



/************************************************************************
* �������ƣ�void Menu_print(pList pt)
* ��Ҫ���ܣ�
		   ���������ӡ����
* �β�˵����
*       pList pt    ���׵Ľ��
* ����ֵ��
*        ��
*************************************************************************/

void Menu_print(pList pt)
{
	static int k = 0;
	struct Menu_t* pd;
	pd = (struct Menu_t*)(pt->pData);
	if (k == 0)
	{
		system("cls");
		printf("\n\n\t\t�˵�������ѽ���˵�������~");
		printf("\n\n\t\t%-10s%-20s%-12s\n", "�˱��", "����", "�۸�");
		k = 1;
	}
	printf("\t\t%-10s%-20s%-12d\n", pd->num, pd->name, pd->price);
	if (pt->pNext == NULL)
		k = 0;
}

/************************************************************************
* �������ƣ�void *Menu_add(void *data)
* ��Ҫ���ܣ�
		   �������������Ӻ���
* �β�˵����
*       void *data    �������һ����������ָ��
* ����ֵ��
*        ��������������ָ��
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
	printf("\n������Ҫ���ӵĲ�����");
	Input_control(pData->name, 0, 0, 14, 1);
	printf("������Ҫ���ӵļ۸�");
	pData->price = Input_control(str, '0', '9', 2, 2);
	pData->food_nums = 5.0;
	printf("\n");
	return pData;
}

/************************************************************************
* �������ƣ�int Menu_del(pList pL)
* ��Ҫ���ܣ�
		   ����������ɾ������
* �β�˵����
*       pList pL    ���׽��
* ����ֵ��
*        ���سɹ�����־
*************************************************************************/

int Menu_del(pList pL)
{
	struct Menu_t* pt;
	static int k = 0;
	static int id = 0;
	static char str[8] = { 0 };
	if (k == 0)
	{
		printf("������Ҫɾ���Ĳ˱��(5λ)��");
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
* �������ƣ�int Menu_update(pList pL)
* ��Ҫ���ܣ�
		   ������������º���
* �β�˵����
*       pList pL    ���׽��
* ����ֵ��
*        ���سɹ�����־
*************************************************************************/

int Menu_update(pList pL)
{
	struct Menu_t* pt;
	static int k = 0;
	static char str[8] = { 0 };
	if (k == 0)
	{
		printf("������Ҫ�޸ĵĲ˱��(5λ)��");
		Input_control(str, '0', '9', 5, 2);
		k = 1;
	}
	pt = (struct Menu_t*)(pL->pData);
	if (strcmp(pt->num, str) == 0)
	{
		memset(str, 0, sizeof(char));
		printf("\n�������������");
		Input_control(pt->name, 0, 0, 14, 1);
		printf("��������۸�");
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
* �������ƣ�void Menu_search(pList head);
* ��Ҫ���ܣ�
		   ���ײ�ѯ����
* �β�˵����
*       pList head    ���׵�ͷָ��
* ����ֵ��
*        ��
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
		printf("\nδ���в�����Ϣ��������ӣ�\n");
		return;
	}
	system("cls");
	printf("\n\t\t\t(1) ȫ��");
	printf("\n\n\t\t\t(2) ���");
	printf("\n\n\t\t\t������Ҫ��ѯ��������");
	if (Input_control(NULL, '1', '2', 1, 2) == 1)
	{
		List_print(head, Menu_print);
		return;
	}
	printf("\n\n\t\t\t������Ҫ��ѯ�Ĳ˱��(5λ)��");
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
		printf("\n\n��������δ��ѯ�������Ϣ");
	}
}


/************************************************************************
* �������ƣ�float popf��int price��
* ��Ҫ���ܣ�
           �����Ƽ�ָ��
* �β�˵����
*       int price �۸�
* ����ֵ��
*        �����Ƽ�ָ��
*************************************************************************/
float popf(int price)
{
	float pop;
	//pop��Ϊ���곤�Ƽ���ָ�������ڸ�����Ա�Ƽ�ʱ���ο�
	pop = 2.0/35.0*price+50.0/7.0;
	return pop;
}

