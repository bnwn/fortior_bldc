
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
* Description    : MDUģ���ʼ�����˷������λ���˷�ģʽ
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MDU_Init(void)
{
/*-----------------------------------------------------------------------------------
  �˷�����ʼ��
  00:�˷��������0λ	01:�˷��������8λ	10:�˷��������12λ	  11:�˷��������15λ
-----------------------------------------------------------------------------------*/
  SetBit(MD_MODE, ALIGN1, 0);
  SetBit(MD_MODE, ALIGN0, 0);          /*00:�˷��������0λ*/

  SetBit(MD_MODE, MDSN, 0);            /*ѡ���޷��ų˷�*/
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint16 MDU_MUL_U16(uint16 TData0, uint16 TData1)
	Description   :	16λ�޷��ų˷�������16λ�޷���ֵ���˻�����65535�������������ʱ��
									2.5us�������ڵ��ù�����������жϴ������ظ�����
	Input         :	TData0-����0��TData1-����1
  Output				:	MD_MB-�˻���16λ
-------------------------------------------------------------------------------------------------*/
uint16 MDU_MUL_U16(uint16 TData0, uint16 TData1)
{
	SetBit(MD_MODE, ALIGN1, 0);
	SetBit(MD_MODE, ALIGN0, 0);				                     // 00:�˷��������0λ						
	SetBit(MD_MODE, MDSN, 0);						                   // ѡ���޷��ų˷�

	MD_MA = TData0;
	MD_MB = TData1;								                         // д�������ͳ���
	
	return MD_MB;	

}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void MDU_MUL_U32(uint16 TData0, uint16 TData1, uint16 xdata *Result32)
	Description   :	16λ�޷��ų˷�������32λ�޷���ֵ������ʱ��3.2us�������ڵ��ù��������
                  ���жϴ������ظ�����
	Input         :	TData0-����0; TData1-����1; Result32-32bi�˻�����ָ��
-------------------------------------------------------------------------------------------------*/
void MDU_MUL_U32(uint16 TData0, uint16 TData1, uint16 xdata *Result32)
{

	SetBit(MD_MODE, ALIGN1, 0);
	SetBit(MD_MODE, ALIGN0, 0);				                     // 00:�˷��������0λ				
	SetBit(MD_MODE, MDSN, 0);							                 // ѡ���޷��ų˷�

	MD_MA = TData0;
	MD_MB = TData1;								                         // д�������ͳ���
	
	*Result32 = MD_MA;
	*(Result32+1) = MD_MB;
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	int16 MDU_MUL_S16(int16 TData0, int16 TData1)
	Description   :	16λ�з��ų˷�������16λ�з���ֵ���˻�����32767�������,����ʱ��
									2.5us�������ڵ��ù�����������жϴ������ظ�����
	Input         :	TData0-����0��TData1-����1
  Output				:	MD_MB-�˻���16λ
-------------------------------------------------------------------------------------------------*/
int16 MDU_MUL_S16(int16 TData0, int16 TData1)
{
	SetBit(MD_MODE, ALIGN1, 0);
	SetBit(MD_MODE, ALIGN0, 0);				                     // 00:�˷��������0λ				
	SetBit(MD_MODE, MDSN, 1);						                   // ѡ���з��ų˷�

	MD_MA = TData0;
	MD_MB = TData1;								                         // д�������ͳ���
	
	return MD_MB;
}

/*-------------------------------------------------------------------------------------------------
	Function Name : void MDU_MUL_S32(int16 TData0, int16 TData1, uint16 xdata *Result32)
	Description   :	32�з��ų˷�������32λ�з���ֵ������ʱ��3.2us�������ڵ��ù��������
                  ���жϴ������ظ�����
	Input         :	TData0-����0; TData1-����1; Result32-32bi�˻�����ָ��
-------------------------------------------------------------------------------------------------*/
void MDU_MUL_S32(int16 TData0, int16 TData1, uint16 xdata *Result32)
{	
	SetBit(MD_MODE, ALIGN1, 0);
	SetBit(MD_MODE, ALIGN0, 0);				                     // 00:�˷��������0λ				
	SetBit(MD_MODE, MDSN, 1);						                   // ѡ���з��ų˷�

	MD_MA = TData0;
	MD_MB = TData1;								                         // д�������ͳ���
	
	*Result32 = MD_MA;
	*(Result32+1) = MD_MB;
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint16 MDU_MULA_U16(uint16 TData0, uint16 TData1, uint8 ALIGN)
	Description   :	16λ�޷��ų˷�������16λ�޷���ֵ���˻�����65535�����������ѡ������
									�����λ������ʱ��3.0us�������ڵ��ù�����������жϴ������ظ�����
	Input         :	TData0-����0, TData1-����1, ALIGN-����λ��
  Output				:	MD_MB-�˻���16λ
-------------------------------------------------------------------------------------------------*/
uint16 MDU_MULA_U16(uint16 TData0, uint16 TData1, uint8 ALIGN)
{
	if(ALIGN == 8)
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 1);					               // 01:�˷��������8λ
	}
	else if(ALIGN == 12)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 0);				                 // 10:�˷��������12λ
	}
	else if(ALIGN == 15)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 1);					               // 11:�˷��������15λ
	}
	else
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 0);					               // 00:�˷��������0λ
	}
	
	SetBit(MD_MODE, MDSN, 0);						                   // ѡ���޷��ų˷�

	MD_MA = TData0;
	MD_MB = TData1;								                         // д�������ͳ���

	return MD_MB;
	
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void MDU_MULA_U32(uint16 TData0, uint16 TData1, uint8 ALIGN, uint16 xdata *Result32)
	Description   :	16λ�޷��ų˷�������32λ�޷���ֵ����ѡ����������λ������ʱ��4.8us��
									�����ڵ��ù�����������жϴ������ظ�����
	Input         :	TData0-����0��TData1-����1, ALIGN-����λ����Result32-32bit�˻����ָ��
