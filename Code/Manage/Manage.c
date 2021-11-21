/************************************************************************
* �ļ����ƣ� Manage.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ��ھ����ѯ�Ĺ��ܡ�

*************************************************************************/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "../Manage/Manage.h"
#include "../List/List.h"
#include "../Staff/Staff.h"
#include "../Order/Order.h"
#include "../Menu/Menu.h"


/************************************************************************
* �������ƣ�int Ui_manage()
* ��Ҫ���ܣ�
		   ������ѡ����
* �β�˵����
*       ��
* ����ֵ��
*        һ���������֣������ж���ע�������˳�
*************************************************************************/

int Ui_manage()
{
	int n;
	while (1)
	{
		system("cls");
		printf("\n\n\n\t\t\t(��v��)���𾴵ľ������ã�");
		printf("\n\n\n\n\t\t\t(��v��)����������ѡ�������棺\n\n");
		printf("\t\t\t1��Ӫ�ջ���\n\n");
		printf("\t\t\t2��ע��\n\n");
		printf("\t\t\t3���˳�\n\n");
		printf("\t\t\t(��v��)������������һ��ѡһ��Ŷ��");
		n = Input_control(NULL, '1', '3', 1, 2);
		if (n == 1)
		{
			Profit_statist();
		}
		else if (n == 2)
			return 0;
		else if (n == 3)
			return 1;
	}

}

/************************************************************************
* �������ƣ�void Profit_statist()
* ��Ҫ���ܣ�
		   ����������ʵ������ˮ������ˮ���ݵ�ͳ�Ʒ�����
* �β�˵����
*       ��
* ����ֵ��
*        ��
*************************************************************************/

void Profit_statist()
{
	pList pOrder, pStaff;
	pList p1, p2;
	struct Order_t* Odate;
	struct staff_t* Sdate;
	FILE* fp;
	long money, income;
	// �ܽ��
	long* stardate, * enddate;
	long ordernum;
	// ������
	money = income = 0;
	stardate = (long*)malloc(sizeof(long));
	// ��ʼ����
	enddate = (long*)malloc(sizeof(long));
	// ��������
	fp = File_open("../../Code/Data/Order/Order.txt");
	pOrder = File_read(fp, sizeof(struct Order_t));
	fp = File_open("../../Code/Data/Staff.txt");
	pStaff = File_read(fp, sizeof(struct staff_t));

	system("cls");
	printf("\n\n\t\t\t((��.w��))��������ŵ�һ��~Ҫ��ʲô��͵��~~��");
	printf("\n\n\n\n\t\t\t(1):�����ѯ\n");
	printf("\n\t\t\t(2):��ʷ��ѯ\n");
	printf("\n\t\t\t((��o��))��Ҫ�����ѽ~__");
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
		printf("\n\n\t\t\t((/QAQ /!))���ᾭӪ���ưɣ�����ɣ�");
		printf("\n\n\n\t\t\t(1):������ˮ\n");
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
	printf("\n\n\t\t\t%-15s%s\n", "����Ա", "Ӫ��");
	p1 = pStaff->pNext;
	while (p1)
	{
		Sdate = (struct staff_t*)(p1->pData);
		p2 = pOrder->pNext;
		while (p2)
		{
			Odate = (struct Order_t*)(p2->pData);
			sscanf(Odate->ordernum, "%8ld", &ordernum);
			// ��ȡ�������ϵ�����
			if ((strcmp(Sdate->acName, Odate->acname) == 0) && (ordernum <= *enddate) && (ordernum >= *stardate))
			{
				money = money + (Odate->money);
			}
			p2 = p2->pNext;
		}
		if ((Sdate->role == 0))
			// �ж��Ƿ�Ϊ����Ա
		{
			printf("\t\t\t%-15s%s%ld\n", Sdate->acName, "��", money);
			income = income + money;
			// �ۼ�ÿ������Ա��Ӫҵ��
			money = 0;
		}
		p1 = p1->pNext;
	}
	int a, month, c;
	char time[10] = { 0 };
	Ordernum_get(time, NULL);
	sscanf(time, "%4d%2d%2d", &a, &month, &c);
	printf("\n\t\t\t������%2d��Ŷ((>��<))\n\n", month);
	printf("\n\t\t\t��Ӫҵ���%ld\n", income);
	printf("\n\t\t\t������~~�����������...");
	getch();
}







