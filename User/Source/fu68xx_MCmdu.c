
/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        : 
********************************************************************************
/*******************************************************************************
* All Rights Reserved
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <FU68xx.h>
#include "sys_conf.h"
/* Private typedef -----------------------------------------------------------*/
bit FlagMDUMUL = 0;
bit FlagMDUDIV = 0;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : MDU_Init
* Description    : MDU模块初始化，乘法结果移位，乘法模式
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MDU_Init(void)
{
/*-----------------------------------------------------------------------------------
  乘法器初始化
  00:乘法结果右移0位	01:乘法结果右移8位	10:乘法结果右移12位	  11:乘法结果右移15位
-----------------------------------------------------------------------------------*/
  SetBit(MD_MODE, ALIGN1, 0);
  SetBit(MD_MODE, ALIGN0, 0);          /*00:乘法结果右移0位*/

  SetBit(MD_MODE, MDSN, 0);            /*选择无符号乘法*/
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint16 MDU_MUL_U16(uint16 TData0, uint16 TData1)
	Description   :	16位无符号乘法，返回16位无符号值，乘积大于65535计算溢出，运行时间
									2.5us，函数在调用过程中如果被中断打断则会重复调用
	Input         :	TData0-乘数0，TData1-乘数1
  Output				:	MD_MB-乘积低16位
-------------------------------------------------------------------------------------------------*/
uint16 MDU_MUL_U16(uint16 TData0, uint16 TData1)
{
	SetBit(MD_MODE, ALIGN1, 0);
	SetBit(MD_MODE, ALIGN0, 0);				                     // 00:乘法结果右移0位						
	SetBit(MD_MODE, MDSN, 0);						                   // 选择无符号乘法

	MD_MA = TData0;
	MD_MB = TData1;								                         // 写被乘数和乘数
	
	return MD_MB;	

}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void MDU_MUL_U32(uint16 TData0, uint16 TData1, uint16 xdata *Result32)
	Description   :	16位无符号乘法，返回32位无符号值，运行时间3.2us，函数在调用过程中如果
                  被中断打断则会重复调用
	Input         :	TData0-乘数0; TData1-乘数1; Result32-32bi乘积变量指针
-------------------------------------------------------------------------------------------------*/
void MDU_MUL_U32(uint16 TData0, uint16 TData1, uint16 xdata *Result32)
{

	SetBit(MD_MODE, ALIGN1, 0);
	SetBit(MD_MODE, ALIGN0, 0);				                     // 00:乘法结果右移0位				
	SetBit(MD_MODE, MDSN, 0);							                 // 选择无符号乘法

	MD_MA = TData0;
	MD_MB = TData1;								                         // 写被乘数和乘数
	
	*Result32 = MD_MA;
	*(Result32+1) = MD_MB;
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	int16 MDU_MUL_S16(int16 TData0, int16 TData1)
	Description   :	16位有符号乘法，返回16位有符号值，乘积大于32767计算溢出,运行时间
									2.5us，函数在调用过程中如果被中断打断则会重复调用
	Input         :	TData0-乘数0，TData1-乘数1
  Output				:	MD_MB-乘积低16位
-------------------------------------------------------------------------------------------------*/
int16 MDU_MUL_S16(int16 TData0, int16 TData1)
{
	SetBit(MD_MODE, ALIGN1, 0);
	SetBit(MD_MODE, ALIGN0, 0);				                     // 00:乘法结果右移0位				
	SetBit(MD_MODE, MDSN, 1);						                   // 选择有符号乘法

	MD_MA = TData0;
	MD_MB = TData1;								                         // 写被乘数和乘数
	
	return MD_MB;
}

/*-------------------------------------------------------------------------------------------------
	Function Name : void MDU_MUL_S32(int16 TData0, int16 TData1, uint16 xdata *Result32)
	Description   :	32有符号乘法，返回32位有符号值，运行时间3.2us，函数在调用过程中如果
                  被中断打断则会重复调用
	Input         :	TData0-乘数0; TData1-乘数1; Result32-32bi乘积变量指针
-------------------------------------------------------------------------------------------------*/
void MDU_MUL_S32(int16 TData0, int16 TData1, uint16 xdata *Result32)
{	
	SetBit(MD_MODE, ALIGN1, 0);
	SetBit(MD_MODE, ALIGN0, 0);				                     // 00:乘法结果右移0位				
	SetBit(MD_MODE, MDSN, 1);						                   // 选择有符号乘法

	MD_MA = TData0;
	MD_MB = TData1;								                         // 写被乘数和乘数
	
	*Result32 = MD_MA;
	*(Result32+1) = MD_MB;
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint16 MDU_MULA_U16(uint16 TData0, uint16 TData1, uint8 ALIGN)
	Description   :	16位无符号乘法，返回16位无符号值，乘积大于65535计算溢出，可选择运算
									结果移位，运行时间3.0us，函数在调用过程中如果被中断打断则会重复调用
	Input         :	TData0-乘数0, TData1-乘数1, ALIGN-左移位数
  Output				:	MD_MB-乘积低16位
-------------------------------------------------------------------------------------------------*/
uint16 MDU_MULA_U16(uint16 TData0, uint16 TData1, uint8 ALIGN)
{
	if(ALIGN == 8)
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 1);					               // 01:乘法结果右移8位
	}
	else if(ALIGN == 12)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 0);				                 // 10:乘法结果右移12位
	}
	else if(ALIGN == 15)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 1);					               // 11:乘法结果右移15位
	}
	else
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 0);					               // 00:乘法结果右移0位
	}
	
	SetBit(MD_MODE, MDSN, 0);						                   // 选择无符号乘法

	MD_MA = TData0;
	MD_MB = TData1;								                         // 写被乘数和乘数

	return MD_MB;
	
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void MDU_MULA_U32(uint16 TData0, uint16 TData1, uint8 ALIGN, uint16 xdata *Result32)
	Description   :	16位无符号乘法，返回32位无符号值，可选择运算结果移位，运行时间4.8us，
									函数在调用过程中如果被中断打断则会重复调用
	Input         :	TData0-乘数0，TData1-乘数1, ALIGN-左移位数，Result32-32bit乘积结果指针
