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
* Description    : HALL��ȡ��ת�ټ���
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/


void TIM1_ISR(void) interrupt 5
{                                       
  if((GetBit(TIM1_SR,WTIF))&&(GetBit(TIM1_IER,WTIE)))    //д���ж� �ж�
  {  
    CLRFlag_WTIF;
  }
  if((GetBit(TIM1_SR,PDIF))&&(GetBit(TIM1_IER,PDIE)))    //λ�ü�� �ж�
  {
    Ctl.Tim.STAnms = 0;                    //��⵽λ�ã�����

    if(Ctl.Bemf.SPItest)
    {
      MOSI_ONOFF;                          //++++�����ź� 
    }
    #if (POSITION_FB_MODE == HALLSENSOR)   //HALL λ��
    {
      Drv.Hall.Status = Hall_IRQHandler(); //HALL��ȡ   

      #if (HALLADVANCEEANGLE == 0)
      Drv_HallDriveD(Ctl.Step);            //��������
      #else
      Drv_HallDriveS(Ctl.Step);            //��ǰ&�ͺ���
      #endif
      Drv.speed.EventPeriod = TIM1_BCCR; 

      #if(MOTORCIRCLECALEEN)
      Ctl.spd.MechCircleNum = Drv_RotorCircleNumCalc(Ctl.Step); //����Ȧ������
      #endif   
    }
    #elif (POSITION_FB_MODE == SENSORLESS) //BEMF ���
    Drv_BemfTim1PDapp();
    #endif
    CLRFlag_PDIF;
  }

  //if((GetBit(TIM1_SR,RUIF))&&(GetBit(TIM1_IER,RUIF)))  //�����ж� 
  if(GetBit(TIM1_SR,RUIF))                               //
  {
    #if (POSITION_FB_MODE == SENSORLESS)
    Drv_BemfTim1RUapp();
    #else
    if(Ctl.Bemf.IRQ == BEMFCOMMUTATION)      //�����жϣ�TIM1��������ģʽ
    {
      if(Ctl.Bemf.SPItest)
      {
        MISO_ONOFF;                           //++++�����ź�
      }
      SetBit(TIM1_CR3,OPS0,0);                //���дDBR��������
      Drv.Hall.u8ChangePhaseFlag = 0xFF;
      Ctl.Bemf.IRQ = BEMFNONE;
      SetBit(TIM1_IER,RUIE,0);               //��ֹPreload��ʱ�������ж�
      SetBit(TIM1_CR1, RCEN, 0);             //ʧ��Preload��ʱ��
    }
    #endif
    CLRFlag_RUIF;
  }
  
  if((GetBit(TIM1_SR,BOIF))&&(GetBit(TIM1_IER,BOIF)))    //�����ж� ʹ��
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
  if(GetBit(TIM2_CR1, T2IR))     //�Ƚ�ƥ���ж�
  {   
    CLRFlag_T2IR;
  }
  if(GetBit(TIM2_CR1, T2IF))     //����ж�
  {
    CLRFlag_T2IF;
//    if(GetBit(ADC_STA, ADCIF))    //ADC��������жϷ�����
//    {
//      //ADCGetValue();            //ADC���ݶ�ȡ
//      CLR(ADC_STA, ADCIF);
//    }
    SetBit(ADC_STA, ADCBSY, 1);  //����ADC����ת��
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
      //�ٶȸ������ۻ�_IQ(15) 0~32767
      Temp32A = (u32)tPWMINHigh<<15;
      Temp32B =  (u32)PWMINCtl.PWMINHighMax;
      MDUControl.SpeedSref = MDU_DIV_U16(&Temp32A,&Temp32B);
      MDUControl.FlagTargetSpeed = 0x7F ;              //�ٶȸ����������� 
      Drv.PWM.DutytargetOpen = MDUControl.TargetSpeed; //MDU�����ٶȸ���ֵ
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
* Description    : �ٶȻ����� ���ȼ�1,������ȼ� Ӳ������
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
  if(GetBit(ADC_STA, ADCIF))    //ADC��������жϷ�����
  {
    ADCGetValue();              //ADC���ݶ�ȡ
    CLR(ADC_STA, ADCIF);
  }
  
  if(GetBit(ADC_CFG, ADTRIGIF)) //ADC�����жϷ�����
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
    MCL_BKIN_IRQHandler();    //Ӳ������
    #endif
  }
}
#endif
/*******************************************************************************
* Function Name  : INT0_ISR
* Description    : INT0 interrupt  FO�жϣ�����IPMӲ�������������ж����ȼ����
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
    MCL_BKIN_IRQHandler();    //Ӳ������
    #endif    
  } 
}
#endif
/*******************************************************************************
* Function Name  : LVW_ISR    
* Description    : ��ѹ�ж�
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/
void LVW_ISR(void) interrupt 0
 {
   CLR(LVSR, LVWIF);
   if(WriteRomValue != ReadRomValue)
   {
     //Flash_KeyWriteValue((WriteRomValue));  //��λ�洢
   }
 }
 
