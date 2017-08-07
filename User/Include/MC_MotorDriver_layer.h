
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
#ifndef __MC_MOTORDRIVER_LAYER_H
#define __MC_MOTORDRIVER_LAYER_H
#include "fu68xx_Dmc.h"
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct 
  {
    int16 ImeasAGain;        // Parameter: gain for Ia (Q13)  
    int16 ImeasAOffset;      // Parameter: offset for Ia (Q15)  
    int16 ImeasA;            // Output: measured Ia (Q15)  
    int16 ImeasBGain;        // Parameter: gain for Ib (Q13)  
    int16 ImeasBOffset;      // Parameter: offset for Ib (Q15)  
    int16 ImeasB;            // Output: measured Ib (Q15) 
    int16 ImeasCGain;        // Parameter: gain for Ib (Q13)  
    int16 ImeasCOffset;      // Parameter: offset for Ib (Q15)  
    int16 ImeasC;            // Output: measured Ib (Q15)    

    __IO float VmeasAGain;     // Parameter: gain for Ib (Q13)  
    __IO int16 VmeasAOffset;   // Parameter: offset for Ib (Q15)  
    __IO int16 VmeasA;         // Output: measured Ib (Q15)    
    __IO float Va;             //实际值
    __IO float VmeasBGain;     // Parameter: gain for Ib (Q13)  
    __IO int16 VmeasBOffset;   // Parameter: offset for Ib (Q15)  
    __IO int16 VmeasB;         // Output: measured Ib (Q15)   
    __IO float Vb;
    __IO float VmeasCGain;     // Parameter: gain for Ib (Q13)  
    __IO int16 VmeasCOffset;   // Parameter: offset for Ib (Q15)  
    __IO int16 VmeasC;         // Output: measured Ib (Q15)         
    __IO float Vc;

    __IO float VdcMeasGain;    // Parameter: gain for Vdc (Q13)  
    __IO int16 VdcMeasOffset;  // Parameter: offset for Vdc (Q15)  
    __IO int16 VdcMeas;        // Output: measured Vdc (Q15)  
    __IO float Vdc; 
    __IO float IBusMeasGain;   // Parameter: gain for Ia (Q13)  
    __IO int16 IBusMeasOffset; // Parameter: offset for Ia (Q15)  
    __IO int16 ImeasBus;       // Output: measured Ia (Q15)  
    __IO float Ibus; 
    
    __IO int16 Vth1Meas;       // Output: measured VthMeas (Q12) 
    __IO int16 Vth1;
    __IO float Therm1;
    __IO int16 Vth2Meas;      // Output: measured Vth1Meas (Q12) 
    __IO int16 Vth2;
    __IO float Therm2;
    __IO int16 Vth3Meas;      // Output: measured Vth1Meas (Q12) 
    __IO int16 Vth3;
    __IO float Therm3;
    
    __IO int16 SrefMeas;      // Output: measured VthMeas (Q12)
    __IO int16 Sref;          
    __IO uint16 ChSelect;      // Parameter: ADC channel selection
  } ADC2MEAS_TypeDef; 

//CTL
typedef struct   
  {
    __IO s8  BemfSetFR;
    __IO s8  BemfValue;                     //过零点值
    __IO u8  BemfNum; 
    __IO s16 BemfTabA,BemfTabB,RefNumZ,RefNumY,RefNumX;     //
    __IO u8  BemfFR;                        //
    __IO u8  Calcnum;                       //转速跟踪检测次数
    __IO u16 Calcnms;                       //转速跟踪检测时间
  } Stk_TypeDef;
  
typedef struct
  {
   __IO  u8  Status;                 //HALL状态 1~6
   __IO  u8  Section;                //扇区     1~6
   __IO  u8  u8ChangePhaseNum;       //换相次数         
   __IO  s16 s16AdvanceEangle;       //换相超前角度
   __IO  u8  u8ChangePhaseFlag;      //换相完成标志  0XFF 已经换相 0X7F 准备换相
  } HALL_TypeDef;
  
typedef struct
{   
    __IO u16  PwmArr;
    __IO u16  DutyCurrent;
    __IO u16  Dutytarget;
    __IO u16  DutytargetOpen;

    __IO u16  DutyIncValue;        
    __IO u16  DutyDecValue;

    __IO u16  DutyMax;
    __IO u16  DutyMin;  
    __IO u16  u16cycle;
    __IO u16  DutyLimitMaxRef;
    __IO u16  DutyLimitFlag;
    __IO u16  DutyLimitADD;
  
  
}PWM_TypeDef;
  
typedef struct
{
  __IO PWM_TypeDef        PWM;               //PWM

  ADC2MEAS_TypeDef        AdcMeas;           //ADC检测值
  HALL_TypeDef            Hall;              //hall
  SPEED_MEAS_CAP          speed;             //速度计算
  Stk_TypeDef             Stk;
}DRV_TypeDef;
  
extern DRV_TypeDef xdata Drv;              //全局外部变量声明
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/*******************************************************************************
* Function Name  : Drv_DutyRampCale 
* Description    : 计算频率，每次斩波计算一次 
* Input          : 目标DUTY  格式_IQ15 即0x7FFF
* Output         : 当先DUTY  格式_IQ15 即0x7FFF
* Return         : 1
*******************************************************************************/  
extern u16 Drv_DutyRampCale(u16 tduty);    //开环加减速模块

/*******************************************************************************
* Function Name  : Drv_SpeedRampCale 闭环加减速曲线
* Description    : 速度闭环加减速曲线 开环无效
* Input          : 目标速度 refTar _IQ15格式
* Output         : 给定速度 refCur _IQ15格式
* Return         : 给定速度 refCur _IQ15格式
*******************************************************************************/
extern u16 Drv_SpeedRampCale(u16 refTar);  //闭环加减速模块

/*******************************************************************************
* Function Name  : Drv_Commutation 换相
* Description    : 换相模块，根据电机转子扇腔幌帏
* Input          : 换相扇区
* Output         : None
* Return         : 1
*******************************************************************************/
extern u8 Drv_Commutation(u8 Step);        //换相模块

/*******************************************************************************
* Function Name  : Fu68xx_PWM_Update
* Description    : PWM更新模块，每次斩波更新，实时更新
* Input          : _IQ15 格式duty
* Output         : TIM2_DR
* Return         : TIM2_DR
*******************************************************************************/
extern u16 Fu68xx_PWM_Update(u16 tduty);   //PWM更新模块

/*******************************************************************************
* Function Name  : Drv_SetStep    
* Description    : 换相区间设置
* Input          : ANGLE 整数
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_SetStep(void);

/*******************************************************************************
* Function Name  : Drv_HallDriveD    
* Description    : hall中断来了，直接换相 不超前不滞后
* Input          : Step
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_HallDriveD(u8 Step);

/*******************************************************************************
* Function Name  : Drv_Stb3Calc    
* Description    : 失速检测
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_Stb3Calc(void);
                
/*******************************************************************************
* Function Name  : Drv_SelfInspection    
* Description    : mos自检
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern u8 Drv_SelfInspection(u8 Num,float Value1,float Value2);//mos自检
#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/