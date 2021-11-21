/************************************************************************
* �ļ����ƣ� Order.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ��ڵ�͵Ĺ��ܡ�

*************************************************************************/
#include <windows.h>
#include <string.h>
#include <time.h>
#include "../Order/Order.h"
#include "../Menu/Menu.h"

extern  char acName[10];
//����Ա��¼��

/************************************************************************
* �������ƣ�void Order_add(int count1,struct Order_t *pNew,pList pTitle,pList pOrder,pList pMenu,char tabpath[])
* ��Ҫ���ܣ�
		   �Ӳ˹��ܺ���
* �β�˵����
*       int count1              ��������ĸ���
		struct Order_t *pNew    ��Ӧ�Ķ�������ָ��
		pList pTitle            �굥�����ͷָ��
		pList pOrder            ���������ͷָ��
		pList pMenu             ���������ͷָ��
		char tabpath[]          �굥���м���·��
* ����ֵ��
*       ��
*************************************************************************/

void Order_add(int count1, struct Order_t* pNew, pList pTitle, pList pOrder, pList pMenu, char tabpath[])
{
	/************************************/
	
	/**************************************/
	FILE* fp;
	pList ps, ps1;
	int t;
	int count;
	// conut�����ڼ�����
	struct Menu_t* data;
	struct Title_t* DATA;
	char str[8];
	while (1)
	{
		JR_EmptyRaw(count1 + 3, count1 + 12);
		JR_SetCursor(count1 + 11, 0);
		printf("\t\t\t\t\t\t\t��<Esc>���˳�...");
		JR_SetCursor(count1 + 3, 0);
		memset(str, 0, sizeof(char));
		printf("\t\t������Ҫ���ӵĲ˱�ţ�");
		Input_control(str, '0', '9', 5, 2); 
		// str���Ų˱��
		if (strcmp(str, "0") == 0)
		{
			return;
		}
		printf("\n\t\t������Ҫ���ӵķ�����");
		t = Input_control(NULL, '1', '9', 1, 2);
		// t���Ų˵ķ���
		count = 0;
		ps = pMenu->pNext;
		while (ps != NULL)
		{
			count++;
			// �����ڼ�����
			data = (struct Menu_t*)(ps->pData);
			if (strcmp(data->num, str) == 0)
				//�ҵ������ж�Ӧ�Ĳ���Ϣ
			{
				//data->food_nums = (data->food_nums) + t;
				break;
			}
			ps = ps->pNext;
		}
		
		if (ps == NULL)
		{
			printf("\n\t\t�˱�������������������룬�����������...");
			getch();
		}
		else
			break;
	}
	printf("\n\n\t\t�Ƿ�ȷ�ϼӲ�(y)ȷ����(n)����:");
	if (Input_control(NULL, 0, 0, 1, 1) == 'n')
	{
		printf("\n\t\t�Ӳ�ʧ�ܣ������������...");
		getch();
		return;
	}
	ps1 = pTitle->pNext;
	while (ps1 != NULL)
	{
		DATA = (struct Title_t*)(ps1->pData);
		if (strcmp(DATA->pMenu.num, str) == 0)
			// �ж��굥���Ƿ��е�˴˵���
		{
			DATA->amount = t + (DATA->amount);
			// ����Ĳˣ���������t

			JR_SetCursor(count, 0);
			// ��궨λ������Ĳ�����
			printf("\t\t*%-11s%-12s��%-10d%-12d", DATA->pMenu.num, DATA->pMenu.name,
				DATA->pMenu.price, DATA->amount);
			// ���´�ӡ���еĲ���Ϣ
			
			break;
		}
		ps1 = ps1->pNext;
	}
	if (ps1 == NULL)
	{
		List_add(pTitle, Title_init(pNew, data, t));
		// û������µ�Ĳ���ӵ��굥������ 
		JR_SetCursor(count, 0);
		// ��궨λ��û����Ĳ�����
		printf("\t\t*%-11s%-12s��%-10d%-12d", data->num, data->name, data->price, t);
		// ���´�ӡ
	}
	fp = File_open(tabpath);
	File_write(fp, pTitle, sizeof(struct Title_t), 0);
	//�Ӳ˽��д�뵽�굥�м��ļ���
	Order_statist(pNew, pTitle);
	// ������ϢҲ���Ÿ���
	fp = File_open("../../Code/Data/Cache/Order.txt");
	File_write(fp, pOrder, sizeof(struct Order_t), 0);
	// ��������д�뵽�м��ļ�
	JR_SetCursor(count1 + 1, 0);
	printf("\t\t\t\t\t%-4s:%-5d%-4s:%d\n", "�ܽ��", pNew->money, "�ܷ���", pNew->amount);
	JR_SetCursor(count1 + 7, 0);
	printf("\t\t�Ӳ˳ɹ�");
	printf("\n\t\t�Ƿ�����Ӳˣ�(y)ȷ����(n)���أ�");
	if (Input_control(NULL, 0, 0, 1, 1) == 'y')
		Order_add(count1, pNew, pTitle, pOrder, pMenu, tabpath);
	// �Ƿ�����Ӳ�
	struct Menu_t *food;
}

