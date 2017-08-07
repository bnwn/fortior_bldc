
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
#include "MC_UserInterface_layer.h"
#include "MC_MotorCotrol_layer.h"  
#include "MC_Beep.h"
#include "fu68xx_Dmc.h"
#include "MC_PwmIn.h"


/* Private typedef ------------------------------------------------------------------------------*/
/* Private define -------------------------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------------------------*/
PWMINCtl_TypeDef xdata PWMINCtl;
u8 xdata PwmInResetFlag;

/* Private function prototypes ------------------------------------------------------------------*/
void PWMINOnOffSwitch(void);
/* Private functions ----------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
Function Name :	void PWMIN_Init(void)
Description   :	PWM��������ʼ��
Input         :	��
Output				:	��
-------------------------------------------------------------------------------------------------*/
void PWMINInit(void)
{
  float tfAlineA;
  #if(PWMINSREF_EN)
  PWMINCtl.FlagPWMAline = 0x7F;
  #if(BEEPSCAN_EN)
  PWMINCtl.FlagPwmIn = 0xF1;
  #else
  PWMINCtl.FlagPwmIn = 0xFF;
  #endif
  PWMINCtl.PWMINStartCnt = 0;  PWMINCtl.PWMINBreakCnt = 0;
  PWMINCtl.PWMINHigh = 0;
  PWMINCtl.PWMINPeriod = 0;
  PWMINCtl.PWMINHighDuty = 0;
  PWMINCtl.PWMINHighErr = 0;
  PWMINCtl.PWMINHighMin = 0;
  PWMINCtl.PWMINHighMax = 0;
  PWMINCtl.PWMStatus = 255;
	PWMINCtl.PWMINIdle = TRUE;
  
  //PWMIN Ĭ��ֵ
  if(!(PWMINCtl.PWMINHighMin && PWMINCtl.PWMINHighMax))
  {
    PWMINCtl.PWMINHighMin = TempPWMHighMinDefault;
    PWMINCtl.PWMINHighMax = TempPWMHighMaxDefault; 
  }

  MDUControl.AlineX2 = 32767*((float)PWMINCtl.PWMINHighMax/(float)PWMINCtl.PWMINHighMax);
  MDUControl.AlineX1 = 32767*((float)(PWMINCtl.PWMINHighMin + TempMotorONTimeErr)/(float)PWMINCtl.PWMINHighMax);

  //MDUControl.SpeedSref = PWMINCtl.PWMINHigh;
  MDUControl.SpeedSrefErr = MDUControl.AlineX2 - MDUControl.AlineX1; ;

  tfAlineA= ((float)(SPEED_REF_MAX-SPEED_REF_MIN)/(MDUControl.SpeedSrefErr));
  MDUControl.AlineA = (u16)(tfAlineA*32767);
  MDUControl.AlineB = (SPEED_REF_MAX - MDUControl.AlineX2*tfAlineA);
  
#endif
}

/*-------------------------------------------------------------------------------------------------
Function Name :	void PWMScan(void)
Description   : //670 ~ 1559
Input         :	��
Output				:	��
-------------------------------------------------------------------------------------------------*/
void PWMScan(void)
{
}

/*-------------------------------------------------------------------------------------------------
Function Name :	void PWMINOnOffSwitch(void)
Description   :  С��900us ɲ��  С��920us ͣ�� ����920us ~2000us ����
Input         :	��
Output				:	��
-------------------------------------------------------------------------------------------------*/

