
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FU68XX_DMC_H
#define __FU68XX_DMC_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
  //u32 NewTimeStamp;  // Variable : New 'Timestamp' corresponding to a capture event (Q0) - independently with global Q 
  //u32 OldTimeStamp;  // Variable : Old 'Timestamp' corresponding to a capture event (Q0) - independently with global Q 
  //u16 TimeStamp;     // Input : Current 'Timestamp' corresponding to a capture event (Q0) - independently with global Q 
  u32 SpeedScaler; // Parameter :  Scaler converting 1/N cycles to a GLOBAL_Q speed (Q0) - independently with global Q
  u16 EventPeriod;   // Input/Variable :  Event Period (Q0) - independently with global Q
  s8  InputSelect;   // Input : Input selection between TimeStamp (InputSelect=0) and EventPeriod (InputSelect=1)
  u32 BaseRpm;       // Parameter : Scaler converting GLOBAL_Q speed to rpm (Q0) speed - independently with global Q
  s32 SpeedRpm;      // Output : speed in r.p.m. (Q0) - independently with global Q
  u32 Speed;
} SPEED_MEAS_CAP;    // Data type created


typedef struct
{
  u8  FlagPWMDuty;           //PWM更新
  u16  DutyCurrent;

  u8 FlagDelayAngleTime;     //换相角度
  u16 DelayAngleIn;
  u16 DelayAngleOut;
  u16 DelayAngleOutRef;
  
  uint8 FlagMaskAngleTime;   //屏蔽角度
  u16 MaskAngleIn;  
  u16 MaskAngleOut;
  
  uint8 FlagCalcSpeed;       //速度计算
  uint8 FlagCalcSpeedRpm;    //速度计算  

  uint8 FlagTargetSpeed;     //速度给定计算
  uint16 TargetSpeed;        //目标速度

  u16 SpeedSref;             //速度给定 曲线校准
  u16 AlineX1,AlineX2,AlineY1,AlineY2;
  u16 AlineA;
  s16 AlineB;
  u32 SpeedSrefErr;

} MDUControl_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern MDUControl_TypeDef xdata MDUControl;
/*******************************************************************************
* Function Name  : speed_prd_calc    
* Description    : 速度计算模块，根据HALL信号计算速度
* Input          : TIM1_BCCR
* Output         : 速度单位 RPM
* Return         : 无
*******************************************************************************/
extern void PDEventPeriodCalc(void); //位置反馈时间周期计算
extern void MDUInit(void);
extern void MDUControlInit(void);
extern void MDUAPP(void);
#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/