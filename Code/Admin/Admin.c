/************************************************************************
* �ļ����ƣ� Admin.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ��ڹ���Ա���ϰ壩�������ݵĹ��ܡ�

*************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "../File/File.h"
#include "../Admin/Admin.h"
#include "../List/List.h"
#include "../Staff/Staff.h"
#include "../Table/Table.h"
#include "../Menu/Menu.h"
#include "../Input_Control/Input_Control.h"



/************************************************************************
* �������ƣ�int Ui_admin()
* ��Ҫ���ܣ�
		   ����Ա����ѡ����
* �β�˵����
*       ��
* ����ֵ��
*        һ���������֣������ж���ע�������˳�
*************************************************************************/

int Ui_admin()
{
	int n;
	void (*pst[4])() = { Table_manage,Menu_manage,Staff_manage };
	while (1)
	{
		system("cls");
		printf("\n\n\n\t\t\t��=�Ԧ�(((�ġ��ء�)�ģ��ϰ壬������ѡ���ܣ�\n\n");
		printf("\t\t\t1��̨������\n\n");
		printf("\t\t\t2�����׹���\n\n");
		printf("\t\t\t3����Ա����\n\n");
		printf("\t\t\t4��ע��\n\n");
		printf("\t\t\t5���˳�\n\n");
		printf("\t\t\t(���� v �ѡ�):(��н~��н~��н~��Ҫ������Ĭ��3��!!!)");
		printf("\n\n\n\t\t\t(�� o ��)�����ϰ�~����������ţ�ֻ��ѡ1��Ŷ��");

		n = Input_control(NULL, '1', '5', 1, 2);
		if (n > 0 && n < 4)
		{
			pst[n - 1]();
			//�ֱ�����Table_manage��Menu_manage��Staff_manage��������
		}
		else if (n == 4)
			return 0;
		else if (n == 5)
			return 1;
	}

}


/************************************************************************
* �������ƣ�void Staff_manage()
* ��Ҫ���ܣ�
		   Ա������ѡ����
* �β�˵����
*       ��
* ����ֵ��
*        ��
*************************************************************************/

void Staff_manage()
{
	char dirname[] = "../../Code/Data/Staff.txt";
	FILE* fp;
	pList head;
	int n;
	fp = File_open(dirname);
	head = File_read(fp, sizeof(struct staff_t));

	while (1)
	{
		system("cls");
		//����
		printf("\n\n\n\t\t\t((��_��;|)):(�������ֲ����Ԥ��.jpg)\n\n");
		printf("\t\t\t1������Ա��\n\n");
		printf("\t\t\t2��ɾ��Ա��\n\n");
		printf("\t\t\t3���޸�Ա��\n\n");
		printf("\t\t\t4����ѯԱ��\n\n");
		printf("\t\t\t5������\n\n");
		printf("\t\t\t�����빦�ܣ������޸ģ�����");
		n = Input_control(NULL, '1', '5', 1, 2);
		switch (n)
		{
		case 1:
			List_print(head, staff_print);
			File_add(fp, head, sizeof(struct staff_t), staff_add);
			List_print(head, staff_print);
			break;
		case 2:
			List_print(head, staff_print);
			File_remove(fp, head, sizeof(struct staff_t), staff_remove);
			head = File_read(fp, sizeof(struct staff_t));
			List_print(head, staff_print);
			break;
		case 3:
			List_print(head, staff_print);
			File_updata(fp, head, sizeof(struct staff_t), staff_update);
			head = File_read(fp, sizeof(struct staff_t));
			List_print(head, staff_print);
			break;
		case 4:
			staff_search(head);
			break;
		case 5:
			break;
		}
		if (n == 5)
		{
			break;
		}
		else
		{
			printf("\n��<Esc>������...");
			while (getch() != 27)
			{
			}
			//�����벻Ϊ<Esc>��ʱ�����أ���ֹ�󴥷���
		}

	}
	List_free(head);
}


