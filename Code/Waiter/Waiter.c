/************************************************************************
* �ļ����ƣ� Waiter.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ��ڷ���Ա�ճ������Ĺ��ܡ�

*************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "../Waiter/Waiter.h"

extern  char acName[10];
//����Ա��¼��

/************************************************************************
* �������ƣ�int Ui_waiter()
* ��Ҫ���ܣ�
		   ����Ա���湦�ܺ���
* �β�˵����
*       ��
* ����ֵ��
*        һ���������֣������ж���ע�������˳�
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
		printf("\n\n\t\t\t(��3��)�ŷ���ԱС����ѽ~~");
		printf("\n\n\n\t\t\t~~���ܶ������￩~~\n\n");
		printf("\t\t\t1������\n\n");
		printf("\t\t\t2�����\n\n");
		printf("\t\t\t3������\n\n");
		printf("\t\t\t4��Ӫҵ���ѯ\n\n");
		printf("\t\t\t5������/δ�򵥲�ѯ\n\n");
		printf("\t\t\t6���곤�Ƽ�\n\n");
		printf("\t\t\t7��ע��\n\n");
		printf("\t\t\t8���˳�\n\n");
		printf("\t\t\t��ѡ�����ܰȣ�");
		n = Input_control(NULL, '1', '8', 1, 2);
		if (n > 0 && n < 7)
		{
			pst[n - 1](pTable);
			//�ֱ�����Open_desk��Order_dishes��Settle_Accounts��turnover_search��Order_search��printPopularFood��������
		}
		else if (n == 7)
			return 0;
		else if (n == 8)
			return 1;
	}
}

/************************************************************************
* �������ƣ�void Open_desk(pList pTable)
* ��Ҫ���ܣ�
		   �������湦�ܺ���
* �β�˵����
*       pList pTable   ̨�������ͷָ��
* ����ֵ��
*        ��
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
		// ��ӡ���к�Ԥ����̨��
		if (n == 0)
		{
			printf("���޿������ӣ�������˼������...�����������...");
			getch();
			return;
		}
		printf("������Ҫ������̨���ţ�");
		Input_control(str, '0', '9', 3, 2);
		// str���Ҫ������̨����
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
			printf("\n̨��������򲻿���,���������룬�����������...");
			getch();
		}
		else
			break;
	}

	if (ps->state == 3)
		// ��ΪԤ��״̬��ֱ����תΪ��˽���
	{
		ps->state = 2;
		//ռ�ã�ת����˽���
		File_write(fp, pTable, sizeof(struct Table_t), 0);
		// ����̨���ļ�
		printf("\n�����ɹ��������������...");
		getch();
		Order_dishes(pTable);
		// ��ת����˽���
		return;
	}
	printf("\n�Ƿ����Ͽ�ʼ���(y)ȷ����(n)���أ�");
	if (Input_control(NULL, 0, 0, 1, 1) != 'y')
	{
		ps->state = 3;
		//Ԥ��״̬
		File_write(fp, pTable, sizeof(struct Table_t), 0);
		printf("\nԤ���ɹ��������������...");
		getch();
	}
	else
	{
		ps->state = 2;
		//ռ�ã�ת����˽���
		File_write(fp, pTable, sizeof(struct Table_t), 0);
		printf("\n�����ɹ��������������...");
		getch();
		Order_dishes(pTable);
		return;
	}
}

/************************************************************************
* �������ƣ�void Order_dishes(pList pTable)
* ��Ҫ���ܣ�
		   ��˽��湦�ܺ���
* �β�˵����
*       pList pTable   ̨�������ͷָ��
* ����ֵ��
*        ��
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
	// �굥�����·��

	fd = File_open("../../Code/Data/Menu.txt");
	pMenu = File_read(fd, sizeof(struct Menu_t));
	fd = File_open("../../Code/Data/Cache/Order.txt");
	pOrder = File_read(fd, sizeof(struct Order_t));

	while (1)
	{
		system("cls");
		n = Table_search(pTable, 2, 4);
		// �ж��Ƿ��п�������
		if (n == 0)
		{
			printf("�����޿������ӣ������������...");
			getch();
			return;
		}
		printf("������Ҫ��˵�̨���ţ�");
		Input_control(str, '0', '9', 3, 2);
		strcat(tabpath, str);
		strcat(tabpath, txt);
		// ��ȡ�굥��·��
		pt = pOrder->pNext;
		while (pt)
		{
			pdata = (struct Order_t*)(pt->pData);
			if (strcmp(pdata->tablenum, str) == 0)
				// �жϵ�ǰδ�򶩵����Ƿ���ڴ�̨���Ķ���
			{
				pNew = pdata;
				fd = File_open(tabpath);
				pTitle = File_read(fd, sizeof(struct Title_t));
				break;
			}
			pt = pt->pNext;
		}

		if (pt == NULL)
			// δ�򶩵�����������̨���Ķ���
		{
			pt = pTable->pNext;
			while (pt)
			{
				if (strcmp(((struct Table_t*)(pt->pData))->acNo, str) == 0)
				{
					if (((struct Table_t*)(pt->pData))->state == 2)
					{
						pNew = Order_init(str);
						// ��ʼ��һ���������
						List_add(pOrder, pNew);
						File_write(fd, pOrder, sizeof(struct Order_t), 0);
						// д��δ�򶩵��ļ�
						fd = fopen(tabpath, "w+");
						// ��w+��ʽ���굥�ļ������ڿ�ʼ���
						pTitle = File_read(fd, sizeof(struct Title_t));
						break;
					}
					else if (((struct Table_t*)(pt->pData))->state == 0)
					{
						printf("\n������Ϊ�������ȿ������ܵ�ˣ��Ƿ�����(y)������(n)���أ�");
						if (Input_control(NULL, 0, 0, 1, 1) == 'y')
							Open_desk(pTable);
						// ��ת����������
						return;
					}

				}
				pt = pt->pNext;

			}
			if (pt == NULL)
			{
				memset(str, 0, sizeof(char));
				strcpy(tabpath, "../../Code/Data/Cache/");
				printf("\n���������������ߴ���ά��״̬�����������룬�����������...");
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
	// ��ȡ���׵ĸ���
	while (1)
	{
		JR_EmptyRaw(count1 + 3, count1 + 12);
		// ��ղ�������ļ�����Ϣ
		JR_SetCursor(count1 + 3, 0);
		printf("\t\t(1)�����\n");
		printf("\t\t(2)���˲�\n");
		printf("\t\t(3)������\n");
		printf("\t\t������Ҫ�����Ĺ��ܣ�");
		n = Input_control(NULL, '1', '3', 1, 2);
		switch (n)
		{
		case 1:
		{
			Order_add(count1, pNew, pTitle, pOrder, pMenu, tabpath);
			// �Ӳ˹��ܺ���
			break;
		}
		case 2:
		{
			Order_del(count1, pNew, pTitle, pMenu, pOrder, tabpath);
			// ���˹��ܺ���
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
* �������ƣ�void turnover_search(pList pTable)
* ��Ҫ���ܣ�
		   Ӫҵ���ѯ���湦�ܺ���
* �β�˵����
*       pList pTable   ̨�������ͷָ��
* ����ֵ��
*        ��
*************************************************************************/

