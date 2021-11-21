/************************************************************************
* �ļ����ƣ� File.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ����ļ����������й��ܡ�

*************************************************************************/
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <windows.h>
#include "../File/File.h"
#include "../Input_Control/Input_Control.h"



/************************************************************************
* �������ƣ�FILE *File_open(char *dirname)
* ��Ҫ���ܣ�
*    �ļ��д��������ļ�����
* �β�˵����
*    char *dirname   �ļ���
* ����ֵ��
*    ���ش��ļ���ָ��
*************************************************************************/

FILE* File_open(char* dirname)
{
	FILE* fp;
	fp = fopen(dirname, "rb+");
	// �ļ����ڣ���r+��
	if (fp == NULL)
	{
		fp = fopen(dirname, "wb+");
		// �ļ������ڣ���w+��
		if (fp == NULL)
		{
			printf("File open failed.\n");
			// �򿪲��ɹ�������ʾ
			// һ�����·������ʱ��ʾ����ɾ
		}
	}

	return fp;
}

/************************************************************************
* �������ƣ�int File_write(FILE *fp,pList head,int size,int n)
* ��Ҫ���ܣ�
*    ����д���ļ�����
* �β�˵����
*    FILE *fp         Ҫд���ļ����ļ�ָ��
	 pList head       Ҫд�������ͷָ��
	 int size         Ҫд��Ľṹ���С
	 int n             Ҫд�����ʼλ��
* ����ֵ��
*    д������ݸ���
*************************************************************************/

int File_write(FILE* fp, pList head, int size, int n)
{
	pList pt;
	int count = 0;
	fseek(fp, 0, n);
	// �ļ�ָ��ƫ�Ƶ�nָ����λ��
	pt = head->pNext;
	while (pt != NULL)
	{
		count++;
		fwrite(pt->pData, size, 1, fp);
		// ��nָ����λ��д������
		fflush(fp);
		// �����ļ�
		pt = pt->pNext;
	}
	return count;
}


/************************************************************************
* �������ƣ�pList File_read(FILE *fp,int size)
* ��Ҫ���ܣ�
*    �ļ����ݶ�������
* �β�˵����
*    FILE *fp    Ҫ�������ļ�ָ��
	 int size    Ҫ�����Ľṹ���С
* ����ֵ��
*    ����������ͷָ��
*************************************************************************/

pList File_read(FILE* fp, int size)
{
	pList head;
	int flag;
	void* p1;
	fseek(fp, 0, SEEK_SET);
	//��λ���ļ�ͷ
	head = List_init(NULL);
	p1 = malloc(size);
	flag = fread(p1, size, 1, fp);
	// flag��ӳ�Ƿ�ɹ�����
	while (flag)
	{
		List_add(head, p1);
		p1 = malloc(size);
		// ÿ�ο���һ���¿ռ䣬���ÿ�ζ�����������
		flag = fread(p1, size, 1, fp);
	}
	return head;
	//���ض��������ͷָ��
}

/************************************************************************
* �������ƣ�void File_remove(FILE *fp,pList head,int size,int (*p)(pList))
* ��Ҫ���ܣ�
*    �ļ�����ɾ��������Ա����̨���ļ�ɾ��
* �β�˵����
*    FILE *fp      Ҫɾ�����ļ�ָ��
	 pList head    Ҫɾ����ͷ���
	 int size      Ҫɾ���Ľṹ���С
	 int (*p)(pList)   ɾ���ĺ���ָ��
* ����ֵ��
*    ��
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
		// ��¼����λ��
		if (prem(pt))
			// ��ѯҪ�����Ľ������
			break;
		pt = pt->pNext;
	}

	if (pt == NULL)
		printf("\nδ�鵽������Ϣ");

	else
	{

		printf("\n�Ƿ�ȷ��ɾ��(y)�ǡ�(n)��:");
		if (Input_control(NULL, 0, 0, 1, 1) == 'y')
			// ��ʾ�Ƿ�ȷ��ɾ��
		{
			fseek(fp, (count - 1) * size, SEEK_SET);
			// ��λ��Ҫ��ɾ���Ľ��λ��
			fwrite(pt->pData, size, 1, fp);
			// ���Ǿ�����
			fflush(fp);
			printf("\nɾ���ɹ�");
		}
		else
			printf("\nɾ��ʧ��");
	}

	printf("�������������...");
	getch();
}

/************************************************************************
* �������ƣ�void File_add(FILE *fp,pList head,int size,void *(*pstr)(void *data))
* ��Ҫ���ܣ�
*    �ļ��������Ӻ���
* �β�˵����
*    FILE *fp      Ҫ���ӵ��ļ�ָ��
	 pList head    Ҫ���ӵ�ͷ���
	 int size      Ҫ���ӵĽṹ���С
	 void *(*pstr)(void *data)   �������ӵĺ���ָ�룬������������
* ����ֵ��
*    ��
*************************************************************************/

