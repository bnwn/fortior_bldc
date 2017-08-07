
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
Uc_TypeDef xdata Uc;              //��������

//_iq xdata SpeedCoefficient;     //�ٶ�ϵ�� extern u8 xdata WriteRomValue;
extern u8 xdata ReadRomValue;
extern u8 xdata u8KeyForbid;  
extern u8 xdata *PageRomAdress;//ROMҳ��ַ

/* Private function prototypes -----------------------------------------------*/void UI(void);         //ȫ�ֺ���  ����

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : UI
* Description    : a������ָʾ���¶ȼ��㡢ADCת�����ٶ�ʵ��ֵ���� 
                   b������ת����������ٶ��������
                   c������ִ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UI(void)        //��������
{   
//-----------------------------------------
//hall��ȡ
  //Drv.Hall.Status = Hall_IRQHandler();
  
//-----------------------------------------
//����ָʾ
  Fault_Led(Ctl.SysError);
  
//-----------------------------------------
//��λָʾ��������ʾ
  LED_show();
  
//-----------------------------------------
//ADCʵ��ֵת��
  ADCGetConversionValue();

//-----------------------------------------  
//ʵ��ת�� rpm 
#if (SPEED_CALC_EN == 2)
  MDUControl.FlagCalcSpeedRpm = 0x7F;    
#endif
//-----------------------------------------
//�����ж�
#if(OVERLOAD_EN) 
  Ctl.OL.Value = MCL_OverLoadCalc(Drv.AdcMeas.ImeasBus);
#endif

//-----------------------------------------
//�¶ȼ���  
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
  
  //Mcl_NoloadCale();//�жϵ���Ƿ����   Ctl.Noload.Flag = 0x7F ���� OXFF����
#if(BEEPSCAN_EN)
  BeepResponse();
#endif//=====================================================
//���ػ� ����  �ٶȸ��� ����ת����
//-----------------------------------------------------
//ON/OFF ����ģʽ
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
//����ת����λ�������
////Xn�����������  -> ����ִ�� �ᴥ�Ϳ���
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
    WriteRomValue = (u8)Ctl.spd.SpeedShift;//���絵λ�洢
  }
#endif
//Xn�����������  -> ����ִ��   ����������
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
//Xn�����������  -> ����ִ�� �ᴥ�Ϳ���
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
//����������� ADC������������������������
//Xn�����������  -> ����ִ�� �ᴥ�Ϳ���
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
  //��λ�ƿ���
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

//    Ctl.SysError = NONE;  //�������
//    Ctl.State = MOTOR_READY; 
//    DRV_OE_ON;
  }  
#endif
  //Ctl.Is.refTar = Drv.AdcMeas.Sref>>2;   //���������

#if(PWMINSREF_EN) //PWMIN ����
  MDUControl.FlagTargetSpeed = 0x7F ;      //�ٶȸ�����������          
  
  Ctl.spd.refTar = MDUControl.TargetSpeed;
  Drv.PWM.DutytargetOpen = MDUControl.TargetSpeed;
#elif(ADCSREF_EN) //ADC ����
  MDUControl.FlagTargetSpeed = 0x7F ;     //�ٶȸ����������� 
  MDUControl.SpeedSref = Drv.AdcMeas.Sref;

  Ctl.spd.refTar = MDUControl.TargetSpeed;
  Drv.PWM.DutytargetOpen = MDUControl.TargetSpeed;
#endif

//-----------------------------------------
//����ִ��
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
//��HALL ����޷� �Ƚ�������ģʽ
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