-------------------------------------------------------------------------------------------------*/
void MDU_MULA_U32(uint16 TData0, uint16 TData1, uint8 ALIGN, uint16 xdata *Result32)
{
	if(ALIGN == 8)
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 1);					               // 01:�˷��������8λ
	}
	else if(ALIGN == 12)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 0);				                 // 10:�˷��������12λ
	}
	else if(ALIGN == 15)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 1);					               // 11:�˷��������15λ
	}
	else
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 0);					               // 00:�˷��������0λ
	}	

	SetBit(MD_MODE, MDSN, 0);							                 // ѡ���޷��ų˷�

	MD_MA = TData0;
	MD_MB = TData1;								                         // д�������ͳ���
	
	*Result32 = MD_MA;
	*(Result32+1) = MD_MB;	
	
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	int16 MDU_MULA_S16(int16 TData0, int16 TData1, uint8 ALIGN)
	Description   :	16λ�з��ų˷�������16λ�з���ֵ���˻�����32767�������,����ʱ��
									3.0us�������ڵ��ù�����������жϴ������ظ�����
	Input         :	TData0-����0��TData1-����1��ALIGN-����λ��
  Output				:	MD_MB-�˻���16λ
-------------------------------------------------------------------------------------------------*/
int16 MDU_MULA_S16(int16 TData0, int16 TData1, uint8 ALIGN)
{
	if(ALIGN == 8)
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 1);					               // 01:�˷��������8λ
	}
	else if(ALIGN == 12)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 0);				                 // 10:�˷��������12λ
	}
	else if(ALIGN == 15)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 1);					               // 11:�˷��������15λ
	}
	else
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 0);					               // 00:�˷��������0λ
	}		
	
	SetBit(MD_MODE, MDSN, 1);						                   // ѡ���з��ų˷�

	MD_MA = TData0;
	MD_MB = TData1;								                         // д�������ͳ���

	return MD_MB;		
	
}

