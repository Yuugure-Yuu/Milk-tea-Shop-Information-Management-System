/************************************************************************
* �ļ����ƣ� Input_Control.h

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ��ڿ�������Ĺ��ܡ�

*************************************************************************/
#ifndef _INPUT_CONRTOL_H_
#define _INPUT_CONRTOL_H_


/************************************************************************
* �������ƣ�int Input_control(char acStr[],char start,char end,int iMaxLen,int iPutType)
* ��Ҫ���ܣ�
*    �������뺯��
* �β�˵����
*    char acStr[]    ���������ַ���
	 char start      �������С����
	 char end        ������������
	 int iMaxLen     ��������λ��
	 int iPutType    ������ĸ�����ֵĲ��� 1Ϊ��ĸ��2Ϊ����
* ����ֵ��
*       ��������
*************************************************************************/
int Input_control(char acStr[], char start, char end, int iMaxLen, int iPutType);

/************************************************************************
* �������ƣ�int Input_control1(char acStr[],int iMaxLen)
* ��Ҫ���ܣ�
*         ������ĸ�ĺ���
* �β�˵����
*    char acStr[]    ���������ַ���
	 int iMaxLen     ��������λ��
* ����ֵ��
*       ��������
*************************************************************************/
int Input_control1(char acStr[], int iMaxLen);

/************************************************************************
* �������ƣ�int Input_control2(char acStr[],char start,char end,int iMaxLen)
* ��Ҫ���ܣ�
*         �������ֵĺ���
* �β�˵����
*    char acStr[]    ���������ַ���
	 char start      �������С����
	 char end        ������������
	 int iMaxLen     ��������λ��
* ����ֵ��
*       ��������
*************************************************************************/
int Input_control2(char acStr[], char start, char end, int iMaxLen);

#endif