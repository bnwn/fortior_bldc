
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
    __IO float Va;             //ʵ��ֵ
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
    __IO s8  BemfValue;                     //�����ֵ
    __IO u8  BemfNum; 
    __IO s16 BemfTabA,BemfTabB,RefNumZ,RefNumY,RefNumX;     //
    __IO u8  BemfFR;                        //
    __IO u8  Calcnum;                       //ת�ٸ��ټ�����
    __IO u16 Calcnms;                       //ת�ٸ��ټ��ʱ��
  } Stk_TypeDef;
  
typedef struct
  {
   __IO  u8  Status;                 //HALL״̬ 1~6
   __IO  u8  Section;                //����     1~6
   __IO  u8  u8ChangePhaseNum;       //�������         
   __IO  s16 s16AdvanceEangle;       //���೬ǰ�Ƕ�
   __IO  u8  u8ChangePhaseFlag;      //������ɱ�־  0XFF �Ѿ����� 0X7F ׼������
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

  ADC2MEAS_TypeDef        AdcMeas;           //ADC���ֵ
  HALL_TypeDef            Hall;              //hall
  SPEED_MEAS_CAP          speed;             //�ٶȼ���
  Stk_TypeDef             Stk;
}DRV_TypeDef;
  
extern DRV_TypeDef xdata Drv;              //ȫ���ⲿ��������
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/*******************************************************************************
* Function Name  : Drv_DutyRampCale 
* Description    : ����Ƶ�ʣ�ÿ��ն������һ�� 
* Input          : Ŀ��DUTY  ��ʽ_IQ15 ��0x7FFF
* Output         : ����DUTY  ��ʽ_IQ15 ��0x7FFF
* Return         : 1
*******************************************************************************/  
extern u16 Drv_DutyRampCale(u16 tduty);    //�����Ӽ���ģ��

/*******************************************************************************
* Function Name  : Drv_SpeedRampCale �ջ��Ӽ�������
* Description    : �ٶȱջ��Ӽ������� ������Ч
* Input          : Ŀ���ٶ� refTar _IQ15��ʽ
* Output         : �����ٶ� refCur _IQ15��ʽ
* Return         : �����ٶ� refCur _IQ15��ʽ
*******************************************************************************/
extern u16 Drv_SpeedRampCale(u16 refTar);  //�ջ��Ӽ���ģ��

/*******************************************************************************
* Function Name  : Drv_Commutation ����
* Description    : ����ģ�飬���ݵ��ת����ǻ����
* Input          : ��������
* Output         : None
* Return         : 1
*******************************************************************************/
extern u8 Drv_Commutation(u8 Step);        //����ģ��

/*******************************************************************************
* Function Name  : Fu68xx_PWM_Update
* Description    : PWM����ģ�飬ÿ��ն�����£�ʵʱ����
* Input          : _IQ15 ��ʽduty
* Output         : TIM2_DR
* Return         : TIM2_DR
*******************************************************************************/
extern u16 Fu68xx_PWM_Update(u16 tduty);   //PWM����ģ��

/*******************************************************************************
* Function Name  : Drv_SetStep    
* Description    : ������������
* Input          : ANGLE ����
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_SetStep(void);

/*******************************************************************************
* Function Name  : Drv_HallDriveD    
* Description    : hall�ж����ˣ�ֱ�ӻ��� ����ǰ���ͺ�
* Input          : Step
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_HallDriveD(u8 Step);

/*******************************************************************************
* Function Name  : Drv_Stb3Calc    
* Description    : ʧ�ټ��
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern void Drv_Stb3Calc(void);
                
/*******************************************************************************
* Function Name  : Drv_SelfInspection    
* Description    : mos�Լ�
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
extern u8 Drv_SelfInspection(u8 Num,float Value1,float Value2);//mos�Լ�
#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/