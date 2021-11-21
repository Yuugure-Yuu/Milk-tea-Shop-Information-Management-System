/************************************************************************
* �ļ����ƣ� Input_Control.c

* ���빦�ܣ�
*     ���ļ�ʵ�ֹ��ڿ�������Ĺ��ܡ�

*************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../Input_Control/Input_Control.h"


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

int Input_control(char acStr[],char start,char end,int iMaxLen,int iPutType)
{
	  int k = 0;
	  switch(iPutType)
		  // 1��������ĸ 2����������
       {
	     case 1:
               k = Input_control1(acStr,iMaxLen);
			   break;
	     case 2:
			   k = Input_control2(acStr,start,end,iMaxLen);
			   break;
		  default :
			   break;

       }
	      return k;
}


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

int Input_control1(char acStr[],int iMaxLen)
//�����ַ�����
{
     char t,y = 0;
  	 int  i;
	 i = 0;
    if (iMaxLen <= 10)
 {
     t = getch();
     while (i == 0 || t != 13) 
		 // �ж������ַ��ĺϷ���
	{
		 if (i>0 && t==8)
		{
			printf("\b \b"); 
			//ɾ���ַ�
			i--;
		}

		 else if(((t>='a'&&t<='z')||(t>='A'&&t<='Z')) && i < iMaxLen)
			 // �Ƿ�Ϊ��ĸ��λ����û�г�
		{
		     if(iMaxLen == 1)
			 {
			   if (t=='y'||t=='n')
				   // ѡ��ʱ
			   {
			   y = t;
			   printf("%c",y);
			   i++;
			   }

			 }
			 else
			 {
				acStr[i]=t;
				printf("%c",acStr[i]);
				i++;
			}
		}

		   t=getch();
}
           if (iMaxLen != 1)
           {
		    acStr[i] = '\0';
           }

}
        else
		{
            fflush(stdin);
		    gets(acStr);
			// ���뺺��
		}

        return (y);
		// ����y��n
}


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

int Input_control2(char acStr[],char start,char end,int iMaxLen)
//��������
{
         char t;
	     int i,n,k;
	     n = i = 0;
		 if (acStr != NULL&&acStr[0] != 0)
			 // �˱�ź�̨���ŵ���
		 {
			 k = strlen(acStr);
			 for (;acStr[i] != '\0';i++)
			 n = n*10+acStr[i] - 48;
			 // �ַ�ת��������
			 n = n+1;               
			 // ���ּ�һ
			 for(i=k-1;i>=0;i--)
			 {
				 acStr[i] = (n%10 + 48);
				 // ������ת�����ַ�
				 n = n/10;
			 }
                 acStr[k] = '\0';
		         return 0;
		 }

		t=getch();
	    while (i == 0 || t != 13)
	{
		if (t == 27&&acStr != NULL)
		{
			strcpy(acStr,"0");
			return 0;
		}
		if(i>0 && t==8)
			// ɾ����
		{
			printf("\b \b");
			i--;
		}

		else  if ((t>=start && t<=end) && i<iMaxLen)
			// ���뷶Χ�ĺϷ����ж�
	{
		  if (iMaxLen == 6)	
			  // �������룬������ʾ
		{
		    acStr[i]=t;
			printf("%c",'*');
			i++;
		}
        else if (iMaxLen == 1)
			  // ���湦�����ֵ�ѡ��
        {
		  n = t-48;
		  printf("%d",n);
		  i++;
        }
		   else
		   {
			 acStr[i]=t; 
			 // ������룬�����acStr��
			 printf("%c",t);
			 i++;
		   }
   }

		   t=getch();
}

		  if (iMaxLen == 1)
		  {
		    return n;
			//����һ�����֣���������ѡ��
		  }
		  else
		  {
		    acStr[i] = '\0';
		    for (i=0;acStr[i]!='\0';i++)
			n = n*10+acStr[i]-48;
			// �ַ�ת����int��
		    return n;
			//����int�͵����ݣ��������
		  }

}


