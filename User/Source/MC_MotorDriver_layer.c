
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
DRV_TypeDef xdata Drv; 
extern uc16 DRV_SECTION2OCM[8];

/* Private function prototypes -----------------------------------------------*/
u8 Drv_Commutation(u8 Step);                //����
u16 Drv_SpeedRampCale(u16 refTar);          //�ջ��Ӽ�������
u16 Drv_DutyRampCale(u16 tduty);            //�����Ӽ�������
u16 Fu68xx_PWM_Update(u16 tduty);           //PWM����
void Drv_SetStep(void);                     //
void Drv_HallDriveD(u8 Step);               //HALL�ж�ֱ�ӻ���
u8 Drv_SelfInspection(u8 Num,float Value1,float Value2);//mos�Լ�
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Drv_Commutation ����  TIM1_DBR -> TIM1_DR
* Description    : ����ģ�飬���ݵ��ת����
* Input          : ��������
* Output         : None
* Return         : 1
*******************************************************************************/
u8 Drv_Commutation(u8 Step)
{
  //�������壬��Ҫ��ʼ�� 3.3.3
  Ctl.Step = Step;
  
  if(Ctl.StepPre != Ctl.Step)
  {
    Ctl.StepPre = Ctl.Step; 
    if((Ctl.State == MOTOR_NORMAL)||(Ctl.State == MOTOR_OPENLOOP)||(Ctl.State == MOTOR_PRECHARGE))
    {
      TIM1_DBR = DRV_SECTION2OCM[Ctl.Step];
    }
  }

  return 1;
} 


/*******************************************************************************
* Function Name  : Drv_SpeedRampCale �ջ��Ӽ�������
* Description    : �ٶȱջ��Ӽ������� ������Ч
* Input          : Ŀ���ٶ� refTar _IQ15��ʽ
* Output         : �����ٶ� refCur _IQ15��ʽ
* Return         : �����ٶ� refCur _IQ15��ʽ
*******************************************************************************/
u16 Drv_SpeedRampCale(u16 refTar)
  {
    u16 refCur = 0;
      
    refCur = Ctl.spd.refCur;
      
    if(refCur < refTar)
    {
      refCur += Ctl.spd.IncValue;
    }
    else if(refCur > refTar)
    {
      refCur -= Ctl.spd.DecValue;
    }
    else
    {
      refCur = Ctl.spd.refTar;
    }
    
    return refCur;
  }

/*******************************************************************************
* Function Name  : Drv_DutyRampCale 
* Description    : ����Ƶ�ʣ�ÿ��ն������һ�� 
* Input          : Ŀ��DUTY  ��ʽ_IQ15 ��0x7FFF
* Output         : ��ǰDUTY  ��ʽ_IQ15 ��0x7FFF
* Return         : ��ǰDUTY  ��ʽ_IQ15 ��0x7FFF       
*******************************************************************************/
u16 Drv_DutyRampCale(u16 tduty)
{
  if(((s32)Drv.PWM.DutyCurrent - (s32)Drv.PWM.Dutytarget) > Drv.PWM.DutyDecValue)
  {
    Drv.PWM.DutyCurrent -= Drv.PWM.DutyDecValue;
  }
  else if(((s32)Drv.PWM.Dutytarget - (s32)Drv.PWM.DutyCurrent) > Drv.PWM.DutyIncValue) 
  {
    Drv.PWM.DutyCurrent += Drv.PWM.DutyIncValue;  
  }
  else
  {
    Drv.PWM.DutyCurrent = Drv.PWM.Dutytarget;
  }

  return Drv.PWM.DutyCurrent ;
}