void PWMINOnOffSwitch(void)
{
  float tfAlineA;
  #if(PWMINSREF_EN)
  if(PWMINCtl.FlagPwmIn == 0xF1)  //�ϵ����ű�����������У׼ ������Ϣ��ȡ
  {
    if(PWMINCtl.PWMINHigh == 0) //���ű���
    { 
      BeepRequestFun(PWMINError);
      PWMINCtl.FlagPwmIn = 0xF1;
    }
    else if(PWMINCtl.PWMINHigh > TempPWMHighMaxAline) //����У׼����A
    {
      #if(PWMINALINE_EN)
      PWMINCtl.FlagPwmIn = 0xF1;
      PWMINCtl.PWMINCnt ++;
      if(PWMINCtl.PWMINCnt > 3000)
      {
        PWMINCtl.PWMINCnt = 3000;	
        if(PWMINCtl.FlagPWMAline == 0x7F)
        {
          PWMINCtl.PWMINHighMax = PWMINCtl.PWMINHigh - 20; //�������ֵ��ȥ 30
          BeepRequestFun(PWMINAline);
        }
      }
      #else
      PWMINCtl.PWMINCnt = 0;
      PWMINCtl.FlagPwmIn = 0xF1;
      if(PWMINCtl.FlagPWMAline = 0x7F)
      {
        BeepRequestFun(PWMINError);
    }      
      #endif
    }
    else if(PWMINCtl.PWMINHigh < TempPWMHighMinAline) //����У׼����B
    {
      PWMINCtl.FlagPwmIn = 0xF1;
      PWMINCtl.PWMINCnt --;
      
      if(Beep.BeepType != PWMINReady)
      {
        if(PWMINCtl.PWMINCnt < -10)
        {
          PWMINCtl.PWMINCnt = -10;
          #if(PWMINALINE_EN)
          if(PWMINCtl.FlagPWMAline == 0xFF)
          {
            PWMINCtl.PWMINHighMin = PWMINCtl.PWMINHigh;
//            while(Flash_Sector_Erase((uint8 xdata *)16128)); // ��д��126������16128~16255��
//            while(Flash_Sector_Write((uint8 xdata *)16128, PWMINCtl.PWMINHighMin)); // д��С���ŵ��ֽ�
//            while(Flash_Sector_Write((uint8 xdata *)16129, (PWMINCtl.PWMINHighMin >> 8))); // д������Ÿ��ֽ�
//            while(Flash_Sector_Write((uint8 xdata *)16130, PWMINCtl.PWMINHighMax)); // д������ŵ��ֽ�
//            while(Flash_Sector_Write((uint8 xdata *)16131, (PWMINCtl.PWMINHighMax >> 8))); // д������Ÿ��ֽ�
          }
          PWMINCtl.PWMINHighMin = ((*(unsigned char code *)16129)<<8) + (*(unsigned char code *)16128);
          PWMINCtl.PWMINHighMax = ((*(unsigned char code *)16131)<<8) + (*(unsigned char code *)16130);
          #endif 
          if(!(PWMINCtl.PWMINHighMin && PWMINCtl.PWMINHighMax))
          {
            PWMINCtl.PWMINHighMin = TempPWMHighMinDefault;
            PWMINCtl.PWMINHighMax = TempPWMHighMaxDefault; 
          }
        
          MDUControl.AlineX2 = 32767*((float)(PWMINCtl.PWMINHighMax - TempPWMINHighMinFilt)/(float)PWMINCtl.PWMINHighMax);
          MDUControl.AlineX1 = 32767*((float)(PWMINCtl.PWMINHighMin - TempPWMINHighMinFilt + TempMotorONTimeErr)/(float)PWMINCtl.PWMINHighMax);

          //MDUControl.SpeedSref = PWMINCtl.PWMINHigh;
          MDUControl.SpeedSrefErr = MDUControl.AlineX2 - MDUControl.AlineX1; ;

          tfAlineA = ((float)(SPEED_REF_MAX-SPEED_REF_MIN)/(MDUControl.SpeedSrefErr));
          if(tfAlineA > 2.0)
          {
            tfAlineA = 1.9999;
          }
          MDUControl.AlineA = (u16)(tfAlineA*32767);
          MDUControl.AlineB = (SPEED_REF_MAX - MDUControl.AlineX2*tfAlineA);

          BeepRequestFun(PWMINReady);
        }
      }
    }
    else                        //���ű���
    {
      PWMINCtl.PWMINCnt = 0;
      PWMINCtl.FlagPwmIn = 0xF1;
      if(PWMINCtl.FlagPWMAline == 0x7F)
      {        BeepRequestFun(PWMINError);
      }
    }
  }
  else                          //PWMIN�ϵ�У׼���
  {
		 if(PWMINCtl.PWMINHigh == 0) //
    {
      Uc.flg.START = FALSE;
			PWMINCtl.PWMINIdle = TRUE;
			BeepRequestFun(PWMINError);
    }
    if(PWMINCtl.PWMINHigh <= (PWMINCtl.PWMINHighMin + TempMotorOFFTimeErr))
    {
      PWMINCtl.PWMINCnt --;
      if(PWMINCtl.PWMINCnt < -5)
      {	
        PWMINCtl.PWMINCnt = -5;

//        PwmInResetFlag = 0x7F;
        Uc.flg.START = FALSE;
				PWMINCtl.PWMINIdle = TRUE;
        if(Ctl.SysError != NONE)
        {
          Ctl.SysError = NONE;        
          Ctl.State = MOTOR_STOP; 
          DRV_OE_ON;
        }        
        
      }
		}
//      if(PWMINCtl.PWMINHigh <= (PWMINCtl.PWMINHighMin + TempMotorBreakTime))    //ɲ���ж�
//      {
//        PWMINCtl.PWMINBreakCnt++;
//        if(PWMINCtl.PWMINBreakCnt > 100)
//        {
//          PWMINCtl.PWMINBreakCnt = 100;
//          PwmInResetFlag = 0x7F;
//          //Ctl.FnStopmodeC = BREAK_DOWN;
//        }
//      }
//      else
//      {
//        PWMINCtl.PWMINBreakCnt--;
//        if(PWMINCtl.PWMINBreakCnt < -100)
//        {
//          PWMINCtl.PWMINBreakCnt = -100;
//          //Ctl.FnStopmodeC = FREE_DOWN;
//        }
//      }
    
    else if(PWMINCtl.PWMINHigh > (PWMINCtl.PWMINHighMin + TempMotorONTimeErr))
    {
      PWMINCtl.PWMINCnt ++;
      if(PWMINCtl.PWMINCnt > 100)
      {
        PWMINCtl.PWMINCnt = 100;
        if((PwmInResetFlag == 0X7F)&&(Uc.flg.START == FALSE)) 
        {
          Beep.BeepRequest = 0xFF;

          Uc.flg.START = TRUE;
          PwmInResetFlag = 0XFF;
        }
      }
    }
  }
  #endif
}