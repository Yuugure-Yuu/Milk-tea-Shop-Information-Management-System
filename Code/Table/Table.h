/************************************************************************
* �ļ����ƣ� Table.h

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ���̨������ɾ�Ĳ鹦�ܡ�

*************************************************************************/
#ifndef _TABLE_H_
#define _TABLe_H_

#include <string.h>
#include "../List/List.h"
#include "../Input_Control/Input_Control.h"

struct Table_t
{
	char acNo[8];
	// ̨�����
	int state;
	//̨��״̬��0-���� 1-ά�� 2-ռ�ã�
	char seat[20];
	// ̨��λ��

};

/************************************************************************
* �������ƣ�void Table_print(pList pt)
* ��Ҫ���ܣ�
		   ̨����Ϣ��ӡ����
* �β�˵����
*       pList pt    ̨�����ָ��
* ����ֵ��
*        ��
*************************************************************************/
void Table_print(pList pt);

/************************************************************************
* �������ƣ�void *Table_add(void *data)
* ��Ҫ���ܣ�
		   ̨��������Ӻ���
* �β�˵����
*       void *data    ̨�����һ���������ָ��
* ����ֵ��
*        ��������̨������ָ��
*************************************************************************/
void* Table_add(void* data);

/************************************************************************
* �������ƣ�int Table_remove(pList pL)
* ��Ҫ���ܣ�
		   ̨����ɾ������
* �β�˵����
*       pList pt    ̨�����ָ��
* ����ֵ��
*        ���سɹ�����־
*************************************************************************/
int Table_remove(pList pL);

/************************************************************************
* �������ƣ�int Table_update(pList pL)
* ��Ҫ���ܣ�
		   ̨�����ݸ��º���
* �β�˵����
*       pList pt    ̨�����ָ��
* ����ֵ��
*        ���سɹ�����־
*************************************************************************/
int Table_update(pList pL);

/************************************************************************
* �������ƣ�int Table_search(pList head,int n,int m)
* ��Ҫ���ܣ�
		   ̨����ѯ����
* �β�˵����
*       pList head     ̨��������ͷָ��
		int n          ̨��״̬
		int m          ̨��״̬
* ����ֵ��
*        ���سɹ�����־
*************************************************************************/
int Table_search(pList head, int n, int m);

#endif