/*******************************************************************************
* Function Name  : Fu68xx_PWM_Update
* Description    : PWM����ģ�飬ÿ��ն�����£�ʵʱ����
* Input          : _IQ15 ��ʽduty
* Output         : TIM2_DR
* Return         : TIM2_DR
*******************************************************************************/
u16 Fu68xx_PWM_Update(u16 tduty)
{
  u16 temp;
  #if(CURRENT_LIMIT_EN)                             //����ʹ��
  if(Drv.PWM.DutyLimitFlag == 0x7F)                 //�������
  {
    Drv.PWM.DutyMax -= Drv.PWM.DutyLimitADD;
    if(Drv.PWM.DutyMax < 3276)
    {
      Drv.PWM.DutyMax = 3276;
    }
  }
  else
  {
    if((Drv.PWM.DutyMax+Drv.PWM.DutyLimitADD) < MOTOR_VS_MAX)
    {
      Drv.PWM.DutyMax += Drv.PWM.DutyLimitADD;
    }
  }    
  #endif
  tduty +=10;
  if(tduty > Drv.PWM.DutyMax)
  {
    tduty = Drv.PWM.DutyMax;
  }
  else if(tduty < Drv.PWM.DutyMin)
  {
    tduty = Drv.PWM.DutyMin;
  }
  
  MDUControl.DutyCurrent = tduty;
  MDUControl.FlagPWMDuty = 0x7F;

  return MDUControl.DutyCurrent;
}

