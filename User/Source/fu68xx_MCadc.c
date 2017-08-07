
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
#include "fu68xx_MCadc.h"
#include "fu68xx_MClpf.h"
#include "MC_MotorDriver_layer.h"    
#include "MC_MotorCotrol_layer.h"    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern u8 Delay(u16 timer);
extern u8 Delayus(u16 timer);

void ADCGetFastValue(void);
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_Config(void)
{
  /*-------------------------------------------------------------------------------------------------
  ADC��������
  1��ʹ��ADC
  4���������ݸ�ʽΪ12bit
  5����ֹADC Trigger
  -------------------------------------------------------------------------------------------------*/
  SetBit(ADC_STA, ADCEN, 1);                               // ʹ��ADC
  SetBit(ADC_STA, ADCBS, 0);                               // 12bit���ݸ�ʽ��0Ϊ12��1Ϊ10λ
  SetBit(ADC_CFG, ADTRIGEN, 1);                            // ��ֹADC Trigger
  TIM2_ADTR = 1;  /*-----------------------------------------------------------------------------------
  ADC�ο���ѹѡ��
  ADCREF = 00��ѡ��VDD5��ΪADC�ο���ѹ
  ADCREF = 01��ѡ���ⲿVREF��ΪADC�ο���ѹ
  ADCREF = 10��ѡ���ڲ�VREF��ΪADC�ο���ѹ
  ADCREF = 11��ѡ���ڲ�VREF��ΪADC�ο���ѹ��ͬʱ�ο���ѹ�����VREF�ܽ�
  -----------------------------------------------------------------------------------*/
  SetBit(ADC_CFG, ADCREF1, 1);
  SetBit(ADC_CFG, ADCREF0, 1);

  /*-----------------------------------------------------------------------------------
  ADCͨ������
  1��ʹ����ӦPinΪģ��Pin����ֹ���ֹ���
  2��ʹ��ͨ��MASK������Pin��ADCģ��
  -----------------------------------------------------------------------------------*/
  SetBit(P3_AN, P34, 1);
  SetBit(ADC_MASK, CH7EN, 1);     //Config P3.4 as ADC7

//  SetBit(P3_AN, P33, 1); 
//  SetBit(ADC_MASK, CH6EN, 1);      //Config P3.3 as ADC6

  //SetBit(P3_AN, P32, 1);
  //SetBit(ADC_MASK, CH5EN, 1);    //Config P3.2 as ADC5

  SetBit(P2_AN, P27, 1);
  SetBit(ADC_MASK, CH4EN, 1);      //Config P2.7 as ADC4

  SetBit(P2_AN, P25, 1);
  SetBit(ADC_MASK, CH3EN, 1);      //Config P2.5 as ADC3
  
  SetBit(P2_AN, P24, 1); 
  SetBit(ADC_MASK, CH2EN, 1);      //Config P2.4 as ADC2

  SetBit(P2_AN, P23, 1);
  SetBit(ADC_MASK, CH1EN, 1);      //Config P2.3 as ADC1

  SetBit(P2_AN, P20, 1);
  SetBit(ADC_MASK, CH0EN, 1);    //Config P2.0 as ADC0

  /*ADCͨ������ʱ����������*/
  ADC_SCYC1 = 0x33;                // 3��ADC Clock
  ADC_SCYC0 = 0x33;                // 3��ADC Clock

/*-------------------------------------------------------------------------------------------------
  ADC�ж�����
  1��ʹ��ADC�ж�
  2����ֹADC Trigger�ж�
  3������ADC�ж����ȼ���Ϊ0
-------------------------------------------------------------------------------------------------*/
  CLR(ADC_STA, ADCIF);
  SetBit(ADC_STA, ADCIE, 1);       // 0����ֹADC�жϣ�1��ʹ��ADC�ж�

  CLR(ADC_CFG, ADTRIGIF);
  SetBit(ADC_CFG, ADTRIGIE, 0);    // 0����ֹADC Trigger�жϣ�1��ʹ��ADC Trigger�ж�
  
}

