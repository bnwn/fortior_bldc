
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
#ifndef __BEEP_H_
#define __BEEP_H_


/* Exported types -------------------------------------------------------------------------------*/

typedef enum
{ 
  BeepDone         = 1,      //蜂鸣器模式1
  PWMINAline       = 2,      //蜂鸣器模式2
  PWMINReady       = 3,      //蜂鸣器模式3
  PWMINError       = 4,      //蜂鸣器模式4
  SelfInspection   = 5       //蜂鸣器模式5
}BeepMold_TypeDef;

typedef struct
{
  BeepMold_TypeDef  BeepType;
  u8  BeepRequest;

} Beep_TypeDef;

/* Exported variables ---------------------------------------------------------------------------*/
extern Beep_TypeDef xdata Beep;

/* Exported functions ---------------------------------------------------------------------------*/
extern void BeepInit(void);
extern void BeepScan(void);
extern void BeepRequestFun(u8 mold);
extern void Beepperform(void);
extern u8 BeepResponse(void);
#endif

