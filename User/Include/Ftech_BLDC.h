
/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        : ���棺��ֹ�޸�,ɾ�� �ṹ�嶨�� ����ᵼ��δ֪����
********************************************************************************
/*******************************************************************************
* All Rights Reserved
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FTECH_BLDCC_H
#define __FTECH_BLDCC_H
#include "fu68xx_Dmc.h"
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

extern u16 MC_PWMARR;
extern u16 MC_RampDetecBEMFCntFilt;
extern u16 MC_RampMaskTime;
/*******************************************************************************
* Function Name  : Drv_HallDrive ����
* Description    : ��HALL����ģ�飬�ں���ǰ����
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/
extern void Drv_HallDriveS(u8 Step);
/*******************************************************************************
* Function Name  : Mcl_BemfPhaseChoice    
* Description    : �����Ƽ����ѡ�񣬸�����Ҫ����� ������Ӧ�ıȽ���
* Input          : Step
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfPhaseChoice(u8 Step);   

/*******************************************************************************
* Function Name  : Mcl_BemfdelayAngle    
* Description    : �����Ƽ�⣬��ʱ�Ƕ�
* Input          : ANGLE ����
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfdelayAngle(u16 Angle);

/*******************************************************************************
* Function Name  : Drv_BemfMaskAngle    
* Description    : �����Ƽ�⣬��ʱ�Ƕ�
* Input          : ANGLE ����
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfMaskAngle(u16 Angle);

/*******************************************************************************
* Function Name  : Drv_BemfTim1PDapp    
* Description    : BEMF�����Ƽ��
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfTim1PDapp(void) ;        

/*******************************************************************************
* Function Name  : Drv_BemfTim1RUapp    
* Description    : bemf�����жϷ�����  ������ʱ���࣬����ʱ������
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfTim1RUapp(void) ;           

/*******************************************************************************
* Function Name  : Drv_SectionCheak    
* Description    : ת�ٸ�������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
extern u8 Drv_SectionCheak(void);

/*******************************************************************************
* Function Name  : Drv_SelfInspection    
* Description    : ׼����ʼ��MOS���Լ�
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern u8 Drv_SelfInspection(u8 Num,float Value1,float Value2);
#endif