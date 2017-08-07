
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
#ifndef __MC_PWMIN_H_
#define __MC_PWMIN_H_


/* Exported types -------------------------------------------------------------------------------*/
typedef struct
{
  uint8 FlagPWMAline;
  uint8 FlagPWMPowerUp;
  
  u8    FlagPwmIn;
  uint8 PWMStatus;
  int16 PWMINCnt;
  int16 PWMINStartCnt;
  int16 PWMINBreakCnt;
  uint16 PWMINHigh;
  uint32 PWMINPeriod;
  uint16 PWMINHighDuty;
  uint16 PWMINHighMin;
  uint16 PWMINHighMax;
  uint32 PWMINHighErr;
	bool PWMINIdle;
} PWMINCtl_TypeDef;

/* Exported variables ---------------------------------------------------------------------------*/
extern PWMINCtl_TypeDef xdata PWMINCtl;extern u8 xdata PwmInResetFlag;
/* Exported functions ---------------------------------------------------------------------------*/
extern void PWMINInit(void);
extern void PWMScan(void);
extern void PWMINOnOffSwitch(void);
#endif