-------------------------------------------------------------------------------------------------*/
void MDU_MULA_U32(uint16 TData0, uint16 TData1, uint8 ALIGN, uint16 xdata *Result32)
{
	if(ALIGN == 8)
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 1);					               // 01:乘法结果右移8位
	}
	else if(ALIGN == 12)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 0);				                 // 10:乘法结果右移12位
	}
	else if(ALIGN == 15)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 1);					               // 11:乘法结果右移15位
	}
	else
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 0);					               // 00:乘法结果右移0位
	}	

	SetBit(MD_MODE, MDSN, 0);							                 // 选择无符号乘法

	MD_MA = TData0;
	MD_MB = TData1;								                         // 写被乘数和乘数
	
	*Result32 = MD_MA;
	*(Result32+1) = MD_MB;	
	
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	int16 MDU_MULA_S16(int16 TData0, int16 TData1, uint8 ALIGN)
	Description   :	16位有符号乘法，返回16位有符号值，乘积大于32767计算溢出,运行时间
									3.0us，函数在调用过程中如果被中断打断则会重复调用
	Input         :	TData0-乘数0，TData1-乘数1，ALIGN-左移位数
  Output				:	MD_MB-乘积低16位
-------------------------------------------------------------------------------------------------*/
int16 MDU_MULA_S16(int16 TData0, int16 TData1, uint8 ALIGN)
{
	if(ALIGN == 8)
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 1);					               // 01:乘法结果右移8位
	}
	else if(ALIGN == 12)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 0);				                 // 10:乘法结果右移12位
	}
	else if(ALIGN == 15)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 1);					               // 11:乘法结果右移15位
	}
	else
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 0);					               // 00:乘法结果右移0位
	}		
	
	SetBit(MD_MODE, MDSN, 1);						                   // 选择有符号乘法

	MD_MA = TData0;
	MD_MB = TData1;								                         // 写被乘数和乘数

	return MD_MB;		
	
}

