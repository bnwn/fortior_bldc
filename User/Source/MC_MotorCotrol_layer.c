
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

/** @addtogroup FT68xx
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
MCL_TypeDef xdata Ctl;    
/* Private function prototypes -----------------------------------------------*/
void MCL_MotorC(void);
void MCL_BKIN_IRQHandler(void);
void MainISR(void);

static u8 MCL_Init(void); 
static u8 MCL_Ready(void);
static u8 MCL_Strack(void);
static u8 MCL_Precharge(void);
static u8 MCL_Alignment(void);
static u8 MCL_OpenLoop(void);
static u8 MCL_Normal(void);
static u8 MCL_Stop(void);
static u8 MCL_Failure(void);

static void SysTick_1ms(void);
static void BLDC_BRK_IRQHandler(void); 
static void MCL_ChkPowerStage(void);
static void MCL_ChkSysStage(void);

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MCL_MotorC
* Description    : 
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
void MCL_MotorC(void)
{
  switch(Ctl.State)
  {
    case MOTOR_INIT:
      while(MCL_Init() == 0);
      break;
    case MOTOR_STOP:
      while(MCL_Stop() == 0);
      break;
    case MOTOR_READY:
      while(MCL_Ready() == 0);
      break;
    case MOTOR_STRACK:
      while(MCL_Strack() == 0);
      break;  
    case MOTOR_PRECHARGE:
      while(MCL_Precharge() == 0);
      break;
    case MOTOR_ALIGNMENGT:
     while(MCL_Alignment() ==0 );
      break;
    case MOTOR_OPENLOOP:     
      while(MCL_OpenLoop() == 0);
      break;
    case MOTOR_NORMAL:
      while(MCL_Normal() == 0);
      break;
    case MOTOR_FAILURE:
      while(MCL_Failure() == 0);
      break;
    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : MCL_Init
* Description    : 
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
u8 MCL_Init(void)
{ 
  u8 tValue;

  MCL_ModuleInit();
  PWMOUT_OFF;
  #if(MOS_SELFINSPECTION)
  //tValue = Drv_SelfInspection(1,0.4,0.1);
  //while(tValue);  //自检
  #endif
  BeepRequestFun(SelfInspection);
  #if(DriverFD6536_EN) 
  FD6536_EN;
  #endif

  #if (EFAL == FO_CMP)
  SetBit(CMP_CR2, CMP3EN, 1);  //下桥打开，自举电容充电导致硬件过流
  #elif (EFAL == FO_INT)
  EX0 = 1;
  #endif

  Ctl.State = MOTOR_STOP;
	PWMINCtl.PWMINIdle = TRUE;
  return 1;
}

/*******************************************************************************
* Function Name  : MCL_Stop
* Description    : 
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
u8 MCL_Stop(void)
{
  if(Beep.BeepRequest == 0x7F)
  {
    ;
  }
  else
  {
    Drv.PWM.Dutytarget = BREAK_VALUE;                 //充电占空比
    Drv.PWM.DutyCurrent = Drv.PWM.Dutytarget;
    Drv.PWM.u16cycle = Fu68xx_PWM_Update(Drv.PWM.DutyCurrent);  //占空比给定
    
    #if (POSITION_FB_MODE == SENSORLESS)
    Drv_BemfPhaseChoice(7);
    #endif

    if((Ctl.FnStopmodeC == FREE_DOWN)||(Ctl.FnStopmodeC == SLOWING_DOWN))
    {
      PWMOUT_OFF;
      if(Ctl.Start == FALSE) 
      {
        Ctl.State = MOTOR_STOP;
				PWMINCtl.PWMINIdle = TRUE;
      }
      else
      {
        Ctl.State =  MOTOR_READY;
        DRV_OE_ON;
      }
    }
    else if(Ctl.FnStopmodeC == BREAK_DOWN) 
    {
      if(Ctl.Tim.u16BrankwaitNms < BREAK_DOWNWALTNMS)
      {
        if(BREAK_VALUE == 32767)
        {
          PWM_BREAK;
        }
        else
        {
          PWM_ULVLWL_PWM;
        }
      }
      else
      {
        Ctl.Tim.u16BrankwaitNms = BREAK_DOWNWALTNMS;

        if(BREAK_VALUE == 32767)
        {
          PWM_BREAK;
        }
        else
        {
          PWM_ULVLWL_PWM;
        }

        if(Ctl.Start == FALSE) 
        {
          Ctl.State = MOTOR_STOP;
					PWMINCtl.PWMINIdle = TRUE;
        }
        else
        {
          PWMOUT_OFF;
          
          Ctl.State =  MOTOR_READY;
          DRV_OE_ON;
        }
      }      
    }
  }
  
  return 1;
}

/*******************************************************************************
* Function Name  : MCL_Ready
* Description    : 
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
u8 MCL_Ready(void)
{  
  MCL_ModuleDefault();
  Ctl.Tim.u16chargeNms = 0;
  
  #if (POSITION_FB_MODE == HALLSENSOR)         
  Ctl.State =  MOTOR_PRECHARGE ;
  #elif (POSITION_FB_MODE == SENSORLESS)
  Drv.Stk.Calcnms = 0;
  Ctl.State =  MOTOR_STRACK ;
  #endif
  if(Ctl.Start == FALSE)   {
    Ctl.State = MOTOR_STOP;
		PWMINCtl.PWMINIdle = TRUE;
  }
     
  return 1;
}

/*******************************************************************************
* Function Name  : MCL_Strack
* Description    : 
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
u8 MCL_Strack(void)
{
  PWMOUT_OFF; 
  Drv.PWM.Dutytarget = 1;                 //充电占空比
  Drv.PWM.DutyCurrent = Drv.PWM.Dutytarget;
  
  Drv_BemfPhaseChoice(7);                 //检测UVW反电势

  #if (WAIT_STEP == WAIT_STRACK)          //调试模式
  Drv.Stk.Calcnms = 0;
  #endif

  #if(BEMFSETFR)                          //方向设定
  Drv_BemfSetFRFun();
  #endif

  if(Drv.Stk.Calcnms < STKNMS)
  { 
    if(Drv.Stk.BemfFR!=0xFF)
    {
      if(Ctl.direction == Drv.Stk.BemfFR)
      {
        Drv_BemfPhaseChoice(0);

        if(Ctl.direction == CW)
        {
          if(Drv.Stk.BemfTabB<6)
          {
            Drv.Stk.BemfTabB +=1;
          }
          else 
          {
            Drv.Stk.BemfTabB = 1;
          }
        }
        Ctl.Step = Drv.Stk.BemfTabB;
        
        Drv_BemfPhaseChoice(Ctl.Step);//7  
        Drv.PWM.Dutytarget = Ctl.Ramp.cpDutyEnd ;                 //充电占空比
        Drv.PWM.DutyCurrent = Drv.PWM.Dutytarget;
        pid_spd.Out = Ctl.Ramp.cpDutyEnd;
        
        Ctl.State = MOTOR_NORMAL;
      }
      else if(Drv.Stk.BemfFR == 0x7F) 
      {
        #if (STRACK_EN == 2)
        Ctl.FnStopmodeC = FREE_DOWN;
        #endif
        Ctl.State = MOTOR_PRECHARGE;
      }  
      else
      {     
        #if (STRACK_EN == 2)
        Ctl.State = MOTOR_STOP;
				PWMINCtl.PWMINIdle = TRUE;
        Ctl.FnStopmodeC = BREAK_DOWN;
        #endif
      }
    } 
  }
  else
  {
    #if (STRACK_EN == 2)
    Ctl.FnStopmodeC = FREE_DOWN;
    #endif
    Ctl.State = MOTOR_PRECHARGE;
  }

  if(Ctl.Start == FALSE) 
  {
    Ctl.State = MOTOR_STOP;
		PWMINCtl.PWMINIdle = TRUE;
  }

  return 1;
}

/*******************************************************************************
* Function Name  : MCL_Precharge
* Description    : 
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
u8 MCL_Precharge(void)
{
  if(Ctl.Tim.u16chargeNms < CHARGENMS)            // 100ms 测试101ms
  {
    Drv.PWM.Dutytarget = CHARGEDUTY;                 //充电占空比
    Drv.PWM.DutyCurrent = Drv.PWM.Dutytarget;
    Drv.PWM.u16cycle = Fu68xx_PWM_Update(Drv.PWM.DutyCurrent);  //占空比给定
    PWM_UL_ON;
  }
  else if(Ctl.Tim.u16chargeNms < CHARGENMS*2)     // 100ms 测试101ms
  {
    PWM_VL_ON;  //PWM_ULVL_ON
  }
  else if(Ctl.Tim.u16chargeNms < CHARGENMS*3)     // 100ms 测试101ms
  {
    PWM_WL_ON; //PWM_ULVLWL_ON
  }
  else
  {
    PWMOUT_OFF;                                    //
    #if (POSITION_FB_MODE == HALLSENSOR )         //HALLSENSOR
    Drv.Hall.Status = Hall_IRQHandler();           //hall读取

    Drv.PWM.Dutytarget = MOTOR_INIT_DUTY;                 //充电占空比    //初始占空比
    Drv.PWM.DutyCurrent = Drv.PWM.Dutytarget;
    Drv.PWM.u16cycle = Fu68xx_PWM_Update(Drv.PWM.DutyCurrent);  //占空比给定
    TIM2_DR = 0;
    Ctl.Tim.STAnms = 0;
    Ctl.spd.refTar = SPEED_REF_TAR;
    Ctl.spd.refCur = SPEED_REF_INIT; 
    pid_spd.Out = 0;

    #if (HALLADVANCEEANGLE == 0)
    Drv_HallDriveD(Ctl.Step);
    #else
    Drv_HallDriveS(Ctl.Step);    
    #endif
    Ctl.State = MOTOR_NORMAL;                          

    #elif (POSITION_FB_MODE == SENSORLESS)
    
    Drv.PWM.Dutytarget = RAMP_DUTY_END;                 //充电占空比    //初始占空比
    Drv.PWM.DutyCurrent = Drv.PWM.Dutytarget;

    Ctl.Alig.NmsCount = 0;
    Ctl.State = MOTOR_ALIGNMENGT; 

    Drv.PWM.Dutytarget = Ctl.Alig.duty;
    Drv.PWM.DutyCurrent = Drv.PWM.Dutytarget; 
    Drv.PWM.u16cycle = Fu68xx_PWM_Update(Drv.PWM.DutyCurrent);  //占空比给定
  
    #endif
  }

  if(Ctl.Start == FALSE)
  {
    Ctl.State = MOTOR_STOP;
		PWMINCtl.PWMINIdle = TRUE;
  }    
  
  return 1;
}

/*******************************************************************************
* Function Name  : MCL_Alignment
* Description    : 
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
u8 MCL_Alignment(void)
{
  if(Ctl.Alig.NmsCount < Ctl.Alig.timNms)     // 1000ms 
  {
    //AH->BL,CL    U->V/W
    PWM_UHVLWL_PWM;
    Drv.PWM.Dutytarget = Ctl.Alig.duty;
    Drv.PWM.DutyCurrent = Drv.PWM.Dutytarget; 
    Drv.PWM.u16cycle = Fu68xx_PWM_Update(Drv.PWM.DutyCurrent);  //占空比给定
  }
  else
  {
    PWMOUT_OFF;
    Drv_BemfPhaseChoice(0);
    
    Drv.PWM.Dutytarget = Ctl.Ramp.cpDutySta;
    Drv.PWM.DutyCurrent = Ctl.Ramp.cpDutySta; 
    
    if (Ctl.direction == CW)   //U->V
    {
      Ctl.StepPre = 0;
      Ctl.Step = 1;          //1
    }
    else if (Ctl.direction == CCW)
    {                        //U->W
      Ctl.StepPre = 0;
      Ctl.Step = 2;          //2
    }
    Ctl.Ramp.cpOver = 0xFF;
    TIM2_ARR = RAMP_PWMARR;
    Ctl.State = MOTOR_OPENLOOP;
  }
  if(Ctl.Start == FALSE)
  {
    Ctl.State = MOTOR_STOP;
		PWMINCtl.PWMINIdle = TRUE;
  }    
  
  return 1;
}

/*******************************************************************************
* Function Name  : MCL_OpenLoop  RampUp
* Description    : 
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
u8 MCL_OpenLoop(void)
{  
  #if (WAIT_STEP == WAIT_RAMPUP)
  Ctl.Ramp.cpNumB = 0;
  #endif
  if(Ctl.Ramp.cpOver != 0x7F)
  {
    if(Ctl.Ramp.cpNmsCount >= Ctl.Ramp.cpNms) 
      { 
        Drv_BemfPhaseChoice(0); 
        
        Ctl.Ramp.cpNmsCount = 0;
        
        if((Ctl.Ramp.cpNms - Ctl.Ramp.cptimEnd) > Ctl.Ramp.cptimstep)
        {
          Ctl.Ramp.cpNms = Ctl.Ramp.cpNms - Ctl.Ramp.cptimstep;
        }
        else if((Ctl.Ramp.cptimEnd - Ctl.Ramp.cpNms) > Ctl.Ramp.cptimstep)
        {
          Ctl.Ramp.cpNms = Ctl.Ramp.cpNms + Ctl.Ramp.cptimstep;
        }
        #if (RAMP_MODE != 3)
        else if(Ctl.Ramp.cpNms == Ctl.Ramp.cptimEnd)
        {
          Ctl.Ramp.cpNms = Ctl.Ramp.cptimSta;
        }
        #endif
        else 
        {
          Ctl.Ramp.cpNms = Ctl.Ramp.cptimEnd;
        }

        if((Drv.PWM.Dutytarget - Ctl.Ramp.cpDutyEnd) > Ctl.Ramp.cpDutystep)
        {
          Drv.PWM.Dutytarget = Drv.PWM.Dutytarget - Ctl.Ramp.cpDutystep;
        }      
        else if((Ctl.Ramp.cpDutyEnd - Drv.PWM.Dutytarget)> Ctl.Ramp.cpDutystep)
        {
          Drv.PWM.Dutytarget = Drv.PWM.Dutytarget + Ctl.Ramp.cpDutystep;
        }        
        else
        {
          Drv.PWM.Dutytarget = Ctl.Ramp.cpDutyEnd;
        }

        SetBit(TIM1_CR3,OPS0,0);               //软件写DBR触发换相
        
        Drv_SetStep(); 
        Drv_Commutation(Ctl.Step);
        
        #if ((RAMP_MODE == 1)||(RAMP_MODE == 2))

        TIM1_BCNTR = 0;
        SetBit(TIM1_CR1,RCEN,0);               //失能Preload定时器 
        TIM1_RARR = TempRampMaskTime;
        TIM1_RCNTR = TIM1_RARR;
        CLRFlag_RUIF;
        Ctl.Bemf.IRQ = BEMFCMASK;              
        SetBit(TIM1_IER,RUIE,1);               //使能Preload定时器下溢中断
        SetBit(TIM1_CR1,RCEN,1);               //启动Preload定时器  

        #elif (RAMP_MODE == 3)
        Drv.speed.EventPeriod = TIM1_BCCR;
        TIM1_BCNTR = 0;
        #endif
        
        Drv_BemfPhaseChoice(0); 
        Ctl.Ramp.cpNumA++;                     //换相次数
        
        if(( Ctl.Ramp.cpNms == Ctl.Ramp.cptimEnd)&&(Drv.PWM.Dutytarget ==Ctl.Ramp.cpDutyEnd))
        {
          Ctl.Ramp.cpNumB ++;                 //换相次数
        }
      }
  }

  #if (RAMP_MODE == 3)
  if(((Ctl.Ramp.cpNumB >= Ctl.Ramp.cpFinalNumB)&&(Ctl.Step==1)))  
  { 
    PWMOUT_OFF;
    Ctl.State = MOTOR_READY; 
    TIM2_ARR = Drv.PWM.PwmArr;                //载波频率 = 24M/1500 =16K    
  }
  #endif
          
  if(Ctl.Start == FALSE)
  {
    Ctl.State = MOTOR_STOP;
		PWMINCtl.PWMINIdle = TRUE;
  }  
  
  return 1;
}

/*******************************************************************************
* Function Name  : MCL_Normal
* Description    :
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
u8 MCL_Normal(void)
{ 
  if(Ctl.Start == FALSE)
  {
    PWMOUT_OFF;
    Ctl.State = MOTOR_STOP;
		PWMINCtl.PWMINIdle = TRUE;
  }  
  #if(OCRESTART_EN) 
  if(Ctl.OC.u16Runms >= 5000)      //运行5s
  {
    Ctl.OC.u16Runms = 5000;
    //Ctl.OC.u8ReNum = OCRESTARTNUM;  //启动完成后，过流不再重启 20150827
    Ctl.OC.u8ReNum = 0;              //
    Ctl.OC.u16nmsCount =0;
  }
  #endif  
  if(Ctl.Cbcc.ReCounter >= 10000)       //1S后清除GO故障
  {    Ctl.Cbcc.FoCounter = 0;            //清FO故障计数器
    Ctl.Cbcc.ReCounter = 1000;
  }
  #if(STALLRESTART_EN) 
  if((Ctl.Stall.u16NormalRunms >= STANMS+500)) //运行5s         
    {
      Ctl.Stall.WaitReatartNms = 0;              //堵转重启等待时间
      Ctl.Stall.u16NormalRunms = STANMS+500;   //
      Ctl.Stall.u8Num = 0;              //清楚堵转故障 次数标记     
    }
  #endif
  return 1;
}

/*******************************************************************************
* Function Name  : MCL_Failure
* Description    : 
* Input          : None
* Output         : None
* Return         : 1
*******************************************************************************/
u8 MCL_Failure(void)
{
  PWMOUT_OFF;
  DRV_OE_OFF;             //
  Ctl.Start = FALSE;
	PWMINCtl.PWMINIdle = TRUE;
  
//-------------------------------------------------------  
//故障记录    
  #if(FAILLOGEN)
  if(Ctl.E_message.ErrorF==0)
  {
    //故障信息记录
    Ctl.E_message.ErrorF   = 1 ;
    Ctl.E_message.SysError = Ctl.SysError;
    //Ctl.E_message.State  = Ctl.State ;
    Ctl.E_message.FR       = Uc.flg.FR;
    //Ctl.E_message.SpeedRef = pid_spd.Ref;
    Ctl.E_message.SpeedFdb = Drv.speed.SpeedRpm;
    Ctl.E_message.Duty     = Drv.PWM.DutyCurrent;
    Ctl.E_message.ImeasBus = Drv.AdcMeas.ImeasBus;
    Ctl.E_message.VdcMeas = Drv.AdcMeas.VdcMeas;
    Ctl.E_message.Ibus     = Drv.AdcMeas.Ibus;
    Ctl.E_message.Vdc      = Drv.AdcMeas.Vdc;
//-------------------------------------------------------  
//故障信息flash 存储。
    #if(FAILSTOREEN)
    if((Ctl.SysError != E_OV)&&(Ctl.SysError != E_UV))       
        ;//Flash_Save_Data();
    #endif
//------------------------------------------------------- 
//故障上报        
  }
  #endif
//-------------------------------------------------------
//故障重启
  #if(VBUSRECOVER_EN)
  if((Ctl.SysError == E_OV)||(Ctl.SysError == E_UV))
  {
    if(Ctl.Tim.Nonms>=NONMS)
    {
      Mcl_MotorRestart();
    }
  }
  #endif
//-------------------------------------------------------
  #if(OCRESTART_EN)  
  if((Ctl.SysError == E_OC)||(Ctl.SysError == E_FAIL))
  //if(Ctl.SysError == E_OC)
  {
    if(Ctl.OC.ReFlag == 0)
    {
      if(Ctl.OC.u8ReNum < OCRESTARTNUM)
      {
        Ctl.OC.u8ReNum ++;
        Ctl.OC.u16nmsCount = 0;  
        Ctl.OC.ReFlag = 1;
      }
    }
    if(Ctl.OC.ReFlag == 1)
    {
      if(Ctl.OC.u16nmsCount >= OCRESTARTTIM)
      {
        Ctl.OC.ReFlag = 0;
        Mcl_MotorRestart();
      }
    }
  }
  #endif
    
//-------------------------------------------------------
  #if(STALLRESTART_EN)
  if((Ctl.SysError == E_STA)||(Ctl.SysError == E_STB3)||(Ctl.SysError == E_STB2)||((Ctl.SysError == E_STB1)))
    {
      if(Ctl.Stall.u8FL == 0)
        {
          if(Ctl.Stall.WaitReatartNms >= STALLRESTARTTIM)
            {
              Ctl.Stall.WaitReatartNms = 0;
              Mcl_StallRestart(); 
            }
        }
    }
  #endif
    
//-------------------------------------------------------
  #if(OHRE_EN)
  if((Ctl.SysError == E_OH1)||(Ctl.SysError == E_OH2)||(Ctl.SysError == E_OH3))
  {
    if((Ctl.Tim.OH1REnms>=OH1NMS)&&((Ctl.Tim.OH2REnms>=OH2NMS)))
    {
      Mcl_MotorRestart();
    }
  }
  #endif
  return 1;
}

/*******************************************************************************
* Function Name  : MCL_BKIN_IRQHandler
* Description    : 
* Input          : break input
* Output         : None
* Return         : 
*******************************************************************************/
void MCL_BKIN_IRQHandler(void)
{
  #if (CBCCP_EN == 0)
    DRV_OE_OFF;
    Ctl.SysError = E_FAIL;
    Ctl.State = MOTOR_FAILURE;    
  #elif (CBCCP_EN == 1)
    Ctl.Cbcc.FoCounter++;
    Ctl.Cbcc.ReCounter = 0;  //FO信号后重新计数
    if(Ctl.Cbcc.FoCounter >= CBCCP_NUM)
    {
      DRV_OE_OFF;
      Ctl.SysError = E_FAIL;
      Ctl.State = MOTOR_FAILURE;  
    }
  #elif (CBCCP_EN == 2)
    ;
  #else
    DRV_OE_OFF;
    Ctl.SysError = E_FAIL;
    Ctl.State = MOTOR_FAILURE;   
  #endif
      
  #if(FAILLOGEN)
  if(Ctl.E_message.State == 0)
  {
    Ctl.E_message.State = Ctl.State; 
  }
  #endif  
}
/*******************************************************************************
* Function Name  : MainISR
* Description    : 斩波中断执行，用于同步PWM计算 速度闭环，电流闭环
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/
void MainISR(void)
{
  Ctl.gIsrTicker++;
  Ctl.counterCtrl++;
  Ctl.counterSpeed++;
  Ctl.counterCurrent++;

  #if(CBCCP_EN)
    #if (EFAL == FO_CMP)
    DRV_OE_ON ; 
    #else
    if(FO == 1)
    {
      DRV_OE_ON ; 
    }
    #endif
  #endif

  if(Ctl.gIsrTicker >= 10)
  {
    Ctl.gIsrTicker = 0;
    SysTick_1ms();
  }
  else if(Ctl.gIsrTicker == 1)
  {
    if(Ctl.PowerOn == 0X7f)
    {
      MCL_ChkSysStage();          //故障报警
    }
  }
  else if(Ctl.gIsrTicker == 2) 
  {
    if(Ctl.PowerOn == 0X7f)
    {
      MCL_ChkPowerStage();       //故障检测
    }
  }
  else if(Ctl.gIsrTicker == 3)
  {
    #if (SPEED_CALC_EN >= 1) 
    MDUControl.FlagCalcSpeed = 0x7F;                            //转速计算请求
    #endif
  }

  #if(SPEED_CLOSE_EN)
  Ctl.spd.refCur = Drv_SpeedRampCale(Ctl.spd.refTar);         //速度闭环加减速曲线  
  #elif(CURRENT_CLOSE_EN)
  ;//                                                         //电流给定
  #else
  Drv.PWM.DutyCurrent = Drv_DutyRampCale(Drv.PWM.Dutytarget); //速度开环加减速曲线
  #endif
  
  #if(SPEED_CLOSE_EN)                       //速度环
  if(Ctl.counterSpeed > Ctl.numTicksPerSpeed)
  {
    Ctl.counterSpeed = 0;
    if(Ctl.State == MOTOR_NORMAL)
    {
      pid_spd.Ref = Ctl.spd.refCur;          //REF
      pid_spd.Fdb = Drv.speed.Speed;         //FDB
      #if(CURRENT_CLOSE_EN)
      Ctl.Is.refTar = Pid_calc(&pid_spd);    //速度环输出
      pid_is.Ref = Ctl.Is.refTar;            //电流环输入
      #else
      Drv.PWM.DutyCurrent = Pid_calc(&pid_spd);
      #endif
    }
  }
  #elif(CURRENT_CLOSE_EN)                    //电流环
  pid_is.Ref = Ctl.Is.refTar;                //电流环输入
  #endif

  #if(CURRENT_CLOSE_EN)
  if(Ctl.counterCurrent > Ctl.numTicksPerCurrent)
  {
    Ctl.counterCurrent = 0;
    if(Ctl.State == MOTOR_NORMAL)
    {
      if(pid_is.Ref > CURRENT_INMAX)
      {
        pid_is.Ref = CURRENT_INMAX;
      }
      pid_is.Fdb = Drv.AdcMeas.ImeasBus;
      Drv.PWM.DutyCurrent = Pid_calc(&pid_is); //电流环输出
    }
  }
  #endif

  #if(CURRENT_LIMIT_EN)
  {
    if(Drv.AdcMeas.ImeasBus >  Drv.PWM.DutyLimitMaxRef)
    {
      Drv.PWM.DutyLimitFlag = 0x7F;
    }
    else
    {
      Drv.PWM.DutyLimitFlag = 0xFF;
    }
  }
  #endif

  Drv.PWM.u16cycle = Fu68xx_PWM_Update(Drv.PWM.DutyCurrent);  //占空比给定
  
}

/*******************************************************************************
* Function Name  : MCL_ChkSysStage
* Description    : 1ms时钟 计时器
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/
void MCL_ChkSysStage(void)  
{

  if(Ctl.State == MOTOR_NORMAL)
  {
    #if(OVERLOAD_EN)
    if(Ctl.OL.Value != 0x7F)        //过载
    {
      Ctl.SysError = E_OL;
    }
    #endif 
  }
  #if(OVERCURRENT_EN)
  if(Ctl.Tim.OCnms >= OCNMS)      //过流
  {
    Ctl.SysError = E_OC;
  }
  #endif
  #if(OVERVOLTAGE_EN)           
  if(Ctl.Tim.OVnms >= OVNMS)      //过压
  {
    Ctl.SysError = E_OV;
  }
  #endif

  #if(UNDERVOLTAGE_EN)            //欠压
  if(Ctl.Tim.UVnms >= UVNMS)
  {
    Ctl.SysError = E_UV;
  }  
  #endif  
  
  #if(STA_EN)                     //堵转
  if(Ctl.Tim.STAnms >= STANMS)
  {
    Ctl.SysError = E_STA; 
  }
  #endif
  #if(STB1_EN)                    //失速1
  if(Ctl.Tim.STB1nms >= STB1NMS)
  {
    Ctl.SysError = E_STB1;
  }
  #endif
  #if(STB2_EN)                    //失速2
  if(Ctl.Tim.STB2nms >= STB2NMS)
  {
    Ctl.SysError = E_STB2;
  }
  #endif
  #if(OH1_EN)                     //过热
  if(Ctl.Tim.OH1nms >= OH1NMS)
  {
    Ctl.SysError = E_OH1;
    Ctl.Tim.OH1nms = OH1NMS;
  }
  #endif
  #if(OH2_EN)                     //过热
  if(Ctl.Tim.OH2nms >= OH2NMS)
  {
    Ctl.SysError = E_OH2;
    Ctl.Tim.OH2nms = OH2NMS;
  }
  #endif

  #if (POSITION_FB_MODE == HALLSENSOR)
  if((Drv.Hall.Section == 0x7F)||(Drv.Hall.Section == 0xFF))
  {
    Ctl.SysError = E_HALL;
  }
  #endif

  if (Ctl.SysError!=NONE)
  {
    PWMOUT_OFF;
    DRV_OE_OFF;

    #if(FAILSTOREEN)
    if(Ctl.E_message.State == 0)
    {
     Ctl.E_message.State = Ctl.State;
    }
    #endif
    Ctl.State = MOTOR_FAILURE;
  }
}

/*******************************************************************************
* Function Name  : MCL_ChkPowerStage
* Description    : 1ms时钟 计时器
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/
void MCL_ChkPowerStage(void)  
{
  //_nop_();
  if(Ctl.State == MOTOR_NORMAL)
  {
    #if(OCRESTART_EN)
    Ctl.OC.u16Runms++;
    #endif
    Ctl.Tim.STAnms++;                   //堵转计时器
    Ctl.Stall.u16NormalRunms++;

    //堵转检测
    #if(STB1_EN) 
    if(Drv.speed.EventPeriod < STB1SPEEDVALUE)
    {
      Ctl.Tim.STB1nms++;
    }
    else
    {
      Ctl.Tim.STB1nms= 0;
    }
    #endif

    #if(STB2_EN) 
    if(Drv.speed.EventPeriod > STB2SPEEDVALUE)
    {
      Ctl.Tim.STB2nms++;
    }
    else
    {
      Ctl.Tim.STB2nms = 0;
    }
    #endif
  }
  else
  {
   Ctl.Section.Counter = 0;
   Ctl.Stall.u16NormalRunms = 0;
 }
//------------------------------------------
//过温检测
  #if(OH1_EN)
  if(Drv.AdcMeas.Therm1 >= 100.0)       // (~120)
  {
    Ctl.Tim.OH1nms++;  //
    Ctl.Tim.OH1REnms = 0;
  }
  else if(Drv.AdcMeas.Therm1 <= 90.0)   //  (80~120)
  {
    Ctl.Tim.OH1REnms++;
    
    Ctl.Tim.OH1nms--;
    if(Ctl.Tim.OH1nms < 0)
    {
      Ctl.Tim.OH1nms = 0;
    }
  } 
  else                                  //  (~80)
  {
    Ctl.Tim.OH1REnms++;
   
    Ctl.Tim.OH1nms--;
    if(Ctl.Tim.OH1nms<0)
    {
      Ctl.Tim.OH1nms = 0;
    }
  }     
  #endif
  
  #if(OH2_EN)
  if(Drv.AdcMeas.Therm2 >= 100.0)       // (~120)
    {
      Ctl.Tim.OH2nms++;  //
      Ctl.Tim.OH2REnms = 0;
    }
  else if(Drv.AdcMeas.Therm2 <= 80.0)   //  (80~120)
    {
      Ctl.Tim.OH2REnms++;
      
      Ctl.Tim.OH2nms--;
      if(Ctl.Tim.OH2nms < 0)
      {
        Ctl.Tim.OH2nms = 0;
      }
    } 
  else                                  //  (~80)
  {
      Ctl.Tim.OH2REnms++;
     
      Ctl.Tim.OH2nms--;
      if(Ctl.Tim.OH2nms<0)
      {
        Ctl.Tim.OH2nms = 0;
      }
  }     
  #endif        
//------------------------------------------
//过流检测
  #if (CBCCP_EN != 0)
  Ctl.Cbcc.ReCounter++; 
  #endif   
  #if(OVERCURRENT_EN)
  if(Drv.AdcMeas.ImeasBus > MECASEOVERCURRENT)
    {
      Ctl.Tim.OCnms++;
    }
  else
    {
      Ctl.Tim.OCnms--;
      if(Ctl.Tim.OCnms<0)
      {
        Ctl.Tim.OCnms = 0; 
      }
    }    
  #endif  
  #if(NOLOAD_EN)  
  if(Drv.AdcMeas.ImeasBus < MECASENOLOADCURRENT)        //
    {
      Ctl.Noload.Counter++;
    }
  else
    {
      Ctl.Noload.Counter--;
      if(Ctl.Noload.Counter<0)
      {
        Ctl.Noload.Counter = 0; 
      }
    }
 #endif      
//------------------------------------------
//过压欠压检测
  #if((OVERVOLTAGE_EN)||(UNDERVOLTAGE_EN)||(VBUSRECOVER_EN))
  if(Drv.AdcMeas.VdcMeas != 0)             
  {
    if(Drv.AdcMeas.VdcMeas > MECASEOVERVOLTAGE)
    {
      Ctl.Tim.OVnms++;
      Ctl.Tim.UVnms = 0;
      Ctl.Tim.Nonms = 0;
    }
    else if (Drv.AdcMeas.VdcMeas < MECASEUNDERVOLTAGE)
    {
      Ctl.Tim.OVnms = 0;
      Ctl.Tim.UVnms++;
      Ctl.Tim.Nonms = 0;
    }
    else if ((Drv.AdcMeas.VdcMeas < MECASEOVREERVOLTAGE)&&(Drv.AdcMeas.VdcMeas > MECASEUNREDERVOLTAGE))
    {
      Ctl.Tim.OVnms = 0;
      Ctl.Tim.UVnms = 0;
      Ctl.Tim.Nonms++;
    }      
  }
  #endif
}
/*******************************************************************************
* Function Name  : SysTick_1ms
* Description    : 1ms时钟 计时器
* Input          : 
* Output         : 
* Return         : 1
*******************************************************************************/
void SysTick_1ms(void)
{  
  #if(FAILLAMPEN)
  Ctl.Tim.LED_msCunter++;
  Ctl.Tim.LED_OnOffms++;              //故障指示led闪烁
  #endif
  
  if(Ctl.FnStopmodeC == BREAK_DOWN)
  {
    if(Ctl.State == MOTOR_STOP)
    {
      Ctl.Tim.u16BrankwaitNms++;        //刹车等待定时器
    }
    else
    {
      Ctl.Tim.u16BrankwaitNms = 0;      //刹车等待定时器
    }    
  }

  if(Ctl.PowerOn == 0X7f)
  {
    Ctl.Tim.u16chargeNms++;             //充电定时器 
    Ctl.Tim.OnOffnms++;                 //ONOFF定时器

    #if (POSITION_FB_MODE == SENSORLESS)
    Ctl.Alig.NmsCount++;                //定位定时器
    Ctl.Ramp.cpNmsCount++;              //换相定时器
    Drv.Stk.Calcnms++;
    #endif
    
    #if(LAMP_EN)
    Ctl.Tim.NoOperationDelaynms++;      //无操作延时定时器
    #endif
    Ctl.Stall.WaitReatartNms++;
    #if(OVERLOAD_EN)
    Ctl.OL.msFlag = 0x7F;               //过载保护
    #endif
    #if(OCRESTART_EN) 
    Ctl.OC.u16nmsCount++;               //过载保护重启等待时间
    #endif
    #if(NOLOAD_EN)
    if(Drv.AdcMeas.ImeasBus > MECASENOLOADCURRENT)
    {
      Ctl.Tim.NOloadCounter++;
    }
    else
    {
      Ctl.Tim.NOloadCounter--;
    }
    #endif
  }
  else
  {
    Ctl.Tim.u16PowerOnNms++;            //上电定时器
  }
}