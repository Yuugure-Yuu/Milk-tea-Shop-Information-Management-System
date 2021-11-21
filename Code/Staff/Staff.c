/************************************************************************
* �ļ����ƣ� Staff.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ���Ա������ɾ��Ĺ��ܡ�

*************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>
#include "../Staff/Staff.h"
#include "../Input_Control/Input_Control.h"



/************************************************************************
* �������ƣ�void staff_print(pList pt)
* ����������
		   Ա����Ϣ��ӡ����
* ����˵����
*       pList pt    Ա�����ָ��
* ����ֵ��
*        ��
*************************************************************************/

void staff_print(pList pt)
{
	static int k = 0;
	char role[3][10] = { "����Ա","����","����Ա" };
	struct staff_t* pd;
	pd = (struct staff_t*)(pt->pData);
	if (k == 0)
	{
		system("cls");
		printf("\n\n\t\t-=��(((��3��)��������~");
		printf("\n\n\t\t%-10s%-12s%-12s%-10s\n", "���", "�û���", "��ɫ", "״̬");
		k = 1;
	}
	printf("\t\t%-10d%-12s%-12s%-10s\n", pd->acNO, pd->acName, role[pd->role],
		pd->flag > 0 ? "��ְ" : "��ְ");
	if (pt->pNext == NULL)
		k = 0;
}

/************************************************************************
* �������ƣ�void *staff_add(void *data)
* ����������
		   Ա�����Ӻ���
* ����˵����
*       void *data        Ա����������һ���������ָ��
* ����ֵ��
*        ��������������ָ��
*************************************************************************/

void* staff_add(void* data)
{
	struct staff_t* pData, * ps;
	char str[8] = { 0 };
	pData = (struct staff_t*)malloc(sizeof(struct staff_t));
	// ����һ�����ݿռ�
	ps = (struct staff_t*)data;
	pData->acNO = (ps->acNO) + 1;
	// Ա����Ϊ���ͣ�ֱ�Ӽ�1
	printf("\n������Ҫ���ӵ��û���(10λ��)��");
	Input_control(pData->acName, 0, 0, 10, 1);
	while (1)
	{
		memset(pData->psd, 0, sizeof(char));
		printf("\n������Ҫ���ӵ�����(6λ)��");
		Input_control(pData->psd, '0', '9', 6, 2);
		printf("\n�ٴ�ȷ����������(6λ)��");
		Input_control(str, '0', '9', 6, 2);
		if (strcmp(pData->psd, str) == 0)
			// ��֤�������������һ����
		{
			break;
		}
		else
		{
			printf("\n���벻һ�£����������룬�����������...");
			memset(str, 0, sizeof(char));
			getch();
			printf("\n");
		}

	}
	printf("\n������Ҫ���ӵĽ�ɫ(0-����Ա��1-����2-����Ա)��");
	pData->role = Input_control(NULL, '0', '2', 1, 2);
	printf("\n������Ҫ���ӵ�״̬(0-��ְ��1-��ְ):");
	pData->flag = Input_control(NULL, '0', '1', 1, 2);
	printf("\n");
	return pData;
}

/************************************************************************
* �������ƣ�int staff_update(pList pL)
* ����������
		   Ա����Ϣ���º���
* ����˵����
*      pList pL       Ա������Ľ��ָ��
* ����ֵ��
*        ���سɹ�����־
*************************************************************************/

int staff_remove(pList pL)
{
	struct staff_t* pt;
	static int k = 0;
	static int id = 0;
	static char str[8] = { 0 };
	if (k == 0)
		// ������Ϣ��־
	{
		printf("������Ҫɾ����Ա����ţ�");
		id = Input_control(str, '0', '9', 4, 2);
		k = 1;
		memset(str, 0, sizeof(char));
	}
	pt = (struct staff_t*)(pL->pData);
	if (pt->acNO == id)
	{
		pt->flag = 0;
		// Ա��״̬��Ϊ��ְ����Ϊɾ��
		k = 0;

		return 1;
		// ɾ���ɹ�
	}
	else
	{
		if (pL->pNext == NULL)
			k = 0;
		return 0;
		// ɾ��ʧ��
	}
}

/************************************************************************
* �������ƣ�int staff_update(pList pL)
* ����������
		   Ա����Ϣ���º���
* ����˵����
*      pList pL       Ա������Ľ��ָ��
* ����ֵ��
*        ���سɹ�����־
*************************************************************************/

