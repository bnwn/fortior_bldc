
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
u8 Drv_Commutation(u8 Step);                //换相
u16 Drv_SpeedRampCale(u16 refTar);          //闭环加减速曲线
u16 Drv_DutyRampCale(u16 tduty);            //开环加减速曲线
u16 Fu68xx_PWM_Update(u16 tduty);           //PWM更新
void Drv_SetStep(void);                     //
void Drv_HallDriveD(u8 Step);               //HALL中断直接换相
u8 Drv_SelfInspection(u8 Num,float Value1,float Value2);//mos自检
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Drv_Commutation 换相  TIM1_DBR -> TIM1_DR
* Description    : 换相模块，根据电机转子扇
* Input          : 换相扇区
* Output         : None
* Return         : 1
*******************************************************************************/
u8 Drv_Commutation(u8 Step)
{
  //变量定义，需要初始化 3.3.3
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
* Function Name  : Drv_SpeedRampCale 闭环加减速曲线
* Description    : 速度闭环加减速曲线 开环无效
* Input          : 目标速度 refTar _IQ15格式
* Output         : 给定速度 refCur _IQ15格式
* Return         : 给定速度 refCur _IQ15格式
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
* Description    : 计算频率，每次斩波计算一次 
* Input          : 目标DUTY  格式_IQ15 即0x7FFF
* Output         : 当前DUTY  格式_IQ15 即0x7FFF
* Return         : 当前DUTY  格式_IQ15 即0x7FFF       
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
* Description    : PWM更新模块，每次斩波更新，实时更新
* Input          : _IQ15 格式duty
* Output         : TIM2_DR
* Return         : TIM2_DR
*******************************************************************************/
u16 Fu68xx_PWM_Update(u16 tduty)
{
  u16 temp;
  #if(CURRENT_LIMIT_EN)                             //限流使能
  if(Drv.PWM.DutyLimitFlag == 0x7F)                 //输出限制
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
* Description    : 换相设置
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
* Description    : hall中断来了，直接换相 不超前不滞后
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
      SetBit(TIM1_CR3,OPS0,0);              //软件写DBR触发换相
      TIM1_DBR = DRV_SECTION2OCM[Ctl.Step];
      Drv.Hall.u8ChangePhaseFlag = 0xFF;  
    }
  }   
}




/*******************************************************************************
* Function Name  : Drv_SelfInspection  self-inspection system  
* Description    : 
* Input          : None      AB  A={1,2,3,4,5,6}  B={1,2}  A=管子  B =1 短路 2断路
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
  //UH VH WH 断路检测  
  EA = 0;
  PWMOUT_OFF;
  ADCGetFastValue();                      //ADC数据读取 
  if((Drv.AdcMeas.VmeasA > VbusShortValue)||(Drv.AdcMeas.VmeasB > VbusShortValue)||(Drv.AdcMeas.VmeasC > VbusShortValue))
  {
    tValue = 0XFF;              //UVW 有短路
    goto MOSFETerror;
  }
  else
  {
    tValue = 0;
  }
  EA = 1;
 
  Delay(100); 
  //================================================
  //UH VH WH 开路检测 
  //UL VL WL 短路检测
  //-----------
  //UH 断路检测 UL短路检测 
  EA = 0;
  for(i=0;i < Num;i++)
  {            
    PWM_UH_ON;
    FastADConvert();                     
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC数据读取 
    if(Drv.AdcMeas.VmeasA < VbusPoenValue)
    {
      tValue = 0x12;         //UH 断路
      goto MOSFETerror;
    }
    else if(Drv.AdcMeas.VmeasA < VbusShortValue)
    {
      tValue = 0x21;         //UL 有短路
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
  //VH 断路检测 VL短路检测 
  EA = 0;
  for(i=0;i < Num;i++)
  {
    PWM_VH_ON;
    FastADConvert();
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC数据读取 
    
    if(Drv.AdcMeas.VmeasB < VbusPoenValue)
    {
      tValue = 0x32;         //VH 断路
      goto MOSFETerror;
    }
    else if(Drv.AdcMeas.VmeasB < VbusShortValue)
    {
      tValue = 0x41;         //VL 有短路
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
  //WH 断路检测 WL短路检测 
  EA = 0;
  for(i=0;i < Num;i++)
  {

    PWM_WH_ON;
    FastADConvert();
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC数据读取
    
    if(Drv.AdcMeas.VmeasC < VbusPoenValue)
    {
      tValue = 0x52;         //WH 断路
      goto MOSFETerror;
    }
    else if(Drv.AdcMeas.VmeasC < VbusShortValue)
    {
      tValue = 0x61;         //WL 有短路
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
  //UL VL WL 开路检测 
  //-----------
  //UL 开路检测  
  EA = 0;
  for(i=0;i < Num;i++)
  {            
    PWM_UH_ON;
    PWM_UL_ON;
    FastADConvert();                     
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC数据读取 
    if(Drv.AdcMeas.VmeasA > VbusShortValue>>1)
    {
      tValue = 0x22;         //UL 有开路
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
  //VL 开路检测
  EA = 0;
  for(i=0;i < Num;i++)
  {            
    PWM_VH_ON;
    PWM_VL_ON;
    FastADConvert();                      
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC数据读取 
    if(Drv.AdcMeas.VmeasB > VbusShortValue>>1)
    {
      tValue = 0x42;         //VL 有开路
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
  //WL 开路检测
  EA = 0;
  for(i=0;i < Num;i++)
  {            
    PWM_WH_ON;
    PWM_WL_ON;
    FastADConvert();                      
    PWMOUT_OFF;
    ADCGetFastValue();                      //ADC数据读取 
    if(Drv.AdcMeas.VmeasC > VbusShortValue>>1)
    {
      tValue = 0x62;         //WL 有开路
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