void turnover_search(pList  pTable)
{
	FILE* fp;
	pList pOrder, pt;
	struct Order_t* data;
	long* stardate, * enddate;
	long ordernum;
	// ������
	int a, b, c;
	// ������ӡ������
	long money = 0;
	// ��Ӫҵ��
	stardate = (long*)malloc(sizeof(long));
	// ��ʼ����
	enddate = (long*)malloc(sizeof(long));
	// ��������
	fp = File_open("../../Code/Data/Order/Order.txt");
	pOrder = File_read(fp, sizeof(struct Order_t));
	// �������򶩵�����

	system("cls");
	printf("\n\t\t\t(1):�����ѯ\n");
	printf("\n\t\t\t(2):��ʷ��ѯ\n");
	printf("\n\t\t\t������Ҫѡ��Ĺ��ܣ�");
	if (Input_control(NULL, '1', '2', 1, 2) == 1)
	{
		system("cls");
		*stardate = Ordernum_get(NULL, NULL);
		// ��ȡ��ǰϵͳ����
		*enddate = *stardate;
	}
	else
	{
		system("cls");
		printf("\n\t\t\t(1):������ˮ\n");
		printf("\n\t\t\t(2):ָ������\n");
		printf("\n\t\t\t������Ҫѡ��Ĺ��ܣ�");
		if (Input_control(NULL, '1', '2', 1, 2) == 2)
		{
			Orderdate_input(stardate, enddate);
			// ���뿪ʼ�ͽ�������
			printf("\n");
		}
		else
		{
			system("cls");
			*stardate = Ordernum_get(NULL, "month");
			*enddate = Ordernum_get(NULL, NULL);
		}
	}

	printf("\t\t%-16s%-18s%-11s\n", "������", "ʱ��", "���");
	pt = pOrder->pNext;
	while (pt)
	{
		data = (struct Order_t*)(pt->pData);
		sscanf(data->ordernum, "%8ld", &ordernum);
		// �ַ���ת���ɳ�����
		if ((strcmp(data->acname, acName) == 0) && ((ordernum <= *enddate) && (ordernum >= *stardate)))//
		{
			money = money + (data->money);
			// Ӫҵ���ۼ�
			sscanf(data->ordernum, "%4d%2d%2d", &a, &b, &c);
			//�ֱ�ȡ��������
			printf("\t\t%-16s%d%s%2d%s%2d%-6s%s%d\n", data->ordernum, a, "��", b, "��", c, "��", "��", data->money);
		}
		pt = pt->pNext;
	}
	int x, month, y;
	char time[10] = { 0 };
	Ordernum_get(time, NULL);
	sscanf(time, "%4d%2d%2d", &x, &month, &y);
	printf("\n\t\t\t�����·�Ϊ��%2d��\n\n", month);
	printf("\n\t\tӪҵ���ܶ��%ld\n", money);
	List_free(pOrder);
	printf("\n\t\t�����������...");
	getch();
}