/************************************************************************
* �������ƣ�void Order_del(int count1,struct Order_t *pNew,pList pTitle,pList pMenu,pList pOrder,char tabpath[])
* ��Ҫ���ܣ�
		   ���˹��ܺ���
* �β�˵����
*       int count1               ��������ĸ���
		struct Order_t *pNew    ��Ӧ�Ķ�������ָ��
		pList pTitle            �굥�����ͷָ��
		pList pOrder            ���������ͷָ��
		pList pMenu             ���������ͷָ��
		char tabpath[]          �굥���м���·��
* ����ֵ��
*       ��
*************************************************************************/

void Order_del(int count1, struct Order_t* pNew, pList pTitle, pList pMenu, pList pOrder, char tabpath[])
{
	FILE* fp;
	pList ps, pt;
	int t;
	struct Title_t* DATA;
	char str[8];
	int count;
	// ��¼����Ĳ˵�λ��
	JR_EmptyRaw(count1 + 3, count1 + 12);
	JR_SetCursor(count1 + 11, 0);
	printf("\t\t\t\t\t\t\t��<Esc>���˳�...");
	JR_SetCursor(count1 + 3, 0);
	memset(str, 0, sizeof(char));
	printf("\t\t�������˵��Ĳ˱�ţ�");
	Input_control(str, '0', '9', 5, 2);
	if (strcmp(str, "0") == 0)
	{
		return;
	}
	printf("\n\t\t������Ҫ�˵��ķ�����");
	t = Input_control(NULL, '1', '9', 1, 2);
	count = 0;
	ps = pMenu->pNext;
	while (ps != NULL)
	{
		count++;
		// �����ڼ�����
		if (strcmp(((struct Menu_t*)(ps->pData))->num, str) == 0)
			//�ҵ������ж�Ӧ�Ĳ���Ϣ
		{
			break;
		}
		ps = ps->pNext;
	}
	pt = pTitle;
	ps = pTitle->pNext;
	while (ps != NULL)
	{
		DATA = (struct Title_t*)(ps->pData);
		if (strcmp(DATA->pMenu.num, str) == 0)
			// �ж��굥���Ƿ��е�˴˵���
		{
			if (t > DATA->amount)
				// Ҫ�˵ķ�������ʵ�ʵ���ķ���
			{
				printf("\n\t\t�����������ʵ�ʷ����������������...");
				getch();
				break;
			}
			else
			{
				printf("\n\n\t\t�Ƿ�ȷ���˲�(y)ȷ����(n)����:");
				if (Input_control(NULL, 0, 0, 1, 1) == 'n')
				{
					printf("\n\t\t�˲�ʧ�ܣ������������...");
					getch();
					return;
				}
				DATA->amount = (DATA->amount) - t;
				// ���·���
				if (DATA->amount == 0)
					// �˵ķ����Ƿ���ڵ����
				{
					JR_SetCursor(count, 0);
					printf("\t\t%-12s%-12s��%-10d%-12d", DATA->pMenu.num,
						DATA->pMenu.name, DATA->pMenu.price, DATA->amount);
					// ���´�ӡ,ȥ��*��
					pt->pNext = ps->pNext;
					// �ͷ��굥������˵Ľ��
					free(ps);
					fp = fopen(tabpath, "w+");
				}
				else
				{
					fp = File_open(tabpath);
					JR_SetCursor(count, 0);
					printf("\t\t*%-11s%-12s��%-10d%-12d", DATA->pMenu.num,
						DATA->pMenu.name, DATA->pMenu.price, DATA->amount);
					// ������Ϊ0�����´�ӡ��
				}

				File_write(fp, pTitle, sizeof(struct Title_t), 0);
				// ���˲˽��д���м��ļ�
				Order_statist(pNew, pTitle);
				// ���¶�����Ϣ
				fp = File_open("../../Code/Data/Cache/Order.txt");
				File_write(fp, pOrder, sizeof(struct Order_t), 0);
				// ��������д�뵽�м��ļ�
				JR_SetCursor(count1 + 1, 0);
				printf("\t\t\t\t\t%-4s:%-5d%-4s:%d\n", "�ܽ��", pNew->money, "�ܷ���", pNew->amount);
				JR_SetCursor(count1 + 6, 0);
				printf("\n\t\t�˲˳ɹ��������������...");
				getch();
				return;
			}
		}
		pt = ps;
		ps = ps->pNext;
	}
	if (ps == NULL)
	{
		printf("\n\t\t�˵���δ��򲻴��ڣ��޷��˲ˣ������������...");
		getch();
	}

}

