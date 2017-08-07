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
#include <Myproject.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//
extern u8 xdata WriteRomValue;
extern u8 xdata ReadRomValue;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : TIM1_INT    
* Description    : HALL读取，转速计算
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/


void TIM1_ISR(void) interrupt 5
{                                       
  if((GetBit(TIM1_SR,WTIF))&&(GetBit(TIM1_IER,WTIE)))    //写入中断 中断
  {  
    CLRFlag_WTIF;
  }
  if((GetBit(TIM1_SR,PDIF))&&(GetBit(TIM1_IER,PDIE)))    //位置检测 中断
  {
    Ctl.Tim.STAnms = 0;                    //检测到位置，清零

    if(Ctl.Bemf.SPItest)
    {
      MOSI_ONOFF;                          //++++测试信号 
    }
    #if (POSITION_FB_MODE == HALLSENSOR)   //HALL 位置
    {
      Drv.Hall.Status = Hall_IRQHandler(); //HALL读取   

      #if (HALLADVANCEEANGLE == 0)
      Drv_HallDriveD(Ctl.Step);            //正常换相
      #else
      Drv_HallDriveS(Ctl.Step);            //超前&滞后换相
      #endif
      Drv.speed.EventPeriod = TIM1_BCCR; 

      #if(MOTORCIRCLECALEEN)
      Ctl.spd.MechCircleNum = Drv_RotorCircleNumCalc(Ctl.Step); //运行圈数计算
      #endif   
    }
    #elif (POSITION_FB_MODE == SENSORLESS) //BEMF 检测
    Drv_BemfTim1PDapp();
    #endif
    CLRFlag_PDIF;
  }

  //if((GetBit(TIM1_SR,RUIF))&&(GetBit(TIM1_IER,RUIF)))  //下溢中断 
  if(GetBit(TIM1_SR,RUIF))                               //
  {
    #if (POSITION_FB_MODE == SENSORLESS)
    Drv_BemfTim1RUapp();
    #else
    if(Ctl.Bemf.IRQ == BEMFCOMMUTATION)      //换相中断，TIM1触发换相模式
    {
      if(Ctl.Bemf.SPItest)
      {
        MISO_ONOFF;                           //++++测试信号
      }
      SetBit(TIM1_CR3,OPS0,0);                //软件写DBR触发换相
      Drv.Hall.u8ChangePhaseFlag = 0xFF;
      Ctl.Bemf.IRQ = BEMFNONE;
      SetBit(TIM1_IER,RUIE,0);               //禁止Preload定时器下溢中断
      SetBit(TIM1_CR1, RCEN, 0);             //失能Preload定时器
    }
    #endif
    CLRFlag_RUIF;
  }
  
  if((GetBit(TIM1_SR,BOIF))&&(GetBit(TIM1_IER,BOIF)))    //上溢中断 使能
  {
    CLRFlag_BOIF;
    
    Drv.speed.InputSelect++;
    if(Drv.speed.InputSelect > 100)
    {
      Drv.speed.InputSelect = 100;
    }

    Drv.speed.EventPeriod = 32767;
    Drv.speed.Speed = 0;
    Drv.speed.SpeedRpm = 0; 
    Ctl.spd.rpm = Drv.speed.SpeedRpm;
    Ctl.spd.rpmavg = Ctl.spd.rpm;
  }
}
/*******************************************************************************
* Function Name  : TIM23_ISR
* Description    : MainISR 
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/
void TIM23_ISR(void)  interrupt 9
{
  u32 Temp32A,Temp32B;
  u16 tPWMINHigh;
  /*TIM2 Interrupt*/
  if(GetBit(TIM2_CR1, T2IR))     //比较匹配中断
  {   
    CLRFlag_T2IR;
  }
  if(GetBit(TIM2_CR1, T2IF))     //溢出中断
  {
    CLRFlag_T2IF;
//    if(GetBit(ADC_STA, ADCIF))    //ADC软件触发中断服务函数
//    {
//      //ADCGetValue();            //ADC数据读取
//      CLR(ADC_STA, ADCIF);
//    }
    SetBit(ADC_STA, ADCBSY, 1);  //启动ADC采样转换
    MDUAPP();                    //
  }
  /*TIM3 Interrupt*/
  if(GetBit(TIM3_CR1, T3IR))
  { 
    u32 Temp32A,Temp32B;

    #if(PWMINSREF_EN)
    if((TIM3_DR > TempPWMINHighMinFilt)&&(TIM3_DR < TempPWMINHighMaxFilt))
    {
      PWMINCtl.PWMINHigh = TIM3_DR;//- TempPWMINHighMinFilt;
			
			if (PWMINCtl.PWMINIdle && (PWMINCtl.PWMINHigh < (TempPWMINStartUp + TempPWMINHighMinFilt))) {
				tPWMINHigh = TempPWMINIdling - TempPWMINHighMinFilt;
			} else {
				PWMINCtl.PWMINIdle = FALSE;
				tPWMINHigh = TIM3_DR - TempPWMINHighMinFilt; 
			}
      
      //MDUControl.SpeedSref = 32767*((float)PWMINCtl.PWMINHigh/(float)PWMINCtl.PWMINHighMax);
      //速度给定标幺化_IQ(15) 0~32767
      Temp32A = (u32)tPWMINHigh<<15;
      Temp32B =  (u32)PWMINCtl.PWMINHighMax;
      MDUControl.SpeedSref = MDU_DIV_U16(&Temp32A,&Temp32B);
      MDUControl.FlagTargetSpeed = 0x7F ;              //速度给定计算请求 
      Drv.PWM.DutytargetOpen = MDUControl.TargetSpeed; //MDU计算速度给定值
    }
    #endif
    CLRFlag_T3IR;
  }
  if(GetBit(TIM3_CR1, T3IP))
  {
    CLRFlag_T3IP;
  }
  if(GetBit(TIM3_CR1, T3IF))
  {
    #if((PWMINSREF_EN)||(PWMINONOFF_EN))
    {
      PWMINCtl.PWMINHigh = 0;
      PWMINCtl.PWMStatus = PWMIN;
    }
    #endif
    CLRFlag_T3IF;
  }
}