void File_add(FILE* fp, pList head, int size, void* (*padd)(void* data))
//���һ����Ա
{
	pList pNew, pt;
	pt = head;
	while (pt->pNext != NULL)
	{
		pt = pt->pNext;
	}
	pNew = List_init(padd(pt->pData));
	printf("�Ƿ�ȷ������(y)�ǡ�(n)��:");
	if (Input_control(NULL, 0, 0, 1, 1) == 'y')
		// ��ʾ�Ƿ�ȷ������
	{
		pt->pNext = pNew;
		fseek(fp, 0, SEEK_END);
		//��λ���ļ�ĩβ�������  
		fwrite(pNew->pData, size, 1, fp);
		// ��������������
		fflush(fp);
		printf("\n���ӳɹ�");
	}
	else
		printf("\n����ʧ��");

	printf("�������������...");
	getch();
}

/************************************************************************
* �������ƣ�void File_del(FILE *fp,char dir[],pList head,int size,int (*pdel)(pList))
* ��Ҫ���ܣ�
*    �ļ�����ɾ��������������ɾ��
* �β�˵����
*    FILE *fp      Ҫɾ�����ļ�ָ��
	 char dir[]    �ļ�·��
	 pList head    Ҫɾ����ͷ���
	 int size      Ҫɾ���Ľṹ���С
	 int (*pdel)(pList)   ɾ���ĺ���ָ��
* ����ֵ��
*    ��
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

			printf("\n�Ƿ�ȷ��ɾ��(y)�ǡ�(n)��:");
			if (Input_control(NULL, 0, 0, 1, 1) == 'y')
			{
				ps->pNext = pt->pNext;
				free(pt);
				// �ͷ�Ҫɾ���Ľ��
				fclose(fp);
				fp = fopen(dir, "w+");
				// ��W+��ʽ���´��ļ�
				File_write(fp, head, size, 0);
				// ���°�����д���ļ�
				printf("\nɾ���ɹ�");
			}
			else
				printf("\nɾ��ʧ��");
			break;
		}
		ps = pt;
		pt = pt->pNext;
	}
	if (pt == NULL)
		printf("\nδ�ҵ�������Ϣ");
	printf("�������������...");
	getch();
}

/************************************************************************
* �������ƣ�void File_updata(FILE *fp,pList head,int size,int (*p)(pList))
* ��Ҫ���ܣ�
*    �ļ������޸ĺ���
* �β�˵����
*    FILE *fp     Ҫ�޸ĵ��ļ�ָ��
	 pList head   Ҫ�޸ĵ�ͷ���
	 int size     Ҫ�޸ĵĽṹ���С
	 int (*p)(pList)  �޸ĵĺ���ָ��
* ����ֵ��
*    ��
*************************************************************************/

void File_updata(FILE* fp, pList head, int size, int (*p)(pList))
//���������޸���Ϣ��ͬʱ���µ��ļ���
{
	pList pt;
	int count;
	count = 0;
	pt = head->pNext;
	while (pt != NULL)
	{
		count++;
		// ��¼Ҫ���µ������������е�λ��
		if (p(pt))
			// ����Ҫ���µ�����
		{
			break;
		}
		pt = pt->pNext;
	}

	if (pt == NULL)
		printf("\nδ�鵽������Ϣ");

	else
	{
		printf("\n�Ƿ�ȷ���޸�(y)�ǡ�(n)��:");
		if (Input_control(NULL, 0, 0, 1, 1) == 'y')
		{
			fseek(fp, (count - 1) * size, SEEK_SET);
			// ��λ��Ҫ���µĽ��λ��
			fwrite(pt->pData, size, 1, fp);
			// ���Ǿ�����
			fflush(fp);
			printf("\n�޸ĳɹ�");
		}
		else
			printf("\n�޸�ʧ��");
	}
	printf("�������������...");
	getch();
}