int staff_update(pList pL)
{
	struct staff_t* pt;
	static int k = 0;
	static int id = 0;
	static char str[8] = { 0 };
	if (k == 0)
	{
		printf("������Ҫ�޸ĵ�Ա�����(5λ)��");
		id = Input_control(str, '0', '9', 5, 2);
		k = 1;
		memset(str, 0, sizeof(char));
	}
	pt = (struct staff_t*)(pL->pData);
	if (pt->acNO == id)
	{
		printf("\n��������Ա���û�����");
		Input_control(pt->acName, 0, 0, 10, 1);
		while (1)
		{
			memset(pt->psd, 0, sizeof(char));
			printf("\n���������û����룺");
			Input_control(pt->psd, '0', '9', 6, 2);
			printf("\n�ٴ�ȷ���������룺");
			Input_control(str, '0', '9', 6, 2);
			if (strcmp(pt->psd, str) == 0)
			{
				memset(str, 0, sizeof(char));
				break;
			}
			else
			{
				printf("\n���벻һ�£����������룬�����������...");
				memset(str, 0, sizeof(char));
				getch();
				printf("\n");
			}
		}
		printf("\n��������Ա����ɫ(0-����Ա��1-����2-����Ա)��");
		pt->role = Input_control(NULL, '0', '2', 1, 2);
		printf("\n��������Ա��״̬(0-��ְ��1-��ְ)��");
		pt->flag = Input_control(NULL, '0', '1', 1, 2);
		k = 0;
		return 1;
		// �޸ĳɹ���־		
	}
	else
	{
		if (pL->pNext == NULL)
		{
			k = 0;
		}
		return 0;
		// �޸�ʧ��
	}

}

/************************************************************************
* �������ƣ�void staff_search(pList head)
* ����������
		   Ա����ѯ����
* ����˵����
*      pList head       Ա�������ͷָ��
* ����ֵ��
*        ��
*************************************************************************/

void staff_search(pList head)
{
	int n;
	pList pL, ps;
	void (*pf[3])(int n, pList ps, pList pL) = { staff_search_flag,staff_search_flag,staff_search_acNO };
	system("cls");
	pL = List_init(NULL);
	printf("\n\n\t\t\t(1) ȫ��\n\n\t\t\t(2) ��ְ\n\n\t\t\t(3) ��ְ\n\n\t\t\t(4) ���");
	printf("\n\n\t\t\t������Ҫ��ѯ������:");
	n = Input_control(NULL, '1', '4', 1, 2);
	if (n == 1)
		List_print(head, staff_print);
	else
	{
		ps = head->pNext;
		while (ps != NULL)
		{
			pf[n - 2](n - 2, ps, pL);
			ps = ps->pNext;
		}
	}

}

/************************************************************************
* �������ƣ�void staff_search_flag(int n,pList ps,pList pL);
* ����������
		   ��ְ����ְԱ���Ĳ�ѯ����
* ����˵����
*      int n        Ա��״̬
	   pList ps     Ա�����ָ��
	   pList pL     �����������ͷָ��
* ����ֵ��
*        ��
*************************************************************************/

void staff_search_flag(int n, pList ps, pList pL)
{
	struct staff_t* pt;
	pt = (struct staff_t*)(ps->pData);
	if (pt->flag == n)
	{
		List_add(pL, pt);
		// ���������Ľ����ӽ�����
	}
	if (ps->pNext == NULL)
	{
		if (pL->pNext != NULL)
		{
			List_print(pL, staff_print);
			if (n == 1)
				// �ж�״̬
			{
				printf("��ְ������%d��", List_count(pL));
			}
			else
				printf("��ְ������%d��", List_count(pL));
		}
		else
			printf("\n\nδ��ѯ�������Ϣ");
	}

}

/************************************************************************
* �������ƣ�void staff_search_acNO(int n,pList ps,pList pL);
* ����������
		   ���ݱ�Ų�ѯԱ���ĺ���
* ����˵����
*      int n        Ա��״̬
	   pList ps     Ա�����ָ��
	   pList pL     �����������ͷָ��
* ����ֵ��
*        ��
*************************************************************************/

void staff_search_acNO(int n, pList ps, pList pL)
{
	static int id, k = 0;
	struct staff_t* pt;
	static char str[8] = { 0 };
	pt = (struct staff_t*)(ps->pData);
	if (k == 0)
	{
		printf("\n\n\t\t\t������Ҫ��ѯ�ı��(4λ)��");
		id = Input_control(str, '0', '9', 4, 2);
		k = 1;
		memset(str, 0, sizeof(char));
	}
	if (pt->acNO == id)
	{
		List_add(pL, pt);
	}
	if (ps->pNext == NULL)
	{
		if (pL->pNext != NULL)
		{
			List_print(pL, staff_print);
		}
		else
			printf("\n\n��������δ��ѯ�������Ϣ");
		k = 0;
	}

}