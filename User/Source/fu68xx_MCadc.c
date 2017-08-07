
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
  ADC基本配置
  1、使能ADC
  4、设置数据格式为12bit
  5、禁止ADC Trigger
  -------------------------------------------------------------------------------------------------*/
  SetBit(ADC_STA, ADCEN, 1);                               // 使能ADC
  SetBit(ADC_STA, ADCBS, 0);                               // 12bit数据格式，0为12，1为10位
  SetBit(ADC_CFG, ADTRIGEN, 1);                            // 禁止ADC Trigger
  TIM2_ADTR = 1;  /*-----------------------------------------------------------------------------------
  ADC参考电压选择
  ADCREF = 00：选择VDD5作为ADC参考电压
  ADCREF = 01：选择外部VREF作为ADC参考电压
  ADCREF = 10：选择内部VREF作为ADC参考电压
  ADCREF = 11：选择内部VREF作为ADC参考电压，同时参考电压输出到VREF管脚
  -----------------------------------------------------------------------------------*/
  SetBit(ADC_CFG, ADCREF1, 1);
  SetBit(ADC_CFG, ADCREF0, 1);

  /*-----------------------------------------------------------------------------------
  ADC通道配置
  1、使能相应Pin为模拟Pin，禁止数字功能
  2、使能通道MASK，连接Pin到ADC模块
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

  /*ADC通道采样时钟周期设置*/
  ADC_SCYC1 = 0x33;                // 3个ADC Clock
  ADC_SCYC0 = 0x33;                // 3个ADC Clock

/*-------------------------------------------------------------------------------------------------
  ADC中断设置
  1、使能ADC中断
  2、禁止ADC Trigger中断
  3、设置ADC中断优先级别为0
-------------------------------------------------------------------------------------------------*/
  CLR(ADC_STA, ADCIF);
  SetBit(ADC_STA, ADCIE, 1);       // 0，禁止ADC中断，1，使能ADC中断

  CLR(ADC_CFG, ADTRIGIF);
  SetBit(ADC_CFG, ADTRIGIE, 0);    // 0，禁止ADC Trigger中断，1，使能ADC Trigger中断
  
}

/*******************************************************************************
* Function Name  : ADCInit
* Description    : ADC初始化
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
* Description    : ADC快速检测
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
  SetBit(ADC_STA, ADCBSY, 1);         //启动ADC采样转换
  while(!(GetBit(ADC_STA, ADCIF)));   //ADC软件触发中断服务函数
  {
    CLR(ADC_STA, ADCIF);
    ADC_MASK = tempADC_MASK;
  }
  #endif
}


void ADCGetFastValue(void)
{
  u16 DataMeasValue,tImeasBus,tVmeasA,tVmeasB,tVmeasC;              //ADC采集值
  
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
  u16 DataMeasValue,tImeasBus;   //ADC采集值
  
  DataMeasValue = ADC2_DR << 3;  // Q12-->Q15
  Drv.AdcMeas.VdcMeas  = MC_LPF(DataMeasValue,Drv.AdcMeas.VdcMeas, 10000); //运行时间25us

  tImeasBus = ADC4_DR << 3;      // Q12-->Q15  
  if(Ctl.State <= MOTOR_INIT) 
  {
    Drv.AdcMeas.ImeasBus = MC_LPF(tImeasBus,Drv.AdcMeas.ImeasBus, 10000); //运行时间25us
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