/*******************************************************************************
* Function Name  : ADCInit
* Description    : ADC��ʼ��
* Input          : None
* Output         : None
* Return         : None      
*******************************************************************************/
void ADCInit(void)
{
  // V_bus
  //Drv.AdcMeas.VdcMeasOffset = 0;
  Drv.AdcMeas.VdcMeasGain = VDCMEASEGAIN;
  Drv.AdcMeas.VdcMeas = 0;
  Drv.AdcMeas.Vdc = 0;

  if(Drv.AdcMeas.ImeasA < 0x100)
  {
    Drv.AdcMeas.ImeasAOffset = -Drv.AdcMeas.ImeasA;
  }
  if(Drv.AdcMeas.ImeasB < 0x100)
  {
    Drv.AdcMeas.ImeasBOffset = -Drv.AdcMeas.ImeasB;
  }
  if(Drv.AdcMeas.ImeasC < 0x100)
  {
    Drv.AdcMeas.ImeasCOffset = -Drv.AdcMeas.ImeasC;
  }
  // I_bus                   
  if(Drv.AdcMeas.ImeasBus < 0x100)
  {
    Drv.AdcMeas.IBusMeasOffset = -Drv.AdcMeas.ImeasBus;
  }
  else if((Drv.AdcMeas.ImeasBus < 0x3FFF+0x500)&&(Drv.AdcMeas.ImeasBus > 0x3FFF-0x500))
  {
    Drv.AdcMeas.IBusMeasOffset = -Drv.AdcMeas.ImeasBus;
  }    
  Drv.AdcMeas.IBusMeasGain = IBUSMEASGAIN;
  Drv.AdcMeas.ImeasBus = 0;
  Drv.AdcMeas.Ibus = 0;  
  // VTH1
  Drv.AdcMeas.Vth1Meas     = 0;
  Drv.AdcMeas.Vth1         = 0;
  Drv.AdcMeas.Therm1       = 0;
  // VTH2
  Drv.AdcMeas.Vth2Meas     = 0;
  Drv.AdcMeas.Vth2         = 0;
  Drv.AdcMeas.Therm2       = 0;
  // VTH3
  Drv.AdcMeas.Vth3Meas     = 0;
  Drv.AdcMeas.Vth3         = 0;
  Drv.AdcMeas.Therm3       = 0;
  // Vref
  Drv.AdcMeas.SrefMeas     = 0;
  Drv.AdcMeas.Sref         = 0;
}


