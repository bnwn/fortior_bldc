
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

#ifndef __TEMPCONSTANT_H_
#define __TEMPCONSTANT_H_

 //-----------------------------------------------------------------------------
//PWM PWM��������
//TIM1
#define PWMPeriod                 (1000000/PWM_FREQ)            //��λ us %% PWMPeriod = 1/PWMFre 
#define PWMARR                    (SYSCLK_FREQ/PWM_FREQ)        //��λ -- %% PWMARR = 24MHZ/16KHz
#define PWMDIV                    (32767/PWMARR)                //��λ -- %% 
#define PWM_PRESCALER             (PWM_FREQ/1000)               //��λ -- %%  
//-----------------------------------------------------------------------------
//BEMF
#define BEMFNONE          0XF0                                  //��λ --
#define BEMFCOMMUTATION   0xF1                                  //��λ --
#define BEMFCMASK         0xF2                                  //��λ --

#define RAMP_PWMARR               (SYSCLK_FREQ/PAMP_PWM_FREQ) // PWMARR = 24MHZ/16KHz/2
#define ELEC_FREQ                 (POLE_PAIR*BASE_SPEED/60)     //��λ -- ����Ƶ��

#define TIM1PSC24M               24000000
#define TIM1PSC12M               12000000                       //��λ -- %% 
#define TIM1PSC6M                 6000000                       //��λ -- %% 
#define TIM1PSC3M                 3000000                       //��λ -- %% 
#define TIM1PSC1_5M               1500000                       //��λ -- %% 
#define TIM1PSC750K                750000                       //��λ -- %% 
#define TIM1PSC375K                375000                       //��λ -- %% 
#define TIM1PSC187_5K              187500                       //��λ -- %% 
#define TIM1PSC93_75K               75000                       //��λ -- %% 
#define TIM1PSC46_875K              46875                       //��λ -- %% 
#define TIM1PSC23_4375K             23767                       //��λ -- %% 
#define TIM1PSC15_625K              15625                       //��λ -- %% 

#if (ELEC_FREQ > 3000)
  #define TIM1_PSC                   (TIM1PSC24M)                //��λ -- 
#elif (ELEC_FREQ > 2000)
  #define TIM1_PSC                   (TIM1PSC12M)                //��λ -- 
#elif (ELEC_FREQ > 1000)
  #define TIM1_PSC                   (TIM1PSC6M)                //��λ -- #elif (ELEC_FREQ > 500)
  #define TIM1_PSC                   (TIM1PSC3M)                //��λ -- 
#else
  #define TIM1_PSC                   (TIM1PSC1_5M)                //��λ -- 
#endif
//675 722 1374
//����ģ�� 666 1547
//============================================================================
//TIM3 ��Ƶ
#define TIM3_Fre                          (750000.0)           //TIM3����Ƶ��750KHz
//PWMIN  ������峵 ���ſ���
//PWMIN ����У��
#define TempMotorBreakTime                (u16)(MotorBreakTime*TIM3_Fre/1000000.0) //ɲ������ʱ��, us
//#define TempMotorOFFTime                  (u16)(MotorOFFTime*TIM3_Fre/1000000.0)   // us
//#define TempMotorONTime                   (u16)(MotorONTime*TIM3_Fre/1000000.0)  // us
#define TempMotorONTimeErr                (u16)(MotorONTimeErr*TIM3_Fre/1000000.0)  // us
#define TempMotorOFFTimeErr               (u16)(MotorOFFTimeErr*TIM3_Fre/1000000.0)  // us
#define TempPWMHighMinDefault             (u16)(PWMHighMinDefault*TIM3_Fre/1000000.0)   // �������У׼����, us
#define TempPWMHighMaxDefault             (u16)(PWMHighMaxDefault*TIM3_Fre/1000000.0)   // �������У׼����, us
#define TempPWMHighMinAline               (u16)(PWMHighMinAline*TIM3_Fre/1000000.0)   // �������У׼����, us
#define TempPWMHighMaxAline               (u16)(PWMHighMaxAline*TIM3_Fre/1000000.0)   // �������У׼����, us
#define TempPWMINHighMinFilt              (u16)(PWMINHighMinFilt*TIM3_Fre/1000000.0)   // �������У׼����, us
#define TempPWMINHighMaxFilt              (u16)(PWMINHighMaxFilt*TIM3_Fre/1000000.0)   // �������У׼����, us
#define TempPWMINIdling                   (u16)(PWMIdling*TIM3_Fre/1000000.0)         // ��������
#define TempPWMINStartUp                  (u16)(PWMINStartUp*TIM3_Fre/1000000.0)

