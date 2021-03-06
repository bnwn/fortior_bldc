
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
Uc_TypeDef xdata Uc;              //变量定义

//_iq xdata SpeedCoefficient;     //速度系数 extern u8 xdata WriteRomValue;
extern u8 xdata ReadRomValue;
extern u8 xdata u8KeyForbid;  
extern u8 xdata *PageRomAdress;//ROM页地址

/* Private function prototypes -----------------------------------------------*/void UI(void);         //全局函数  声明

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : UI
* Description    : a、故障指示、温度计算、ADC转换、速度实际值计算 
                   b、正反转命令给定、速度命令给定
                   c、命令执行
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UI(void)        //函数定义
{   
//-----------------------------------------
//hall读取
  //Drv.Hall.Status = Hall_IRQHandler();
  
//-----------------------------------------
//故障指示
  Fault_Led(Ctl.SysError);
  
//-----------------------------------------
//档位指示，电量显示
  LED_show();
  
//-----------------------------------------
//ADC实际值转换
  ADCGetConversionValue();

//-----------------------------------------  
//实际转速 rpm 
#if (SPEED_CALC_EN == 2)
  MDUControl.FlagCalcSpeedRpm = 0x7F;    
#endif
//-----------------------------------------
//过载判断
#if(OVERLOAD_EN) 
  Ctl.OL.Value = MCL_OverLoadCalc(Drv.AdcMeas.ImeasBus);
#endif

//-----------------------------------------
//温度计算  
#if(OH1_EN)
  Drv.AdcMeas.Therm1 = Drv_PowerThermCalc(Drv.AdcMeas.Vth1);
  if(Drv.AdcMeas.Therm1 == 200)
  {
    Drv.AdcMeas.Therm1 = 25;
  }
#endif

#if(OH2_EN)
  Drv.AdcMeas.Therm2 = Drv_PowerThermCalc(Drv.AdcMeas.Vth2);
  //Drv.AdcMeas.Therm3 = Drv_PowerThermCalc(Drv.AdcMeas.Vth3);
  #endif
  
  //Mcl_NoloadCale();//判断电机是否空载   Ctl.Noload.Flag = 0x7F 空载 OXFF带载
#if(BEEPSCAN_EN)
  BeepResponse();
#endif//=====================================================
//开关机 命令  速度给定 正反转给定
//-----------------------------------------------------
//ON/OFF 测试模式
#if(0)
  if((Ctl.Tim.OnOffnms > 10)&&(Ctl.Tim.OnOffnms < 500))   
  {
    Uc.flg.START = FALSE;
  }
  else if (Ctl.Tim.OnOffnms < 1200)
  {
    //Ctl.Tim.OnOffnms = 1000;
    Uc.flg.START = TRUE;  
  }     
  else
  {
    Ctl.Tim.OnOffnms = 0; //15001
  }
  #endif
//=====================================================
//---------------------------------------------------
//正反转，档位命令给定
////Xn按键命令给定  -> 命令执行 轻触型开发
#if(0)
  if(X1.Kflg == TRUE)
  {
    X1.Kflg = FALSE;
    X1.KNum = FALSE;
    SpeedShift--;

   if(Ctl.spd.SpeedShift < 1)
    {
      Ctl.spd.SpeedShift = 1;
    }
    WriteRomValue = (u8)Ctl.spd.SpeedShift;//掉电档位存储
  }
#endif
//Xn端子命令给定  -> 命令执行   常开常闭型
#if(0)
  if(X3.XCount == KEY_FILTERCOUNT)
  { 
    Uc.flg.FR = CCW;
  }
  else if(X3.XCount == -KEY_FILTERCOUNT)
  {
    Uc.flg.FR = CW;
  }
#endif
//Xn按键命令给定  -> 命令执行 轻触型开发
#if(0)
  if(X3.Kflg == TRUE)
  {
    X3.Kflg = FALSE;
    X3.KNum = FALSE;
     
    if(Uc.flg.FR == CW)
    {
      Uc.flg.FR = CCW;
    }
    else if(Uc.flg.FR == CCW)
    {
      Uc.flg.FR = CW;
    }
  }
#endif
//---------------------------------------------------
//启动命令给定 ADC启动、按键启动、端子启动
//Xn按键命令给定  -> 命令执行 轻触型开发
#if (KEYONOFF_EN == 1) 
  if(X2.Kflg == TRUE)
  {
    X2.Kflg = FALSE;
    X2.KNum = FALSE;
    
    if(Uc.flg.START == TRUE)
    {
      Uc.flg.START = FALSE;
    }
    else
    {
      Uc.flg.START = TRUE;
    }      
  }
#elif (KEYONOFF_EN == 2)
  if(X0.XCount == KEY_FILTERCOUNT)
  { 
    Uc.flg.START = FALSE;
  }
  else if(X0.XCount == -KEY_FILTERCOUNT)
  {
    Uc.flg.START = TRUE;
  }
#elif(ADCONOFF_EN)
  //电位计开关
  if(Drv.AdcMeas.Sref > ADCREFONVALUE)
  {
    Ctl.spd.SwitchCount++;
  }
  //else if((Drv.AdcMeas.Sref < _IQ(0.02))&&(Drv.PWM.DutyCurrent < _IQ(0.02)))
  else if(Drv.AdcMeas.Sref < ADCREFOFFVALUE)
  {
    Ctl.spd.SwitchCount--;
  }
  if(Ctl.spd.SwitchCount > SREFCOUNT)
  {
    Ctl.spd.SwitchCount = SREFCOUNT;
    Uc.flg.START = TRUE;
  }
  else if(Ctl.spd.SwitchCount < -SREFCOUNT) 
  {
    Ctl.spd.SwitchCount = -SREFCOUNT;
    Uc.flg.START = FALSE;

//    Ctl.SysError = NONE;  //清除故障
//    Ctl.State = MOTOR_READY; 
//    DRV_OE_ON;
  }  
#endif
  //Ctl.Is.refTar = Drv.AdcMeas.Sref>>2;   //电流环给�

#if(PWMINSREF_EN) //PWMIN 调速
  MDUControl.FlagTargetSpeed = 0x7F ;      //速度给定计算请求          
  
  Ctl.spd.refTar = MDUControl.TargetSpeed;
  Drv.PWM.DutytargetOpen = MDUControl.TargetSpeed;
#elif(ADCSREF_EN) //ADC 调速
  MDUControl.FlagTargetSpeed = 0x7F ;     //速度给定计算请求 
  MDUControl.SpeedSref = Drv.AdcMeas.Sref;

  Ctl.spd.refTar = MDUControl.TargetSpeed;
  Drv.PWM.DutytargetOpen = MDUControl.TargetSpeed;
#endif

//-----------------------------------------
//命令执行
  if((Uc.flg.START == TRUE)&&(Uc.flg.FR != NONE))  
  {
    Ctl.Start = TRUE;
  } 
  else if(Uc.flg.START == FALSE)
  {                   
    if(Ctl.FnStopmodeC == FREE_DOWN)
    {
      Ctl.Start = FALSE;
			PWMINCtl.PWMINIdle = TRUE;
    }
    else if(Ctl.FnStopmodeC == SLOWING_DOWN)
    {
      Ctl.spd.refTar = 0;
      Drv.PWM.DutytargetOpen = 0;
      if(Ctl.State == MOTOR_NORMAL)
      {
        #if(SPEED_CLOSE_EN)
        if(((Ctl.spd.refCur<_IQ(0.05))))
        {
          Ctl.Start = FALSE;
					PWMINCtl.PWMINIdle = TRUE;
        }      
        #else
        if((Drv.PWM.DutyCurrent < _IQ(0.05)))
        {
          Ctl.Start = FALSE;
					PWMINCtl.PWMINIdle = TRUE;
        }      
        #endif
      }
      else
      {
        Ctl.Start = FALSE;
				PWMINCtl.PWMINIdle = TRUE;
      }
    } 
    else if(Ctl.FnStopmodeC == BREAK_DOWN)
    {
      Ctl.Start = FALSE;
			PWMINCtl.PWMINIdle = TRUE;
    }      
  }

  if(Ctl.State == MOTOR_NORMAL)
  {
    Drv.PWM.Dutytarget = Drv.PWM.DutytargetOpen;
  }
  
//=====================================================
//无HALL 输出限幅 比较器触发模式
#if (POSITION_FB_MODE == SENSORLESS)  
//    if(Drv.PWM.DutytargetOpen < Ctl.Ramp.cpDutyEnd)
//    {
//      Drv.PWM.DutytargetOpen = Ctl.Ramp.cpDutyEnd ;
//    }
  #if (CMPSAME_EN == 1) 
    SetBit(CMP_CR2, CMPSAME, 1);
  #elif (CMPSAME_EN == 2)
    if(Drv.PWM.DutyCurrent > CMPSAMESWITCH)         //CMPSAMESWITCH
    {
      SetBit(CMP_CR2, CMPSAME, 0);
    }
    else
    {
      SetBit(CMP_CR2, CMPSAME, 1);
    }
  #endif

#endif
}