/************************************************************************
* �������ƣ�void Order_print(pList pMenu,pList pTitle,struct Order_t *pNew)
* ��Ҫ���ܣ�
		   ������ӡ����
* �β�˵����
*       pList pMenu            ���׵�ͷָ��
		pList pTitle           �굥��ͷָ��
		struct Order_t *pNew   �������ݵ�ָ��
* ����ֵ��
*        ��
*************************************************************************/

void Order_print(pList pMenu, pList pTitle, struct Order_t* pNew)
{

	pList pt, ps;
	struct Title_t* data;
	struct Menu_t* pM;
	system("cls");
	printf("\t\t%-12s%-12s%-12s%-12s\n", "�˱��", "����", "�۸�", "����");
	pt = pMenu->pNext;
	while (pt)
	{
		ps = pTitle->pNext;
		pM = (struct Menu_t*)(pt->pData);
		while (ps)
		{
			data = (struct Title_t*)(ps->pData);
			if (strcmp(data->pMenu.num, pM->num) == 0)
				//�ж��굥���Ƿ���������
			{
				printf("\t\t%c", '*');
				// Ϊ����Ĳ˱��ǰ��ӡ*
				printf("%-11s%-12s%s%-10d%-12d\n", data->pMenu.num, data->pMenu.name,
					"��", data->pMenu.price, data->amount);
				break;
			}
			ps = ps->pNext;
		}
		if (ps == NULL)
		{
			printf("\t\t%-12s%-12s%s%-10d%-12d\n", pM->num, pM->name, "��", pM->price, 0);
		}
		pt = pt->pNext;

	}
	printf("\t\t\t\t\t%-4s:%-5d%-4s:%d\n", "�ܽ��", pNew->money, "�ܷ���", pNew->amount);
}

/************************************************************************
* �������ƣ�void Order_statist(struct Order_t *pNew,pList pTitle)
* ��Ҫ���ܣ�
		   �������ܽ��ܷ���ͳ�ƺ���
* �β�˵����
*       struct Order_t *pNew     �������ݵ�ָ��
		pList pTitle             �굥�����ͷָ��
* ����ֵ��
*        ��
*************************************************************************/

void Order_statist(struct Order_t* pNew, pList pTitle)
{
	struct Title_t* Data;
	pList pt;
	int money, copies;
	money = copies = 0;
	pt = pTitle->pNext;
	while (pt)
	{
		Data = (struct Title_t*)(pt->pData);
		money = money + (Data->pMenu.price) * (Data->amount);
		//�굥�Ľ���ۼ�
		copies = copies + (Data->amount);
		// �굥�ķ����ۼ�
		pt = pt->pNext;

	}
	pNew->amount = copies;
	// �ܽ����붩����
	pNew->money = money;
	// �ܷ������붩����
}

/************************************************************************
* �������ƣ�struct Order_t *Order_init(char str[])
* ��Ҫ���ܣ�
		   �����ṹ���ʼ������
* �β�˵����
*       char str[]  ��˵�̨����
* ����ֵ��
*        ���س�ʼ���Ķ������ָ��
*************************************************************************/

struct Order_t* Order_init(char str[])
{
	struct Order_t* pNew;
	pNew = (struct Order_t*)malloc(sizeof(struct Order_t));
	memset(pNew, 0, sizeof(struct Order_t));
	strcpy(pNew->tablenum, str);
	// ���붩���ṹ���̨����
	Ordernum_get(pNew->ordernum, str);
	// �Զ���ö�����

	return pNew;

}

/************************************************************************
* �������ƣ�struct Title_t *Title_init(struct Order_t *pNew,struct Menu_t *data,int n)
* ��Ҫ���ܣ�
		   �굥�ṹ���ʼ������
* �β�˵����
*       struct Order_t *pNew     �����̨����Ӧ�Ķ������ݵ�ָ��
		struct Menu_t *data      �����Ĳ�������
		int n                    �˵ķ���
* ����ֵ��
*        ���س�ʼ�����굥���ָ��
*************************************************************************/