/************************************************************************
* �������ƣ�void Order_search(pList pTable)
* ��Ҫ���ܣ�
		   ����/δ�򵥲�ѯ���湦�ܺ���
* �β�˵����
*       pList pTable   ̨�������ͷָ��
* ����ֵ��
*        ��
*************************************************************************/

void Order_search(pList  pTable)
{
	int n;
	FILE* fp;
	pList pOrder;
	fp = File_open("../../Code/Data/Cache/Order.txt");
	pOrder = File_read(fp, sizeof(struct Order_t));
	// ����δ������
	while (1)
	{
		system("cls");
		printf("\n\n\n\t\t\t����/δ�򵥲�ѯ����\n\n");
		printf("\t\t\t1��δ�򵥲�ѯ\n\n");
		printf("\t\t\t2�����򵥲�ѯ\n\n");
		printf("\t\t\t3���˳�\n\n");
		printf("\t\t\t����������Ҫѡ��Ĺ��ܣ�");
		n = Input_control(NULL, '1', '3', 1, 2);
		switch (n)
		{
		case 1:
			Order_search_unbuy(pOrder);
			// δ�򵥲�ѯ���� 
			getch();
			break;
		case 2:
			Order_search_buy();
			// ���򵥲�ѯ����
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
	// �ͷ�����
}

/************************************************************************
* �������ƣ�Settle_Accounts(pList pTable);
* ��Ҫ���ܣ�
		   ̨���������˲�ѯ���湦�ܺ���
* �β�˵����
*       pList pTable   ̨�������ͷָ��
* ����ֵ��
*        ��
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
	// δ���굥·��
	fp = File_open("../../Code/Data/Cache/Order.txt");
	// ��δ�򶩵��ļ�
	pOrder = File_read(fp, sizeof(struct Order_t));
	while (1)
	{
		system("cls");
		pt = pOrder->pNext;
		if (pt == NULL)
			//�жϵ�ǰ�Ƿ���δ�򶩵�
		{
			printf("\nĿǰû��δ�򶩵��������������...");
			return;
		}
		printf("\t\t%12s%12s%11s%11s\n", "������", "̨����", "���", "״̬");
		while (pt)
		{
			data = (struct Order_t*)(pt->pData);
			printf("\t\t%12s%12s%11d%11s\n", data->ordernum, data->tablenum, data->money, "δ֧��");
			// ��ӡ����δ�ᶩ����Ϣ
			pt = pt->pNext;
		}
		printf("\n������Ҫ���˵�̨����(3λ)��");
		Input_control(str, '0', '9', 3, 2);
		ps = pOrder;
		pt = pOrder->pNext;
		while (pt)
		{
			data = (struct Order_t*)(pt->pData);
			if (strcmp(data->tablenum, str) == 0)
				// �ҳ�Ҫ���˵Ķ������
				break;
			ps = pt;
			pt = pt->pNext;
		}
		if (pt == NULL)
			// δ�ҵ�����������ʾ
		{
			printf("\n\n̨�����޶��������󣬰�<Esc>�����ء��������������룺");
			if (getch() == 27)
				return;
			memset(str, 0, sizeof(char));
		}
		else
			break;
	}
	strcat(tabpath, str);
	// ��ȡ�굥��·��
	strcat(tabpath, txt);
	fp = File_open(tabpath);
	// �򿪽����˵��굥�ļ�
	pTitle = File_read(fp, sizeof(struct Title_t));
	// ����δ���굥����
	Title_print(pTitle, data);
	// ��ӡδ���굥��Ϣ
	printf("\n������Ϊ%s�Ƿ���ˣ�(y)ȷ����(n)���أ�", data->ordernum);
	if (Input_control(NULL, 0, 0, 1, 1) == 'y')
	{
		printf("\nʵ�ս�");
		money = Input_control(str1, '0', '9', 5, 2);
		// ������
		if (money < data->money)
			// ʵ�ս���С�ڶ������
		{
			printf("\nʵ�ս��С�ڶ������޷����ˣ������������...");
			getch();
			return;
		}
		printf("\n���ҽ�%d", money - (data->money));
		fp = File_open("../../Code/Data/Title/Title.txt");
		File_write(fp, pTitle, sizeof(struct Title_t), 2);
		//д���ѽ��굥����

		fp = File_open("../../Code/Data/Order/Order.txt");
		fseek(fp, 0, 2);
		strcpy(data->acname, acName);
		//д����˷���Ա��¼���������ṹ����
		fwrite(data, sizeof(struct Order_t), 1, fp);
		//д���ѽᶩ���Ľ�㵽��һ���ļ�
		fflush(fp);

		ps->pNext = pt->pNext;
		// ɾ�����
		free(pt);
		//�ͷ��ѽᶩ���Ľ��
		fp = fopen("../../Code/Data/Cache/Order.txt", "w+");
		File_write(fp, pOrder, sizeof(struct Order_t), 0);
		//ˢ��δ�ᶩ�����ļ�

		pt = pTable->pNext;
		while (pt)
		{
			if (strcmp(((struct Table_t*)(pt->pData))->acNo, str) == 0)
				// �ҵ��ѽ���̨�����
			{
				((struct Table_t*)(pt->pData))->state = 0;
				// ����״̬��Ϊ����
				fp = File_open("../../Code/Data/Table.txt");
				File_write(fp, pTable, sizeof(struct Table_t), 0);
				// ����̨����Ϣ�ļ�
				break;
			}
			pt = pt->pNext;
		}
		printf("\n���˳ɹ�");
	}
	else
		printf("\n����ʧ��");
	printf("�������������...");
	getch();
	List_free(pTitle);
	List_free(pOrder);
}


/************************************************************************
* �������ƣ�void printPopularFood(pList pTable)
* ��Ҫ���ܣ�
		   ��ӡ���ܻ�ӭ��ʳ��
* �β�˵����
*       pList pTable   ̨�������ͷָ��
* ����ֵ��
*        ��
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
		printf("\nδ���в�����Ϣ��������ӣ�\n");
		return;
	}
	system("cls");
	printf("\n\t\t\t(1) ȫ��");
	printf("\n\n\t\t\t������Ҫ��ѯ��������");
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
				printf("\n\n\t\t���š���ҵ��ҵ���");
				printf("\n\n\t\t%-10s%-20s%-12s\n", "�˱��", "����", "�곤�Ƽ�");
				//���곤�Ƽ���ָ����ʵ���������
				k = 1;
			}
			float pop;
			pop = popf(pd->price);
			printf("\t\t%-10s%-20s%-12.1f��\n", pd->num, pd->name, pop);
			if (pt->pNext == NULL)
				k = 0;
			pt = pt->pNext;
		}
		/**************************/

		printf("�����������");
		getch();
		return;
	}
	
	system("pause");
}