/************************************************************************
* �ļ����ƣ� Log_in.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ��ڵ�¼����ͳ�ʼ���Ĺ��ܡ�

*************************************************************************/
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "../Log_in/Log_in.h"


char acName[10] = { 0 };
// ��ŵ�½�û���

/************************************************************************
* �������ƣ�void JR_EmptyRaw(int r1,int r2)
* ��Ҫ���ܣ�
		   ���ָ���еĺ���
* �β�˵����
*    int r1    ��ʼ��
	 int r2	   ������
* ����ֵ��
*        ��
*************************************************************************/

void JR_EmptyRaw(int r1, int r2)
{
	int i, j;
	for (i = r1; i <= r2; i++)
	{
		JR_SetCursor(i, 0);
		for (j = 0; j <= 80; j++)
			printf("%c", ' ');
		// �ÿո������ÿ��
	}
}

/************************************************************************
* �������ƣ�void JR_SetCursor(int x, int y)
* ��Ҫ���ܣ�
		   ��궨λ����
* �β�˵����
*    int x   ������
	 int y   ������
* ����ֵ��
*        ��
*************************************************************************/

void JR_SetCursor(int x, int y)
{

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { y, x };
	SetConsoleCursorPosition(hOut, pos);
}

/************************************************************************
* �������ƣ�int Log_in(pList head)
* ��Ҫ���ܣ�
		   ��¼����
* �β�˵����
*    pList head    Ա�������ͷָ��
* ����ֵ��
*        Ա���Ľ�ɫ��־
*************************************************************************/

int Log_in(pList head)
{
	int a, b, c;
	char time[10] = { 0 };
	pList pt;
	struct staff_t* data;
	char name[10] = { 0 };
	// ���������û���
	char psd[8] = { 0 };
	// ������������
	char role[3][10] = { "����Ա","����","����Ա" };
	Ordernum_get(time, NULL);
	sscanf(time, "%4d%2d%2d", &a, &b, &c);
	while (1)
	{
		system("cls");
		system("color F1");
		printf("\n\n\t\t\t\t\tС�ڣ�С�ס�ͯ���ճ�(*^o^)/\\(^o^*)");
		printf("\n\n\n\n\n\t\t\t�ӵǡ�¼���硤���");
		printf("\t\t\t\t\t��������~~��ӭ�Ͳ�~~\n\n\n\n\n");
		printf("\t\t\t%-19s", "���û�����");
		printf("\n\n\t\t\t%-19s", "�����룺");
		printf("(6λ)");
		printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t��ǰ���ڣ�%4d-%02d-%02d", a, b, c);
		printf("\n\n\n\n\t\t\t\(*^��^*)/����ӭ��ӭ~~С���С������ȵ�¼Ӵ~~");

		JR_SetCursor(12, 33);
		// ��궨λ���û��������λ��
		Input_control(name, 0, 0, 10, 1);
		// �������뺯����ֻ��������ĸ
		JR_SetCursor(14, 31);
		// ��λ�����������λ��
		Input_control(psd, '0', '9', 6, 2);
		//ֻ���������� 
		pt = head->pNext;
		while (pt)
		{
			data = (struct staff_t*)(pt->pData);
			if ((strcmp(data->acName, name) == 0) && (strcmp(data->psd, psd) == 0))
			{
				strcpy(acName, data->acName);
				// �洢��½�û���
				printf("\n\n\t\t\t��¼�ɹ������Ϊ��%s�������������...", role[data->role]);
				getch();
				return data->role;
				// ����Ա����ɫ��־
			}
			pt = pt->pNext;
		}
		printf("\n\n\t\t\t��������������������룬�����������...");
		memset(psd, 0, sizeof(char));
		getch();
	}
}

/************************************************************************
* �������ƣ�void Login_init(FILE *fp,pList head)
* ��Ҫ���ܣ�
		   ��¼��ʼ����������������Աadmin�û�
* �β�˵����
*    FILE *fp    Ա���ļ�ָ��
	 pList head  Ա�������ͷָ��
* ����ֵ��
*        ��
*************************************************************************/

void Login_init(FILE* fp, pList head)
{
	struct staff_t* data;
	data = (struct staff_t*)malloc(sizeof(struct staff_t));
	data->acNO = 1000;
	// ��ʼ������Ա�Ĳ���
	strcpy(data->acName, "admin");
	strcpy(data->psd, "123456");
	data->role = 2;
	// ����Ա���
	data->flag = 1;
	List_add(head, data);
	// ��ӵ�����
	File_write(fp, head, sizeof(struct staff_t), 0);
	// д���ļ�   

}
/************************************************************************
* �������ƣ�void Login_initManager(FILE *fp,pList head)
* ��Ҫ���ܣ�
			��¼��ʼ����������������Աmanager�û�
* �β�˵����
*		FILE *fp    �����ļ�ָ��
		pList head  ���������ͷָ��
* ����ֵ��
*        ��
*************************************************************************/
void Login_initManager(FILE* fp, pList head)
{
	struct staff_t* data;
	data = (struct staff_t*)malloc(sizeof(struct staff_t));
	data->acNO = 10000;
	//��ʼ������Ĳ���
	strcpy(data->acName, "manager");
	strcpy(data->psd, "666666");
	data->role = 1;
	//�������
	data->flag = 1;
	List_add(head, data);
	//��ӵ�����
	File_write(fp, head, sizeof(struct staff_t), 0);
    //д���ļ�
}