struct Title_t* Title_init(struct Order_t* pNew, struct Menu_t* data, int n)
{
	struct Title_t* pTemp;
	pTemp = (struct Title_t*)malloc(sizeof(struct Title_t));
	memset(pTemp, 0, sizeof(struct Title_t));
	strcpy(pTemp->ordernum, pNew->ordernum);
	// ���굥�д��붩����
	pTemp->pMenu = *data;
	// ������ĳһ������
	pTemp->amount = n;
	// �˵ķ���

	return pTemp;

}

/************************************************************************
* �������ƣ�long Ordernum_get(char num[],char str[])
* ��Ҫ���ܣ�
		   �Զ����ɶ����ŵĺ���
* �β�˵����
*       char num[]    �����ṹ���еĶ����ų�Ա����
		char str[]    ��˵�̨����
* ����ֵ��
*        ���ض�����
*************************************************************************/

long Ordernum_get(char num[], char str[])
{
	int year, month, day;
	char s[6] = { 0 };
	time_t t;
	//ʱ������
	struct tm* data;
	//ʱ��ṹ��
	time(&t);
	//��ȡʱ�䣬����rawtime
	data = localtime(&t);
	//ת��Ϊ����ʱ��
	year = 1900 + data->tm_year;
	// ȡ��ϵͳ��ǰ����
	month = data->tm_mon + 1;
	day = data->tm_mday;
	if (num == NULL&&str == "month")
	{
		return((year * 100 + month) * 100);
	}
	if (num == NULL && str == NULL)
	{
		return ((year * 100 + month) * 100 + day);
		// �������͵�����
	}
	convert(s, year, 4);
	// ת������Ϊ�ַ���
	strcat(num, s);
	// ��ϳɶ�����
	convert(s, month, 2);
	strcat(num, s);
	convert(s, day, 2);
	strcat(num, s);
	if (num != NULL && str == NULL)
		// num��ȡ�ַ��͵�����
	{
		return 0;
	}
	strcat(num, str);
	// num��ȡ�����ţ������ź���Ϊ̨����str
	return 0;

}


void convert(char s[], int data, int n)
{
	int t, i = 0;
	t = data;
	while (t != 0)
	{
		s[n - 1 - i] = t % 10 + 48;
		// ����ת��Ϊ�ַ���
		t = t / 10;
		i++;
		if (data < 10 && n == 2)
			// С��10���·ݺ�������ǰ����ַ�0
		{
			s[0] = '0';
		}
	}
	s[n] = '\0';
}


/************************************************************************
* �������ƣ�void Order_search_unbuy(pList pOrder,pList pTable)
* ��Ҫ���ܣ�
		   δ�򶩵���ѯ����
* �β�˵����
*      pList pOrder     ������ͷָ��

* ����ֵ��
*        ��
*************************************************************************/

void Order_search_unbuy(pList pOrder)
{
	pList pt;
	struct Order_t* data;
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

}

/************************************************************************
* �������ƣ�void Order_search_buy()
* ��Ҫ���ܣ�
		   ���򶩵���ѯ����
* �β�˵����
*        ��
* ����ֵ��
*        ��
*************************************************************************/

void Order_search_buy()
{
	FILE* fp;
	struct Order_t* data;
	pList pt, pOrder;
	int count = 0;
	long* stardate, * enddate;
	long ordernum;// ������
	fp = File_open("../../Code/Data/Order/Order.txt");
	// �����򵥵��ļ�
	pOrder = File_read(fp, sizeof(struct Order_t));
	// �������򵥵�����
	stardate = (long*)malloc(sizeof(long));
	// ��ʼ����
	enddate = (long*)malloc(sizeof(long));
	// ��������

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
		Orderdate_input(stardate, enddate);
		// ���뿪ʼ�ͽ�������
		printf("\n");
	}
	printf("\t\t%-16s%-11s%-11s%-11s\n", "������", "���", "״̬", "����Ա");
	pt = pOrder->pNext;
	while (pt)
	{
		data = (struct Order_t*)(pt->pData);
		sscanf(data->ordernum, "%8ld", &ordernum);
		if ((ordernum <= *enddate) && (ordernum >= *stardate))
		{
			count++;
			printf("\t\t%-16s%s%-9d%-11s%-11s\n", data->ordernum, "��", data->money, "�ѽ���", data->acname);
		}
		pt = pt->pNext;
	}
	if (count == 0)
	{
		system("cls");
		printf("\n��������δ��ѯ����ض������밴���������...");
	}
	else
		printf("\n\t\t�밴���������...");
	List_free(pOrder);
}


