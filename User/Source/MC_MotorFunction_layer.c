
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
Power_TypeDef xdata Power;  
/* Private function prototypes -----------------------------------------------*/
float Drv_PowerThermCalc(u16 VthMeas);      //温度计算
u32 Drv_RotorCircleNumCalc(u8 value);       //运行圈数计算
void MCL_OverLoadInit(u16 OL0A,u16 OL1A,u16 OL2A,u16 OL3A,u32 OL0ms,u32 OL1ms,u32 OL2ms,u32 OL3ms);
u8 MCL_OverLoadCalc(u16 Ibus);              //过载计算

void Mcl_MotorRestart(void);                //电机重启
u8 Mcl_StallRestart(void);                  //堵转重启
void Mcl_NoloadCale(void);                  //空载判断
void Drv_PowerClosedCalc(void);             //--
void Drv_Stb3Calc(void);                    //失速判断
void Drv_BemfSetFRFun(void);                //电调转向设定

/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Function Name  : MCL_Inverter_OverCurrentInit    //过载 
* Description    : 
* Input          : PTC温度
* Output         : None
* Return         : ADC采集值
*******************************************************************************/

#if(OVERLOAD_EN)
void MCL_OverLoadInit(u16 OL0A,u16 OL1A,u16 OL2A,u16 OL3A,
                      u32 OL0ms,u32 OL1ms,u32 OL2ms,u32 OL3ms)
  {
    Ctl.OL.Value = 0x7F; 
    Ctl.OL.Group[0].Current = OL0A;
    Ctl.OL.Group[1].Current = OL1A;
    Ctl.OL.Group[2].Current = OL2A;
    Ctl.OL.Group[3].Current = OL3A;

    Ctl.OL.Group[0].Nms = OL0ms;
    Ctl.OL.Group[1].Nms = OL1ms;
    Ctl.OL.Group[2].Nms = OL2ms;
    Ctl.OL.Group[3].Nms = OL3ms;
      
    Ctl.OL.Group[0].msCounter = 0;
    Ctl.OL.Group[1].msCounter = 0;
    Ctl.OL.Group[2].msCounter = 0;
    Ctl.OL.Group[3].msCounter = 0;
    
    Ctl.OL.Group[0].flg = 0;
    Ctl.OL.Group[1].flg = 0;
    Ctl.OL.Group[2].flg = 0;
    Ctl.OL.Group[3].flg = 0;
  }