/*******************************************************************************
* Function Name  : FastADConvert    
* Description    : ADC���ټ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FastADConvert(void)
{
  u8 tempADC_MASK;
  #if(MOS_SELFINSPECTION)
  tempADC_MASK = ADC_MASK;

  ADC_MASK = 0x07;

  CLR(ADC_STA, ADCIF);
  Delay(2);
  SetBit(ADC_STA, ADCBSY, 1);         //����ADC����ת��
  while(!(GetBit(ADC_STA, ADCIF)));   //ADC��������жϷ�����
  {
    CLR(ADC_STA, ADCIF);
    ADC_MASK = tempADC_MASK;
  }
  #endif
}


void ADCGetFastValue(void)
{
  u16 DataMeasValue,tImeasBus,tVmeasA,tVmeasB,tVmeasC;              //ADC�ɼ�ֵ
  
  tVmeasA = ADC2_DR << 3; 
  tVmeasB = ADC0_DR << 3; 
  tVmeasC = ADC1_DR << 3;

  if(Ctl.State <= MOTOR_INIT) 
  {
    Drv.AdcMeas.VmeasA = tVmeasA; 
    Drv.AdcMeas.VmeasB = tVmeasB; 
    Drv.AdcMeas.VmeasC = tVmeasC; 
  }    
  else
  {
    Drv.AdcMeas.VmeasA = tVmeasA + Drv.AdcMeas.ImeasAOffset;
    Drv.AdcMeas.VmeasB = tVmeasB + Drv.AdcMeas.ImeasBOffset;
    Drv.AdcMeas.VmeasC = tVmeasC + Drv.AdcMeas.ImeasCOffset;
    if(Drv.AdcMeas.VmeasA < 0) Drv.AdcMeas.VmeasA = 0;
    if(Drv.AdcMeas.VmeasB < 0) Drv.AdcMeas.VmeasB = 0;
    if(Drv.AdcMeas.VmeasC < 0) Drv.AdcMeas.VmeasC = 0;
  }
}
/*******************************************************************************
* Function Name  : ADCGetValue
* Description    : 
* Input          : None
* Output         : None
* Return         : None      
*******************************************************************************/
void ADCGetValue(void)
{
  u16 DataMeasValue,tImeasBus;   //ADC�ɼ�ֵ
  
  DataMeasValue = ADC2_DR << 3;  // Q12-->Q15
  Drv.AdcMeas.VdcMeas  = MC_LPF(DataMeasValue,Drv.AdcMeas.VdcMeas, 10000); //����ʱ��25us

  tImeasBus = ADC4_DR << 3;      // Q12-->Q15  
  if(Ctl.State <= MOTOR_INIT) 
  {
    Drv.AdcMeas.ImeasBus = MC_LPF(tImeasBus,Drv.AdcMeas.ImeasBus, 10000); //����ʱ��25us
  }    
  else
  {
    Drv.AdcMeas.ImeasBus = tImeasBus + Drv.AdcMeas.IBusMeasOffset;
    if(Drv.AdcMeas.ImeasBus < 0)
    {
      Drv.AdcMeas.ImeasBus = 0;
    }
  }
 
  //Drv.AdcMeas.Vth1Meas = ADC1_DR << 3; // Q12-->Q15 
  Drv.AdcMeas.Vth2Meas = ADC3_DR << 3; // Q12-->Q15
  Drv.AdcMeas.Vth3Meas = ADC6_DR << 3; // Q12-->Q15
  Drv.AdcMeas.SrefMeas = ADC7_DR << 3; // Q12-->Q15
}

/*******************************************************************************
* Function Name  : ADCGetConversionValue
* Description    : 
* Input          : None
* Output         : None
* Return         : None      
*******************************************************************************/
void ADCGetConversionValue(void)
{
  u16 DataMeasValue = 0;
  float fValue = 0;
  #if(VBUS_CALC_EN)
  Drv.AdcMeas.Vdc = Drv.AdcMeas.VdcMeas*Drv.AdcMeas.VdcMeasGain;
  #endif
  #if(IBUS_CALC_EN)
  Drv.AdcMeas.Ibus = Drv.AdcMeas.ImeasBus*Drv.AdcMeas.IBusMeasGain;
  #endif
//  Drv.AdcMeas.Vth1 = Drv.AdcMeas.Vth1Meas;
//  Drv.AdcMeas.Vth2 = Drv.AdcMeas.Vth2Meas;
//  Drv.AdcMeas.Sref = Drv.AdcMeas.SrefMeas;
  #if(OH1_EN)  Drv.AdcMeas.Vth1 = MC_LPF(Drv.AdcMeas.Vth1Meas,Drv.AdcMeas.Vth1, 1000); 
  #endif
  #if(OH2_EN)
  Drv.AdcMeas.Vth2 = MC_LPF(Drv.AdcMeas.Vth2Meas,Drv.AdcMeas.Vth2, 1000);
  #endif
  #if(ADCSREF_EN)
  Drv.AdcMeas.Sref = MC_LPF(Drv.AdcMeas.SrefMeas,Drv.AdcMeas.Sref, 1000);
  #endif
}



