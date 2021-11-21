/************************************************************************
* 文件名称： Input_Control.h

* 代码功能：
*     本文件实现关于控制输入的功能。

*************************************************************************/
#ifndef _INPUT_CONRTOL_H_
#define _INPUT_CONRTOL_H_


/************************************************************************
* 函数名称：int Input_control(char acStr[],char start,char end,int iMaxLen,int iPutType)
* 主要功能：
*    控制输入函数
* 形参说明：
*    char acStr[]    存放输入的字符串
	 char start      输入的最小数字
	 char end        输入的最大数字
	 int iMaxLen     输入的最大位数
	 int iPutType    输入字母或数字的参数 1为字母，2为数字
* 返回值：
*       整型数据
*************************************************************************/
int Input_control(char acStr[], char start, char end, int iMaxLen, int iPutType);

/************************************************************************
* 函数名称：int Input_control1(char acStr[],int iMaxLen)
* 主要功能：
*         输入字母的函数
* 形参说明：
*    char acStr[]    存放输入的字符串
	 int iMaxLen     输入的最大位数
* 返回值：
*       整型数据
*************************************************************************/
int Input_control1(char acStr[], int iMaxLen);

/************************************************************************
* 函数名称：int Input_control2(char acStr[],char start,char end,int iMaxLen)
* 主要功能：
*         输入数字的函数
* 形参说明：
*    char acStr[]    存放输入的字符串
	 char start      输入的最小数字
	 char end        输入的最大数字
	 int iMaxLen     输入的最大位数
* 返回值：
*       整型数据
*************************************************************************/
int Input_control2(char acStr[], char start, char end, int iMaxLen);

#endif