/*******************************************************************************
* Function Name  : Drv_SetStep    
* Description    : ��������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Drv_SetStep(void)
{
  s8 TempCCW,TempCW;
  if(POSITION_FB_MODE == SENSORLESS )  
  {
    TempCCW = CCW;
    TempCW = CW;
  }
  else
  {
    if(HALLADVANCEFIX)
    {
      TempCCW = CCW;
      TempCW = CW;
    }
    else
    {
      TempCCW = CW;
      TempCW = CCW;
    }
  }
  if (Ctl.direction == TempCW)
  {
    if(Ctl.Step < 6)
    {
      Ctl.Step ++;
    }
    else 
    {
      Ctl.Step = 1;
    }
  }
  else if (Ctl.direction == TempCCW)
  {
    if(Ctl.Step > 1)
    {
      Ctl.Step --;
    }  
    else
    {
      Ctl.Step = 6;
    }
  }
}

/*******************************************************************************
* Function Name  : Drv_HallDriveD    
* Description    : hall�ж����ˣ�ֱ�ӻ��� ����ǰ���ͺ�
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Drv_HallDriveD(u8 Step)
{
  Ctl.Step = Step;

  if(Ctl.StepPre != Ctl.Step)
  {
    Ctl.StepPre = Ctl.Step; 
    if((Ctl.State == MOTOR_NORMAL)||(Ctl.State == MOTOR_PRECHARGE))
    {
      SetBit(TIM1_CR3,OPS0,0);              //���дDBR��������
      TIM1_DBR = DRV_SECTION2OCM[Ctl.Step];
      Drv.Hall.u8ChangePhaseFlag = 0xFF;  
    }
  }   
}




/*******************************************************************************
* Function Name  : Drv_SelfInspection  self-inspection system  
* Description    : 
* Input          : None      AB  A={1,2,3,4,5,6}  B={1,2}  A=����  B =1 ��· 2��·
* Output         : None      0.6 0.1
* Return         : None     Drv_SelfInspection(1,0.6,0.1)
*******************************************************************************/
u8 Drv_SelfInspection(u8 Num,float Value1,float Value2)
{

  u16 VbusShortValue,VbusPoenValue;
  u8 tValue,i;

  tValue = 0;
  VbusShortValue = Drv.AdcMeas.VdcMeas *Value1;
  VbusPoenValue = Drv.AdcMeas.VdcMeas *Value2;

  SetBit(ADC_CFG, ADTRIGEN, 0); 
  //================================================
  //UH VH WH ��·���  
  EA = 0;
  PWMOUT_OFF;
  ADCGetFastValue();                      //ADC���ݶ�ȡ 
  if((Drv.AdcMeas.VmeasA > VbusShortValue)||(Drv.AdcMeas.VmeasB > VbusShortValue)||(Drv.AdcMeas.VmeasC > VbusShortValue))
  {
    tValue = 0XFF;              //UVW �ж�·
    goto MOSFETerror;
  }
  else
  {
    tValue = 0;
  }
  EA = 1;
 
  Delay(100); 
  //================================================
  //UH VH WH ��·��� 
  //UL VL WL ��·���
  //-----------
  //UH ��·��� UL��·��� 
  EA = 0;
  for(i=0;i < Num;i++)
  {            
    PWM_UH_ON;
    FastADConvert();                     
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC���ݶ�ȡ 
    if(Drv.AdcMeas.VmeasA < VbusPoenValue)
    {
      tValue = 0x12;         //UH ��·
      goto MOSFETerror;
    }
    else if(Drv.AdcMeas.VmeasA < VbusShortValue)
    {
      tValue = 0x21;         //UL �ж�·
      goto MOSFETerror;
    }
    else
    {
      tValue = 0;
    }    
    Delay(100);
  }
  EA = 1; 
  //-----------
  //VH ��·��� VL��·��� 
  EA = 0;
  for(i=0;i < Num;i++)
  {
    PWM_VH_ON;
    FastADConvert();
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC���ݶ�ȡ 
    
    if(Drv.AdcMeas.VmeasB < VbusPoenValue)
    {
      tValue = 0x32;         //VH ��·
      goto MOSFETerror;
    }
    else if(Drv.AdcMeas.VmeasB < VbusShortValue)
    {
      tValue = 0x41;         //VL �ж�·
      goto MOSFETerror;
    }
    else
    {
      tValue = 0;
    }   
  
    Delay(100);
  }
  EA = 1; 
  //-----------
  //WH ��·��� WL��·��� 
  EA = 0;
  for(i=0;i < Num;i++)
  {

    PWM_WH_ON;
    FastADConvert();
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC���ݶ�ȡ
    
    if(Drv.AdcMeas.VmeasC < VbusPoenValue)
    {
      tValue = 0x52;         //WH ��·
      goto MOSFETerror;
    }
    else if(Drv.AdcMeas.VmeasC < VbusShortValue)
    {
      tValue = 0x61;         //WL �ж�·
      goto MOSFETerror;
    }
    else
    {
      tValue = 0;
    }    
    Delay(100);
  }
  EA = 1; 

  //================================================
  //UL VL WL ��·��� 
  //-----------
  //UL ��·���  
  EA = 0;
  for(i=0;i < Num;i++)
  {            
    PWM_UH_ON;
    PWM_UL_ON;
    FastADConvert();                     
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC���ݶ�ȡ 
    if(Drv.AdcMeas.VmeasA > VbusShortValue>>1)
    {
      tValue = 0x22;         //UL �п�·
      goto MOSFETerror;
    }
    else
    {
      tValue = 0;
    }    
    Delay(100);
  }
  EA = 1; 
  //-----------
  //VL ��·���
  EA = 0;
  for(i=0;i < Num;i++)
  {            
    PWM_VH_ON;
    PWM_VL_ON;
    FastADConvert();                      
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC���ݶ�ȡ 
    if(Drv.AdcMeas.VmeasB > VbusShortValue>>1)
    {
      tValue = 0x42;         //VL �п�·
      goto MOSFETerror;
    }
    else
    {
      tValue = 0;
    }    
    Delay(100);
  }
  EA = 1; 
  //-----------
  //WL ��·���
  EA = 0;
  for(i=0;i < Num;i++)
  {            
    PWM_WH_ON;
    PWM_WL_ON;
    FastADConvert();                      
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC���ݶ�ȡ 
    if(Drv.AdcMeas.VmeasC > VbusShortValue>>1)
    {
      tValue = 0x62;         //WL �п�·
      goto MOSFETerror;
    }
    else
    {
      tValue = 0;
    }    
    Delay(100);
  }
  EA = 1;   
  
  MOSFETerror: 
  SetBit(ADC_CFG, ADTRIGEN, 1);   
  return tValue;
}
#endif