/*******************************************************************************
* Function Name  : TIM45_ISR
* Description    : 速度环控制 优先级1,最高优先级 硬件过流
* Input          : None
* Output         : 
* Return         : None
*******************************************************************************/
/* TIM45 overflow interrupt---------------------------------------------------*/
void TIM45_ISR(void) interrupt 10
{
  /*TIM4 Interrupt*/
  if(GetBit(TIM4_CR1, T4IF))
  { 
    MainISR();
    
    Key_Filtrate();
    #if(PWMINONOFF_EN)  
    if(Ctl.State >= MOTOR_STOP)
    {
      PWMINOnOffSwitch();
    }
    #endif
    
    CLR(TIM4_CR1, T4IF);
  }
  /*TIM5 Interrupt*/
  if(GetBit(TIM5_CR1, T5IF))
  {
    CLR(TIM5_CR1, T5IF);
  }
}
/*******************************************************************************
* Function Name  : ADC_ISR
* Description    : ADCGetValue
* Input          : None
* Output         : None
* Return         : None      

*******************************************************************************/
void ADC_ISR(void) interrupt 6      
{
  if(GetBit(ADC_STA, ADCIF))    //ADC软件触发中断服务函数
  {
    ADCGetValue();              //ADC数据读取
    CLR(ADC_STA, ADCIF);
  }
  
  if(GetBit(ADC_CFG, ADTRIGIF)) //ADC触发中断服务函数
  {
    CLR(ADC_CFG, ADTRIGIF);
  }
}
/*******************************************************************************
* Function Name  : CMP_ISR
* Description    : CMP interrupt
* Input          : None
* Output         : 
* Return         : None
*******************************************************************************/
#if (EFAL == FO_CMP)
void CMP_ISR(void) interrupt 7
{
  if(GetBit(CMP_SR, CMP3INTR))
  {
    CLR(CMP_SR, CMP3INTR);
    #if(HARD_OC_EN)
    MCL_BKIN_IRQHandler();    //硬件过流
    #endif
  }
}
#endif
/*******************************************************************************
* Function Name  : INT0_ISR
* Description    : INT0 interrupt  FO中断，用于IPM硬件过流保护，中断优先级最高
* Input          : None
* Output         : 
* Return         : None
*******************************************************************************/
#if (EFAL == FO_INT)
void INT0_ISR(void) interrupt 1
{
  if(IF0)
  {
    IF0 =0;
    #if(HARD_OC_EN)
    MCL_BKIN_IRQHandler();    //硬件过流
    #endif    
  } 
}
#endif
/*******************************************************************************
* Function Name  : LVW_ISR    
* Description    : 低压中断
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/
void LVW_ISR(void) interrupt 0
 {
   CLR(LVSR, LVWIF);
   if(WriteRomValue != ReadRomValue)
   {
     //Flash_KeyWriteValue((WriteRomValue));  //档位存储
   }
 }
 