#define TempDelayTime                     (u16)(DELAY_TIMEUS*TIM1_PSC/1000.0) // �������νǶȣ���λ�� /
#define TempMaskTime                      (u16)(MASK_TIMEUS*TIM1_PSC/1000.0) // �������νǶȣ���λ�� /
#define TempRampMaskTime                  (u16)(RampMaskTime*TIM1_PSC/1000.0) // �������νǶȣ���λ�� //----------------------------------------------------------------------------------
/*Angle Control*/                                   
#define TEMPMASKANGLE                     (u16)(MASK_ANGLE*32767.0/60.0)          // �������νǶȣ���λ��
#define TEMPDELAYANGLE                    (u16)(DELAY_ANGLE*32767.0/60.0)         // �ӳٻ���Ƕȣ���λ��
#define TEMPHALLADVANCEEANGLE             (s16)(HALLADVANCEEANGLE*32767.0/60.0)
//-----------------------------------------------------------------------------
//�����˲�ʱ�� ��λ����  С��10ms
#define KEY_FILTERNMS             (10)                          //��λms %%
#define KEY_FILTERCOUNT           (KEY_FILTERNMS*(10))          //��λ -- %% 
#define MSCOUNTE                  (10)                          //��λ -- %%  

//-----------------------------------------------------------------------------
//�ٶȼ���
//Drv.speed.SpeedScaler = _IQ((60*(float)750000)/(6*(float)Ctl.Motor.PolePairs*Ctl.Motor.BaseSpeed)); 
#define SPEEDSCALER             (_IQ((60*(float)TIM1_PSC)/(6*(float)POLE_PAIR*BASE_SPEED)))
#define SPEEDSCALER1            ((60*(float)TIM1_PSC)/(6*(float)POLE_PAIR))
#define STB1SPEEDVALUE          ((u16)((float)SPEEDSCALER1/(float)STB1SPEED))
#define STB2SPEEDVALUE          ((u16)((float)SPEEDSCALER1/(float)STB2SPEED))
//-----------------------------------------------------------------------------
//ADC ��ѹ����
//Drv.AdcMeas.VdcMeasGain = (float)(RV_BUS_1+RV_BUS_2)/(float)RV_BUS_2;
//VGain = (float)(RV_BUS_1+RV_BUS_2)/(float)RV_BUS_2;
#define  V_GAIN                  (float)((float)(RV_BUS_1+RV_BUS_2)/(float)RV_BUS_2)
#define  VDCMEASEGAIN            (float)(5.0*(V_GAIN)/0x7FFF)

#define  MECASEOVERVOLTAGE        (OVERVOLTAGE/VDCMEASEGAIN)
#define  MECASEUNDERVOLTAGE       (UNDERVOLTAGE/VDCMEASEGAIN)
#define  MECASEOVREERVOLTAGE      (OVREERVOLTAGE/VDCMEASEGAIN) 
#define  MECASEUNREDERVOLTAGE     (UNREDERVOLTAGE/VDCMEASEGAIN)
//-----------------------------------------------------------------------------//��������
//IGain = ((float)RI_BUS_1/(float)RI_BUS_2)+ 1;      
//Drv.AdcMeas.IBusMeasGain = 5.0/(Rs*0x7FFF*IGain);
#define  I_GAIN                   (((float)RI_BUS_1/(float)RI_BUS_2)+ 1)
#define  IBUSMEASGAIN             (5.0/(Rs*0x7FFF*I_GAIN))

#define  MECASEOVERCURRENT        (u16)(OVERCURRENT/IBUSMEASGAIN)
#define  MECASEOVERLOAD0          (u16)(OVERLOAD0/IBUSMEASGAIN)
#define  MECASEOVERLOAD1          (u16)(OVERLOAD1/IBUSMEASGAIN)
#define  MECASEOVERLOAD2          (u16)(OVERLOAD2/IBUSMEASGAIN)
#define  MECASEOVERLOAD3          (u16)(OVERLOAD3/IBUSMEASGAIN)

#define  MECASENOLOADCURRENT      (u16)(NOLOADCURRENT/IBUSMEASGAIN)
#define  MECASECURRENTLIMITMAXREF (u16)(CURRENT_LIMIT_MAXREF/IBUSMEASGAIN)
                    

//======================================================================
#if ((SPEED_CLOSE_EN==1)&&(SPEED_CALC_EN==0))     
#error ERROR  FORBID SPEED_CLOSE_EN+SPEED_CALC_EN
#endif
#if ((ADCSPEEDREF_EN==1)&&(PWMINSPEEDREF_EN==1))     
#error ERROR  FORBID ADCSPEEDREF_EN+PWMINSPEEDREF_EN
#endif

#if ((ADCSPEEDREF_EN==1)&&(PWMINSPEEDREF_EN==1))     
#error ERROR  FORBID ADCSPEEDREF_EN+PWMINSPEEDREF_EN
#endif

#if (((ICMODE == IC_FU6831)||(ICMODE == IC_FU6818))&&(DriverFD6536_EN == 1))
//#error ERROR FORBID  IC_FU6831+FD6536 OR FU6818+FD6536
#endif 
//======================================================================
#endif