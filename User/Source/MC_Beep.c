
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

//do re mi fa so la ti do
//C:261.6256     229
//D:293.6648     204
//E:329.6276     182
//F:349.2282     171
//G:391.9954     153
//A:440          136
//B:493.8833     121
uc8 BeepNote[7] = {229,204,182,171,153,136,121};
Beep_TypeDef xdata Beep;

void BeepRequestFun(u8 mold);
u8 BeepResponse(void);
void Beepperform(void);
/*-------------------------------------------------------------------------------------------------
  Function Name : void BeepInit(void)
  Description   : 发声控制初始化
  Input         : 无
  Output        : 无
-------------------------------------------------------------------------------------------------*/
void BeepInit(void)
{
  Beep.BeepRequest = 0xFF;
  Beep.BeepType = 0;
}

void BeepTone(u8 tBeepNote,float tvolume,u16 time)
{
  u16 i;
  #if(BEEPSCAN_EN)
  EA = 0;
  if(tBeepNote > 7)
  {
    tBeepNote = 7;
  }
  if(tvolume > 1.0)
  {
    tvolume = 1.0;
  }
  tBeepNote = BeepNote[tBeepNote]*tvolume*BEEP_VOL;
  for(i=0; i< time;i++)
  {
    PWM_UHVL_ON;
    Delay(tBeepNote);
    PWMOUT_OFF;
    Delay(tBeepNote*3);
    PWM_VHUL_ON;
    Delay(tBeepNote);
    PWMOUT_OFF;
    Delay(tBeepNote*3);
  }
  EA = 1;
  #endif
}

void Beepperform(void)
{
  u16 i,k;
  u8 j,tBeepNote;
  for(k=0; k< 1;k++)
  {
    for(j=0; j< 3;j++)
    {
      BeepTone(j,0.4,500);
    }
    //Delay(20000);
  }
  EA = 0;
  Delayus(10000);
  EA = 1;
  Beep.BeepType = BeepDone;
}

u8 BeepResponse(void)
{
  #if(BEEPSCAN_EN)
  if(Beep.BeepRequest == 0x7F)
  {
    switch(Beep.BeepType)
    {
      case PWMINAline:
        BeepTone(1,0.3,1000);
        EA = 0;
        Delayus(5000);
        EA = 1;
        BeepTone(1,0.3,1000);
        PWMINCtl.FlagPWMAline = 0xFF;
        Beep.BeepRequest = 0xFF;
      break;
      case PWMINReady:
        BeepTone(1,0.3,1500);
        Beep.BeepRequest = 0xFF;
        PWMINCtl.FlagPwmIn = 0xFF;
      break;
      case PWMINError:
        BeepTone(1,0.2,1000);
        EA = 0;
        Delayus(20000);
        EA = 1;
        BeepTone(1,0.2,1000);
        break;    
      case SelfInspection:
        Beepperform();
        Beep.BeepType = BeepDone;
        break; 
      case BeepDone:
        break;      
      default:
        break;
    }
  }
  Beep.BeepRequest = 0xFF;
  #else
  PWMINCtl.FlagPwmIn = 0xFF;
  #endif
}

void BeepRequestFun(u8 mold)
{ 
  if(Beep.BeepRequest == 0xFF)
  {
    Beep.BeepRequest = 0x7F;
    Beep.BeepType = mold;
    if(Beep.BeepType == PWMINAline)
    {
      PWMINCtl.FlagPWMAline = 0x7F;
    }
  }
}