/*-------------------------------------------------------------------------------------------------
	Function Name : void MDU_MULA_S32(int16 TData0, int16 TData1, uint8 ALIGN, uint16 xdata *Result32)
	Description   :	32有符号乘法，返回32位有符号值，可选择运算结果移位，运行时间4.8us，
									函数在调用过程中如果被中断打断则会重复调用
	Input         :	TData0-乘数0，TData1-乘数1, ALIGN-左移位数，Result32-32bit乘积结果指针
-------------------------------------------------------------------------------------------------*/
void MDU_MULA_S32(int16 TData0, int16 TData1, uint8 ALIGN, uint16 xdata *Result32)
{

	if(ALIGN == 8)
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 1);					               // 01:乘法结果右移8位
	}
	else if(ALIGN == 12)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 0);				                 // 10:乘法结果右移12位
	}
	else if(ALIGN == 15)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 1);					               // 11:乘法结果右移15位
	}
	else
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 0);					               // 00:乘法结果右移0位
	}	
		
	SetBit(MD_MODE, MDSN, 1);						                   // 选择有符号乘法

	MD_MA = TData0;
	MD_MB = TData1;								                         // 写被乘数和乘数

	*Result32 = MD_MA;
	*(Result32+1) = MD_MB;		
}


/*-------------------------------------------------------------------------------------------------
	Function Name : uint16 MDU_DIV_U16(uint16 xdata *TData0, uint16 xdata *TData1)
	Description   :	16位无符号乘法，返回16位无符号值，运行时间6.4us，函数在调用过程中如果
                  被中断打断则会重复调用
	Input         :	TData0-被除数，TData1-除数，32位数据类型
  Output				:	MD_DAL-商低16位
-------------------------------------------------------------------------------------------------*/
uint16 MDU_DIV_U16(uint16 xdata *TData0, uint16 xdata *TData1)
{
	MD_DAH = *TData0;
	MD_DAL = *(TData0+1);

	MD_DBH = *TData1;
	MD_DBL = *(TData1+1);
							

	SetBit(MD_MODE,DIVSTART,1);
	while(!GetBit(MD_MODE,DIVDONE));			                 // 等待MDU计算完成			

  return MD_DAL;
					
}
/*-----------------------------------------------------------------------------------
	Function Name : uint32 MDU_DIV_U16(uint32 TData0, uint32 TData1)
	Description   :	32位无符号乘法，返回32位无符号值，运行时间54us，函数在调用过程中如果
                  被中断打断则会重复调用
	Input         :	TData0-被除数，TData1-除数
  Output				:	RData32-32位商
-----------------------------------------------------------------------------------*/	
uint32 MDU_DIV_U32(uint32 TData0, uint32 TData1)
{
  uint32 RData32 = 0;

  FlagMDUDIV = 1;
  while(FlagMDUDIV)   // MDU分时复用标志
  {
    FlagMDUDIV = 0;	
    
    while(!GetBit(MD_MODE,DIVDONE));			/*等待MDU计算完成*/	
    MD_DAH = TData0 >> 16;
    MD_DAL = TData0;										/*写32位被除数*/
    MD_DBH = TData1 >> 16;
    MD_DBL = TData1;										/*写32位除数*/								

    SetBit(MD_MODE,DIVSTART,1);
    while(!GetBit(MD_MODE,DIVDONE));			/*等待MDU计算完成*/				

    RData32 += MD_DAH;
    RData32 <<= 16;
    RData32 += MD_DAL;									/*读32位商*/
  }
  FlagMDUDIV = 1;
  return RData32;

}


/*-------------------------------------------------------------------------------------------------
	Function Name : uint32 MDU_DIV_U32(uint16 xdata *TData0, uint16 xdata *TData1, uint16 xdata *Result32)
	Description   :	32位无符号乘法，返回32位无符号值，运行时间7.2us，函数在调用过程中如果
                  被中断打断则会重复调用
	Input         :	TData0-被除数，TData1-除数，32位数据类型，Result32-32bit结果指针
  Output				:	RData32-32位商
-------------------------------------------------------------------------------------------------*/
//void MDU_DIV_U32(uint16 xdata *TData0, uint16 xdata *TData1, uint16 xdata *Result32)
//{	

//	MD_DAH = *TData0;
//	MD_DAL = *(TData0+1);

//	MD_DBH = *TData1;
//	MD_DBL = *(TData1+1);
//	
//	SetBit(MD_MODE,DIVSTART,1);
//	while(!GetBit(MD_MODE,DIVDONE));			                 // 等待MDU计算完成			

//	*Result32 = MD_DAH;
//  *(Result32+1) = MD_DAL;
//}


