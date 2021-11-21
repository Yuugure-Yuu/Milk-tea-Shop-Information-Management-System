/************************************************************************
* �ļ����ƣ� Order.h

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ��ڵ�͵Ĺ��ܡ�

*************************************************************************/
#ifndef _ORDER_H_
#define _ORDER_H_

#include <conio.h>
#include "../File/File.h"
#include "../List/List.h"
#include "../Table/Table.h"
#include "../Menu/Menu.h"
#include "../Log_in/Log_in.h"
#include "../Input_Control/Input_Control.h"

struct Order_t
	//����
{
	char ordernum[15];
	//������
	char acname[10];
	// ���˷���Ա
	char tablenum[6];
	// ̨����
	int money;
	//�ܽ��
	int amount;
	//�ܷ���
};

struct Title_t
	//�굥
{
	char ordernum[15];
	//������
	struct Menu_t pMenu;
	// ĳһ����
	int amount;
	// ĳһ���˵ķ���
	//int food_nums;
};
/**************************************************************************/


/************************************************************************
* �������ƣ�struct Order_t *Order_init(char str[])
* ��Ҫ���ܣ�
		   �����ṹ���ʼ������
* �β�˵����
*       char str[]  ��˵�̨����
* ����ֵ��
*        ���س�ʼ���Ķ������ָ��
*************************************************************************/
struct Order_t* Order_init(char str[]);

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
struct Title_t* Title_init(struct Order_t* pNew, struct Menu_t* data, int n);

/************************************************************************
* �������ƣ�void Order_add(int count1,struct Order_t *pNew,pList pTitle,pList pOrder,pList pMenu,char tabpath[])
* ��Ҫ���ܣ�
		   �Ӳ˹��ܺ���
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
void Order_add(int count1, struct Order_t* pNew, pList pTitle, pList pOrder, pList pMenu, char tabpath[]);
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
void Order_del(int count1, struct Order_t* pNew, pList pTitle, pList pMenu, pList pOrder, char tabpath[]);

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
void Order_statist(struct Order_t* pNew, pList pTitle);

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
void Order_print(pList pMenu, pList pTitle, struct Order_t* pNew);

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
long Ordernum_get(char num[], char str[]);

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
void Orderdate_input(long* stardate, long* enddate);

/************************************************************************
* �������ƣ�void convert(char s[],int data,int n)
* ��Ҫ���ܣ�
		   ����ת������
* �β�˵����
*       char s[]     ���ת�����
		int data    ��ת��������
		int n       ���ڵ�λ��
* ����ֵ��
*        ��
*************************************************************************/
void convert(char s[], int data, int n);

/************************************************************************
* �������ƣ�void Order_search_unbuy(pList pOrder,pList pTable)
* ��Ҫ���ܣ�
		   δ�򶩵���ѯ����
* �β�˵����
*      pList pOrder     ������ͷָ��

* ����ֵ��
*        ��
*************************************************************************/
void Order_search_unbuy(pList pOrder);

/************************************************************************
* �������ƣ�void Order_search_buy()
* ��Ҫ���ܣ�
		   ���򶩵���ѯ����
* �β�˵����
*        ��
* ����ֵ��
*        ��
*************************************************************************/
void Order_search_buy();

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
void Title_print(pList pTitle, struct Order_t* pOrder);

#endif


