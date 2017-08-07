
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
#ifndef __MC_MOTORFUNCTION_LAYER_H
#define __MC_MOTORFUNCTION_LAYER_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
  {
    s16 ref;
    s16 fdb;
    s16 err;
  }Power_TypeDef;
extern Power_TypeDef Power;  
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern float Drv_PowerThermCalc(u16 VthMeas);     //PTC�����¶ȼ���ģ��
extern void MCL_OverLoadInit(u16 OL0A,u16 OL1A,u16 OL2A,u16 OL3A,u32 OL0ms,u32 OL1ms,u32 OL2ms,u32 OL3ms);//���س�ʼ��
extern u8  MCL_OverLoadCalc(u16 Ibus);            //���ؼ���
extern u32 Drv_RotorCircleNumCalc(u8 value);      //����Ȧ������
extern void Mcl_MotorRestart(void);
extern u8  Mcl_StallRestart(void);                //��ת����
extern void Mcl_NoloadCale(void);                 //�жϵ���Ƿ����
extern void Drv_PowerClosedCalc(void);
extern void Drv_Stb3Calc(void);
extern void Drv_BemfSetFRFun(void);               //���Ӧ�� ������з����趨

  
#endif /*  */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/