
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
#ifndef __BEEP_H_
#define __BEEP_H_


/* Exported types -------------------------------------------------------------------------------*/

typedef enum
{ 
  BeepDone         = 1,      //������ģʽ1
  PWMINAline       = 2,      //������ģʽ2
  PWMINReady       = 3,      //������ģʽ3
  PWMINError       = 4,      //������ģʽ4
  SelfInspection   = 5       //������ģʽ5
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