/*-------------------------------------------------------------------------------------------------
	Function Name : void MDU_MULA_S32(int16 TData0, int16 TData1, uint8 ALIGN, uint16 xdata *Result32)
	Description   :	32�з��ų˷�������32λ�з���ֵ����ѡ����������λ������ʱ��4.8us��
									�����ڵ��ù�����������жϴ������ظ�����
	Input         :	TData0-����0��TData1-����1, ALIGN-����λ����Result32-32bit�˻����ָ��
-------------------------------------------------------------------------------------------------*/
void MDU_MULA_S32(int16 TData0, int16 TData1, uint8 ALIGN, uint16 xdata *Result32)
{

	if(ALIGN == 8)
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 1);					               // 01:�˷��������8λ
	}
	else if(ALIGN == 12)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 0);				                 // 10:�˷��������12λ
	}
	else if(ALIGN == 15)
	{
		SetBit(MD_MODE, ALIGN1, 1);
		SetBit(MD_MODE, ALIGN0, 1);					               // 11:�˷��������15λ
	}
	else
	{
		SetBit(MD_MODE, ALIGN1, 0);
		SetBit(MD_MODE, ALIGN0, 0);					               // 00:�˷��������0λ
	}	
		
	SetBit(MD_MODE, MDSN, 1);						                   // ѡ���з��ų˷�

	MD_MA = TData0;
	MD_MB = TData1;								                         // д�������ͳ���

	*Result32 = MD_MA;
	*(Result32+1) = MD_MB;		
}


/*-------------------------------------------------------------------------------------------------
	Function Name : uint16 MDU_DIV_U16(uint16 xdata *TData0, uint16 xdata *TData1)
	Description   :	16λ�޷��ų˷�������16λ�޷���ֵ������ʱ��6.4us�������ڵ��ù��������
                  ���жϴ������ظ�����
	Input         :	TData0-��������TData1-������32λ��������
  Output				:	MD_DAL-�̵�16λ
-------------------------------------------------------------------------------------------------*/
uint16 MDU_DIV_U16(uint16 xdata *TData0, uint16 xdata *TData1)
{
	MD_DAH = *TData0;
	MD_DAL = *(TData0+1);

	MD_DBH = *TData1;
	MD_DBL = *(TData1+1);
							

	SetBit(MD_MODE,DIVSTART,1);
	while(!GetBit(MD_MODE,DIVDONE));			                 // �ȴ�MDU�������			

  return MD_DAL;
					
}
/*-----------------------------------------------------------------------------------
	Function Name : uint32 MDU_DIV_U16(uint32 TData0, uint32 TData1)
	Description   :	32λ�޷��ų˷�������32λ�޷���ֵ������ʱ��54us�������ڵ��ù��������
                  ���жϴ������ظ�����
	Input         :	TData0-��������TData1-����
  Output				:	RData32-32λ��
-----------------------------------------------------------------------------------*/	
uint32 MDU_DIV_U32(uint32 TData0, uint32 TData1)
{
  uint32 RData32 = 0;

  FlagMDUDIV = 1;
  while(FlagMDUDIV)   // MDU��ʱ���ñ�־
  {
    FlagMDUDIV = 0;	
    
    while(!GetBit(MD_MODE,DIVDONE));			/*�ȴ�MDU�������*/	
    MD_DAH = TData0 >> 16;
    MD_DAL = TData0;										/*д32λ������*/
    MD_DBH = TData1 >> 16;
    MD_DBL = TData1;										/*д32λ����*/								

    SetBit(MD_MODE,DIVSTART,1);
    while(!GetBit(MD_MODE,DIVDONE));			/*�ȴ�MDU�������*/				

    RData32 += MD_DAH;
    RData32 <<= 16;
    RData32 += MD_DAL;									/*��32λ��*/
  }
  FlagMDUDIV = 1;
  return RData32;

}


/*-------------------------------------------------------------------------------------------------
	Function Name : uint32 MDU_DIV_U32(uint16 xdata *TData0, uint16 xdata *TData1, uint16 xdata *Result32)
	Description   :	32λ�޷��ų˷�������32λ�޷���ֵ������ʱ��7.2us�������ڵ��ù��������
                  ���жϴ������ظ�����
	Input         :	TData0-��������TData1-������32λ�������ͣ�Result32-32bit���ָ��
  Output				:	RData32-32λ��
-------------------------------------------------------------------------------------------------*/
//void MDU_DIV_U32(uint16 xdata *TData0, uint16 xdata *TData1, uint16 xdata *Result32)
//{	

//	MD_DAH = *TData0;
//	MD_DAL = *(TData0+1);

//	MD_DBH = *TData1;
//	MD_DBL = *(TData1+1);
//	
//	SetBit(MD_MODE,DIVSTART,1);
//	while(!GetBit(MD_MODE,DIVDONE));			                 // �ȴ�MDU�������			

//	*Result32 = MD_DAH;
//  *(Result32+1) = MD_DAL;
//}