/************************************************************************
* �������ƣ�void Title_print(pList pTitle,struct Order_t *pOrder)
* ��Ҫ���ܣ�
		   �굥��ӡ����
* �β�˵����
*      pList pTitle             �굥��ͷָ��
	   struct Order_t *pOrder   �������ݵ�ָ��
* ����ֵ��
*        ��
*************************************************************************/

void Title_print(pList pTitle, struct Order_t* pOrder)
{
	pList pt;
	struct Title_t* data;
	system("cls");
	printf("\t\t%-12s%-12s%-12s%-12s\n", "�˱��", "����", "�۸�", "����");
	pt = pTitle->pNext;
	while (pt)
	{
		data = (struct Title_t*)(pt->pData);
		printf("\t\t%c", '*');
		printf("%-11s%-12s%s%-10d%-12d\n", data->pMenu.num, data->pMenu.name, "��", data->pMenu.price, data->amount);
		pt = pt->pNext;
	}
	printf("\n\t\t%-4s:��%-4d%-4s:%d\n", "�ܽ��", pOrder->money, "�ܷ���", pOrder->amount);
}

/************************************************************************
* �������ƣ�void Orderdate_input(long *stardate,long *enddate)
* ��Ҫ���ܣ�
		   ��ʼ���ںͽ������ڵ����뺯��
* �β�˵����
*       long *stardate    ��ʼ���ڵ�ָ��
		long *enddate     �������ڵ�ָ��
* ����ֵ��
*        ��
*************************************************************************/

void Orderdate_input(long* stardate, long* enddate)
{
	char str[6] = { 0 };
	int n;
	long curdate = 0;
	// ��ǰ����
	curdate = Ordernum_get(NULL, NULL);
	// ��ȡ��ǰϵͳ����
	while (1)
	{
		system("cls");
		printf("��ʼ���ڣ�     -  -  ");
		JR_SetCursor(0, 10);
		*stardate = Input_control(str, '0', '9', 4, 2);
		if (*stardate < 2020)
		{
			printf("\n��ݲ��ɵ���2020Ŷ��С����20�꿪�ŵ�~~���������������...");
			getch();
			memset(str, 0, sizeof(char));
			// ����str
			continue;
			// ��������ѭ��
		}
		JR_SetCursor(0, 16);
		memset(str, 0, sizeof(char));
		n = Input_control(str, '0', '9', 2, 2);
		if (n > 12 || n == 0)
		{
			printf("\n�·�����1-12���ڣ����������������...");
			getch();
			memset(str, 0, sizeof(char));
			// ����str
			continue;
			// ��������ѭ��		
		}
		*stardate = (*stardate) * 100 + n;
		JR_SetCursor(0, 19);
		memset(str, 0, sizeof(char));
		n = Input_control(str, '0', '9', 2, 2);
		if (n > 31 || n == 0)
		{
			printf("\n���ǰ����磬��������Ҫ��1-31�հ������������������...");
			getch();
			memset(str, 0, sizeof(char));
			// ����str
			continue;
			// ��������ѭ��
		}
		*stardate = (*stardate) * 100 + n;
		memset(str, 0, sizeof(char));

		printf("\n�������ڣ�     -  -  ");
		JR_SetCursor(1, 10);
		*enddate = Input_control(str, '0', '9', 4, 2);
		if (*enddate < 2020)
		{
			printf("\n��ݲ��ɵ���2020�����������������...");
			getch();
			memset(str, 0, sizeof(char));
			// ����str
			continue;
			// ��������ѭ��
		}
		JR_SetCursor(1, 16);
		memset(str, 0, sizeof(char));
		n = Input_control(str, '0', '9', 2, 2);
		if (n > 12 || n == 0)
		{
			printf("\n�·�����1-12���ڣ������²�...���������������...");
			getch();
			memset(str, 0, sizeof(char));
			// ����str
			continue;
			// ��������ѭ��
		}
		*enddate = (*enddate) * 100 + n;
		JR_SetCursor(1, 19);
		memset(str, 0, sizeof(char));
		n = Input_control(str, '0', '9', 2, 2);
		if (n > 31 || n == 0)
		{
			printf("\n��������1-31���ڣ����������������...");
			getch();
			memset(str, 0, sizeof(char));
			// ����str
			continue;
			// ��������ѭ��
		}
		*enddate = (*enddate) * 100 + n;
		memset(str, 0, sizeof(char));
		if (*stardate > * enddate)
		{
			printf("\n��ʼ���ڲ��ɴ��ڽ������ڣ����������������...");
			getch();
		}
		else if (*enddate > curdate)
		{
			printf("\n������ǰϵͳ���ڣ����������������...");
			getch();
		}
		else
			break;
	}

}