#endif


 /******************************************************************************* 
* Function Name  : MCL_Chk_Inverter_OverCurrent 
* Author         : wangt  
* Description     
* Input          : None 
* Output         : None 
* Return         : ?OR? 
*******************************************************************************/  
#if(OVERLOAD_EN) 
u8 MCL_OverLoadCalc(u16 Ibus)   
  { 
    u16 tIbus = 0;    //输入电流值
    tIbus = Ibus;

    if((Ctl.OL.msFlag == 0x7F)&&(Ctl.OL.Value == 0x7F)&&(Ctl.State == MOTOR_NORMAL))
      {
        if(tIbus >= Ctl.OL.Group[0].Current)    
          {  
             Ctl.OL.Group[0].msCounter++;
             if(tIbus >= Ctl.OL.Group[1].Current)  
             {
                 Ctl.OL.Group[0].msCounter++;
                 Ctl.OL.Group[1].msCounter++;
                 if(tIbus >= Ctl.OL.Group[2].Current) 
                 {
                     Ctl.OL.Group[0].msCounter++;
                     Ctl.OL.Group[1].msCounter++;
                     Ctl.OL.Group[2].msCounter++;
                     if(tIbus>=Ctl.OL.Group[3].Current) 
                     {  
                         Ctl.OL.Group[0].msCounter++;
                         Ctl.OL.Group[1].msCounter++;
                         Ctl.OL.Group[2].msCounter++;
                         Ctl.OL.Group[3].msCounter++;
                     }
                     else
                     {
                        Ctl.OL.Group[3].msCounter--;  
                     }
                 }
                 else
                 {
                     Ctl.OL.Group[2].msCounter--;  
                     Ctl.OL.Group[3].msCounter--;  
                 }
             }
             else
             {
                 Ctl.OL.Group[1].msCounter--;  
                 Ctl.OL.Group[2].msCounter--;  
                 Ctl.OL.Group[3].msCounter--;                
             }
          }
          else
          {   
             Ctl.OL.Group[0].msCounter--; 
             Ctl.OL.Group[1].msCounter--;  
             Ctl.OL.Group[2].msCounter--;  
             Ctl.OL.Group[3].msCounter--;  
          } 
       if(Ctl.OL.Group[0].msCounter >= Ctl.OL.Group[0].Nms) 
       {
         Ctl.OL.Group[0].flg = TRUE;
         Ctl.OL.Value = 0xF0; 
       }
       if(Ctl.OL.Group[1].msCounter >= Ctl.OL.Group[1].Nms)
       {
         Ctl.OL.Group[1].flg = TRUE; 
         Ctl.OL.Value = 0xF1; 
       }
       if(Ctl.OL.Group[2].msCounter >= Ctl.OL.Group[2].Nms)
       {
         Ctl.OL.Group[2].flg = TRUE; 
         Ctl.OL.Value = 0xF2; 
       }
       if(Ctl.OL.Group[3].msCounter >= Ctl.OL.Group[3].Nms)
       {
         Ctl.OL.Group[3].flg = TRUE;  
         Ctl.OL.Value = 0xF3; 
       }
       
       if(Ctl.OL.Group[0].msCounter<-100)
       {
         Ctl.OL.Group[0].msCounter = -100; 
       }
       if(Ctl.OL.Group[1].msCounter<-100)
       {
         Ctl.OL.Group[1].msCounter = -100;  
       }
       if(Ctl.OL.Group[2].msCounter<-100)
       {
         Ctl.OL.Group[2].msCounter = -100;  
       }
       if(Ctl.OL.Group[3].msCounter<-100)       {
         Ctl.OL.Group[3].msCounter = -100;  
       }

       Ctl.OL.msFlag = 0;
      }   
    return Ctl.OL.Value; 
  } 
#endif
  
/*******************************************************************************
* Function Name  : Drv_PowerThermCalc    
* Description    : 
* Input          : PTC温度
* Output         : None
* Return         : ADC采集值
*******************************************************************************/
float Drv_PowerThermCalc(u16 VthMeas)
  {
    u16 tVthMeas;
    float tTherm;

    tVthMeas =  VthMeas;

    if(tVthMeas<=8130)           
      {
        tTherm = 20.0;
      }
    else if(tVthMeas<=9320)
      {
        tTherm = 25.0;        
      }
    else if(tVthMeas<11869)
      {
        tTherm = 30.0;        
      }
    else if(tVthMeas<14016)
      {
        tTherm = 40.0;        
      }
    else if(tVthMeas<17134)
      {
        tTherm = 50.0;        
      }
    else if(tVthMeas<19578)
      {
        tTherm = 60.0;        
      }
    else if(tVthMeas<21770)
      {
        tTherm = 70.0;        
      }
    else if(tVthMeas<23672)
      {
        tTherm = 80.0;        
      }
    else if(tVthMeas<25278)
      {
        tTherm = 90.0;        
      }
    else if(tVthMeas<26611)
      {
        tTherm = 100.0;        
      }
    else if(tVthMeas<27704)
      {
        tTherm = 110.0;
      }
    else if(tVthMeas<30000)
      {
        tTherm = 120.0;
      }
    else
    {
      tTherm = 200;
    }
    return tTherm;      
  }  

/*******************************************************************************
* Function Name  : Drv_RotorCircleNumCalc    
* Description    : 
* Input          : PTC温度
* Output         : None
* Return         : ADC采集值
*******************************************************************************/
#if(MOTORCIRCLECALEEN)
u32 Drv_RotorCircleNumCalc(u8 value)   //Ctl.Step
{  
  s32 CircleNum;        
  s8 StepERR; 
  Ctl.spd.RotorPosition = value;

  StepERR = Ctl.spd.RotorPosition - Ctl.spd.RotorPositionqPre;
  if(StepERR == 5)
  {
    StepERR = -1;
  }
  else if(StepERR == -5)
  {
    StepERR = 1;
  }
  if(StepERR  == -1) 
  {
    Ctl.spd.ComNum--;
  }    
  else if(StepERR == 1)
  {
    Ctl.spd.ComNum++;
  }    

  Ctl.spd.RotorPositionqPre = Ctl.spd.RotorPosition; 

  CircleNum =  Ctl.spd.ComNum/(6*Ctl.Motor.PolePairs);  
  
  return CircleNum;  
}
#endif

