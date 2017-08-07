
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
#include "fu68xx_MClpf.h"
#include "MC_MotorCotrol_layer.h"  
#include "MC_MotorDriver_layer.h" 
#include "MC_PwmIn.h"
#include "MC_Beep.h"
#include "fu68xx_Dmc.h"
/** @addtogroup FT68xx
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
MDUControl_TypeDef xdata MDUControl;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void speed_prd_calc(void);     //速度计算
void MDUInit(void);
void MDUControlInit(void);
void MDUAPP(void);
/*******************************************************************************
* Function Name  : speed_prd_calc    
* Description    : 速度计算模块，根据HALL信号计算速度
* Input          : TIM1_BCCR
* Output         : 速度单位 RPM
* Return         : 无
*******************************************************************************/
void PDEventPeriodCalc(void)
{
  if(TIM1_BCCR > SRB3TIMEFILT)
  {
    Drv.speed.EventPeriod = TIM1_BCCR;  
    //if(Drv.speed.EventPeriod > 1)
    {
      Ctl.Section.Cur = Drv.speed.EventPeriod;
      Drv_Stb3Calc();
    }    
  }
  //Ctl.Section.S[Ctl.Step] = v->EventPeriod;
  Ctl.Section.Counter++;   
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void MDU_Init(void)
	Description   :	MDU模块初始化，乘法结果移位，乘法模式
	Input         :	None
  Output				:	None
-------------------------------------------------------------------------------------------------*/
void MDUInit(void)
{
/*-------------------------------------------------------------------------------------------------
	乘法器初始化
  00:乘法结果右移0位	01:乘法结果右移8位	10:乘法结果右移12位	  11:乘法结果右移15位
-------------------------------------------------------------------------------------------------*/
  SetBit(MD_MODE, ALIGN1, 0);
  SetBit(MD_MODE, ALIGN0, 0);				                       // 00:乘法结果右移0位	

  SetBit(MD_MODE, MDSN, 0);						                     // 选择无符号乘法

  MDUControlInit();
}

/*-------------------------------------------------------------------------------------------------
	Function Name : void MDUControlInit(void)
	Description   :	MDU控制函数标志位初始化
	Input         :	无
  Output				:	无
-------------------------------------------------------------------------------------------------*/
void MDUControlInit(void)
{

  #if(ADCSREF_EN) 
  MDUControl.AlineX2 = ADCSREFINMAX;
  MDUControl.AlineX1 = ADCSREFINMIN;
  //MDUControl.SpeedSref = Drv.AdcMeas.Sref;
  MDUControl.SpeedSrefErr = (u32)(MDUControl.AlineX2 - MDUControl.AlineX1);
  
  MDUControl.AlineA = (u16)(ADCAlineA*32767);
  MDUControl.AlineB = ADCAlineB;
  #endif
  
  MDUControl.FlagPWMDuty = 0;

  MDUControl.FlagDelayAngleTime = 0;
  MDUControl.FlagMaskAngleTime = 0;
  
  MDUControl.FlagCalcSpeed = 0;
  MDUControl.FlagCalcSpeedRpm = 0;
}
/*-------------------------------------------------------------------------------------------------
	Function Name : void MDUAPP(void)
	Description   :	MDU控制函数，运行频率为PWMFre(16K)，最高优先级，软件系统的所有MDU运算都在此函数
                  执行，函数扫描到相应的标志位后进行相应的运算。
	Input         :	无
  Output				:	无
-------------------------------------------------------------------------------------------------*/
void MDUAPP(void)
{
  if(MDUControl.FlagMaskAngleTime == 0x7F)
  {
    MDUControl.MaskAngleOut = MDU_MULA_U16(Drv.speed.EventPeriod, MDUControl.MaskAngleIn, 15); 
    MDUControl.FlagMaskAngleTime = 0XFF;
  }
  if(MDUControl.FlagDelayAngleTime == 0x7F)
  {
    MDUControl.DelayAngleOut =MDU_MULA_U16(Drv.speed.EventPeriod, MDUControl.DelayAngleIn, 15); 
    MDUControl.FlagDelayAngleTime = 0XFF;
  }
  if(MDUControl.FlagPWMDuty == 0x7F)
  {
      if(Ctl.State == MOTOR_STOP)
      {
        if(Beep.BeepRequest != 0x7F)
        {
          TIM2_DR = MDU_MULA_U16(MDUControl.DutyCurrent,PWMARR,15);
        }
      }    
      else if(Ctl.State == MOTOR_OPENLOOP)
      {
        TIM2_DR = MDU_MULA_U16(MDUControl.DutyCurrent,RAMP_PWMARR,15);
      }
      else
      {
        TIM2_DR = MDU_MULA_U16(MDUControl.DutyCurrent,PWMARR,15);
      }
      if(TIM2_DR < RAMP_PWMARR>>1)
      {
        TIM2_CMTR = TIM2_DR+(RAMP_PWMARR - TIM2_DR)>>1;
      }
      else
      {
        TIM2_CMTR = TIM2_DR>>1; 
      }

      TIM2_ADTR = TIM2_DR>>1; 
      MDUControl.FlagPWMDuty = 0xFF;
  }

  if(MDUControl.FlagCalcSpeed == 0x7F)
  {
    Drv.speed.Speed = MDU_DIV_U32(Drv.speed.SpeedScaler,Drv.speed.EventPeriod);//速度标幺值计算 
    MDUControl.FlagCalcSpeed = 0xFF;
  }
  if(MDUControl.FlagCalcSpeedRpm == 0x7F)
  {
    MDU_MULA_U32(Drv.speed.Speed,Drv.speed.BaseRpm,15,&Drv.speed.SpeedRpm );     //实际转速计算
    MDUControl.FlagCalcSpeedRpm = 0xFF;
  } 
  
  if(MDUControl.FlagTargetSpeed == 0x7F)
  {    if(MDUControl.SpeedSref > MDUControl.AlineX1)
    {  
      //y = A*x + B ;
      MDUControl.TargetSpeed = MDU_MULA_U16(MDUControl.SpeedSref,MDUControl.AlineA,15) + MDUControl.AlineB;
    }
    MDUControl.FlagTargetSpeed = 0xFF;
  }    
}
  