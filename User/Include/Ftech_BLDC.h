
/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        : 警告：禁止修改,删除 结构体定义 否则会导致未知错误
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
* Function Name  : Drv_HallDrive 换相
* Description    : 有HALL换相模块，内含超前换相
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/
extern void Drv_HallDriveS(u8 Step);
/*******************************************************************************
* Function Name  : Mcl_BemfPhaseChoice    
* Description    : 反电势检测相选择，根据需要检测相 开启相应的比较器
* Input          : Step
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfPhaseChoice(u8 Step);   

/*******************************************************************************
* Function Name  : Mcl_BemfdelayAngle    
* Description    : 反电势检测，延时角度
* Input          : ANGLE 整数
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfdelayAngle(u16 Angle);

/*******************************************************************************
* Function Name  : Drv_BemfMaskAngle    
* Description    : 反电势检测，延时角度
* Input          : ANGLE 整数
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfMaskAngle(u16 Angle);

/*******************************************************************************
* Function Name  : Drv_BemfTim1PDapp    
* Description    : BEMF反电势检测
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfTim1PDapp(void) ;        

/*******************************************************************************
* Function Name  : Drv_BemfTim1RUapp    
* Description    : bemf下溢中断服务函数  用于延时换相，续流时间屏蔽
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_BemfTim1RUapp(void) ;           

/*******************************************************************************
* Function Name  : Drv_SectionCheak    
* Description    : 转速跟踪启动
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
extern u8 Drv_SectionCheak(void);

/*******************************************************************************
* Function Name  : Drv_SelfInspection    
* Description    : 准备开始做MOS管自检
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern u8 Drv_SelfInspection(u8 Num,float Value1,float Value2);
#endif