/*******************************************************************************
* Function Name  : Mcl_MotorRestart    
* Description    : 重启参数清零
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void Mcl_MotorRestart(void)
{
  DRV_OE_ON;
  Ctl.SysError = NONE;     
  Ctl.State = MOTOR_READY;
}

/*******************************************************************************
* Function Name  : Mcl_StallRestart    
* Description    : 堵转重启
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
u8 Mcl_StallRestart(void)             //堵转重启
{
  //if(Ctl.Stall.u8Num < STALLRESTARTNUM)
  {
    Ctl.Stall.u8Num++;
    Ctl.Tim.STAnms = 0;
    Ctl.Tim.STB1nms = 0;
    Ctl.Tim.STB2nms = 0;
    Ctl.Stall.u8FL = 0;

    Mcl_MotorRestart();
  }
  return 1;
}

/*******************************************************************************
* Function Name  : Mcl_NoloadCale    
* Description    : 电机空载判断
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void Mcl_NoloadCale(void)            
{
  if(Ctl.Noload.Counter > NOLOADNUM)
  {
     if(Ctl.Noload.Counter > (NOLOADNUM))
     {
       Ctl.Noload.Counter = (NOLOADNUM);
     }
     Ctl.Noload.Flag = 0X7F;
  }
  else
  {
    Ctl.Noload.Flag = 0XFF;
  }
}

/*******************************************************************************
* Function Name  : Drv_PowerClosedCalc
* Description    : 测试程序
* Input          : 
* Output         : None
* Return         : 
*******************************************************************************/
void Drv_PowerClosedCalc(void)
{
  Power.err = Power.ref - Power.fdb;
  if(Power.err > 0)  
  {
    Drv.PWM.DutytargetOpen += 20;
  }
  else
  {
    Drv.PWM.DutytargetOpen -= 20;
  }  
}

/*******************************************************************************
* Function Name  : Drv_Stb3Calc
* Description    : 失速检测
* Input          : 
* Output         : None
* Return         : 
*******************************************************************************/
void Drv_Stb3Calc(void)
{
  #if(STB3_EN)
  if(Ctl.Section.Counter < 2)
  {
    ;
  }
  else //if(Ctl.Section.Counter < STB3WAIT)
  {
    if(((Ctl.Section.Cur >> 1) > Ctl.Section.Per)||(Ctl.Section.Cur < (Ctl.Section.Per>>1)))
    {
      Ctl.Section.ErrCounter += 2 ;
      if(Ctl.Section.ErrCounter >= STB3ERRVALUE)
      {
        Ctl.SysError = E_STB3;
        Ctl.Section.ErrCounter = 0;
      }
    }
    else
    {
      if(Ctl.Section.ErrCounter > 0)
      {
        Ctl.Section.ErrCounter--;
      }
    }
  }
//  else 
//  {
//    Ctl.Section.Counter = STB3WAIT;
//  }
  Ctl.Section.Per = Ctl.Section.Cur;
  #endif 
}

/*******************************************************************************
* Function Name  : Drv_BemfSetFRFun
* Description    : 电调方向设定
* Input          : 
* Output         : None
* Return         : 
*******************************************************************************/
void Drv_BemfSetFRFun(void)
{
  if(Drv.Stk.BemfSetFR == 0x00)
  {
    Drv.Stk.Calcnms = 0;
  }
  if(Drv.Stk.BemfFR!=0xFF)
  {
    if(Drv.Stk.BemfSetFR == 0)
    {
      while(Flash_Sector_Write((uint8 xdata *)BemfSetFRRomAddress, Drv.Stk.BemfFR)); 
      Drv.Stk.BemfSetFR = Drv.Stk.BemfFR;
      Uc.flg.FR  = Drv.Stk.BemfFR;
      Ctl.direction = Uc.flg.FR;
    }
  }
}