/************************************************************************
* �������ƣ�void Table_manage()
* ��Ҫ���ܣ�
		   ̨������ѡ����
* �β�˵����
*       ��
* ����ֵ��
*        ��
*************************************************************************/

void Table_manage()
{
	char dirname[] = "../../Code/Data/Table.txt";
	FILE* fp;
	pList head;
	int n;
	fp = File_open(dirname);
	head = File_read(fp, sizeof(struct Table_t));
	while (1)
	{
		system("cls");
		printf("\n\n\t\t\t((��*��))/������~��Ҫ�Ĺ��ܶ���Ŷ~");
		printf("\n\n\n\t\t\t̨���������\n\n");
		printf("\t\t\t1������̨��\n\n");
		printf("\t\t\t2��ɾ��̨��\n\n");
		printf("\t\t\t3���޸�̨��\n\n");
		printf("\t\t\t4����ѯ̨��\n\n");
		printf("\t\t\t5������\n\n");
		printf("\t\t\t����д������ȣ�");
		n = Input_control(NULL, '1', '5', 1, 2);
		switch (n)
		{
		case 1:
			List_print(head, Table_print);
			File_add(fp, head, sizeof(struct Table_t), Table_add);
			head = File_read(fp, sizeof(struct Table_t));
			List_print(head, Table_print);
			break;
		case 2:
			List_print(head, Table_print);
			File_remove(fp, head, sizeof(struct Table_t), Table_remove);
			head = File_read(fp, sizeof(struct Table_t));
			List_print(head, Table_print);
			break;
		case 3:
			List_print(head, Table_print);
			File_updata(fp, head, sizeof(struct Table_t), Table_update);
			head = File_read(fp, sizeof(struct Table_t));
			List_print(head, Table_print);
			break;
		case 4:
			Table_search(head, 3, 4);
			break;
		case 5:
			break;
		}
		if (n == 5)
		{
			break;
		}
		else
		{
			printf("\n��<Esc>������...");
			while (getch() != 27)
			{
			}
		}

	}
	List_free(head);
}



/************************************************************************
* �������ƣ�void Menu_manage()
* ��Ҫ���ܣ�
		   ���׹���ѡ����
* �β�˵����
*       ��
* ����ֵ��
*        ��
*************************************************************************/

void Menu_manage()
{
	char dirname[] = "../../Code/Data/Menu.txt";
	FILE* fp;
	pList head;
	int n;
	fp = File_open(dirname);
	head = File_read(fp, sizeof(struct Menu_t));
	while (1)
	{
		system("cls");
		printf("\n\n\n\t\t\t((^��^))/���ϰ�����������~\n\n");
		printf("\t\t\t1�����Ӳ���\n\n");
		printf("\t\t\t2��ɾ������\n\n");
		printf("\t\t\t3���޸Ĳ���\n\n");
		printf("\t\t\t4����ѯ����\n\n");
		printf("\t\t\t5������\n\n");
		printf("\t\t\t���ܶ�������Ŷ��ѡһ���ȣ�");
		n = Input_control(NULL, '1', '5', 1, 2);
		switch (n)
		{
		case 1:
			List_print(head, Menu_print);
			File_add(fp, head, sizeof(struct Menu_t), Menu_add);
			head = File_read(fp, sizeof(struct Menu_t));
			List_print(head, Menu_print);
			break;
		case 2:
			List_print(head, Menu_print);
			File_del(fp, dirname, head, sizeof(struct Menu_t), Menu_del);
			List_print(head, Menu_print);
			break;
		case 3:
			List_print(head, Menu_print);
			File_updata(fp, head, sizeof(struct Menu_t), Menu_update);
			head = File_read(fp, sizeof(struct Menu_t));
			List_print(head, Menu_print);
			break;
		case 4:

			Menu_search(head);
			break;
		case 5:
			break;
		}
		if (n == 5)
		{
			break;
		}
		else
		{
			printf("\n��<Esc>������...");
			while (getch() != 27)
			{
			}
		}

	}
	List_free(head);
}



