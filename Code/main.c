/************************************************************************
* �ļ����ƣ� main.c

* ���빦�ܣ�
*     ���ļ�Ϊ��������ڣ�ʵ��ϵͳ�����С�

*************************************************************************/
#include <windows.h>
#include "./Staff/Staff.h"
#include "./File/File.h"
#include "./Log_in/Log_in.h"
#include "./Admin/Admin.h"
#include "./Waiter/Waiter.h"
#include "./Manage/Manage.h"

int main()
{
	pList head, p;
	char staff[] = "../../Code/Data/Staff.txt";
	int (*pFile[3])() = { Ui_waiter, Ui_manage, Ui_admin };
	//��������һ�е��������������Ͽɿ�������ĵ�
	//��������ͬ��Ҳ��������ĵ�
	
	FILE* fp;
	fp = File_open(staff);
	head = File_read(fp, sizeof(struct staff_t));
	p = head;
	if (p->pNext == NULL)
	{
		Login_initManager(fp, head);
		//��ְ���ļ��ʿգ����ʼ������Ա�˻�
/************************************************************************
*����Ŀ������ְ���ļ�������ְ������Ӧ�����㼶

*����Ա���ϰ壩�˺�Ϊadmin������Ϊ123456
*����Ա�˺�Ϊwaiter������Ϊ111111
*�����˺�Ϊmanager������Ϊ666666

*��ͬ�㼶�û�ʹ�ò�ͬ�û����棬���ò�ͬϵͳģ��
*************************************************************************/
	}
	p = p->pNext;
	if (p->pNext == NULL)
	{
		Login_init(fp, head);
		//���ų�ʼ�������˻�
	}
	
	while(1)
	{
		fclose(fp);
		if (pFile[Log_in(head)]() == 1)
			//�����û�����
			//������1�����û���ѡ��ע��
		{
			break;
		}

		fp = File_open(staff);
		head = File_read(fp, sizeof(struct staff_t));
	}
	system("cls");
	//����
	printf("\n\n\n\t\t\t���˳�ϵͳ");
	return 0;
}