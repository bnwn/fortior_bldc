
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
//PWM PWM参数配置
//TIM1
#define PWMPeriod                 (1000000/PWM_FREQ)            //单位 us %% PWMPeriod = 1/PWMFre 
#define PWMARR                    (SYSCLK_FREQ/PWM_FREQ)        //单位 -- %% PWMARR = 24MHZ/16KHz
#define PWMDIV                    (32767/PWMARR)                //单位 -- %% 
#define PWM_PRESCALER             (PWM_FREQ/1000)               //单位 -- %%  
//-----------------------------------------------------------------------------
//BEMF
#define BEMFNONE          0XF0                                  //单位 --
#define BEMFCOMMUTATION   0xF1                                  //单位 --
#define BEMFCMASK         0xF2                                  //单位 --

#define RAMP_PWMARR               (SYSCLK_FREQ/PAMP_PWM_FREQ) // PWMARR = 24MHZ/16KHz/2
#define ELEC_FREQ                 (POLE_PAIR*BASE_SPEED/60)     //单位 -- 最大电频率

#define TIM1PSC24M               24000000
#define TIM1PSC12M               12000000                       //单位 -- %% 
#define TIM1PSC6M                 6000000                       //单位 -- %% 
#define TIM1PSC3M                 3000000                       //单位 -- %% 
#define TIM1PSC1_5M               1500000                       //单位 -- %% 
#define TIM1PSC750K                750000                       //单位 -- %% 
#define TIM1PSC375K                375000                       //单位 -- %% 
#define TIM1PSC187_5K              187500                       //单位 -- %% 
#define TIM1PSC93_75K               75000                       //单位 -- %% 
#define TIM1PSC46_875K              46875                       //单位 -- %% 
#define TIM1PSC23_4375K             23767                       //单位 -- %% 
#define TIM1PSC15_625K              15625                       //单位 -- %% 

#if (ELEC_FREQ > 3000)
  #define TIM1_PSC                   (TIM1PSC24M)                //单位 -- 
#elif (ELEC_FREQ > 2000)
  #define TIM1_PSC                   (TIM1PSC12M)                //单位 -- 
#elif (ELEC_FREQ > 1000)
  #define TIM1_PSC                   (TIM1PSC6M)                //单位 -- #elif (ELEC_FREQ > 500)
  #define TIM1_PSC                   (TIM1PSC3M)                //单位 -- 
#else
  #define TIM1_PSC                   (TIM1PSC1_5M)                //单位 -- 
#endif
//675 722 1374
//油门模拟 666 1547
//============================================================================
//TIM3 分频
#define TIM3_Fre                          (750000.0)           //TIM3计数频率750KHz
//PWMIN  电调滑板车 油门控制
//PWMIN 输入校正
#define TempMotorBreakTime                (u16)(MotorBreakTime*TIM3_Fre/1000000.0) //刹车油门时间, us
//#define TempMotorOFFTime                  (u16)(MotorOFFTime*TIM3_Fre/1000000.0)   // us
//#define TempMotorONTime                   (u16)(MotorONTime*TIM3_Fre/1000000.0)  // us
#define TempMotorONTimeErr                (u16)(MotorONTimeErr*TIM3_Fre/1000000.0)  // us
#define TempMotorOFFTimeErr               (u16)(MotorOFFTimeErr*TIM3_Fre/1000000.0)  // us
#define TempPWMHighMinDefault             (u16)(PWMHighMinDefault*TIM3_Fre/1000000.0)   // 最低油门校准下限, us
#define TempPWMHighMaxDefault             (u16)(PWMHighMaxDefault*TIM3_Fre/1000000.0)   // 最高油门校准下限, us
#define TempPWMHighMinAline               (u16)(PWMHighMinAline*TIM3_Fre/1000000.0)   // 最低油门校准下限, us
#define TempPWMHighMaxAline               (u16)(PWMHighMaxAline*TIM3_Fre/1000000.0)   // 最高油门校准下限, us
#define TempPWMINHighMinFilt              (u16)(PWMINHighMinFilt*TIM3_Fre/1000000.0)   // 最低油门校准下限, us
#define TempPWMINHighMaxFilt              (u16)(PWMINHighMaxFilt*TIM3_Fre/1000000.0)   // 最低油门校准下限, us
#define TempPWMINIdling                   (u16)(PWMIdling*TIM3_Fre/1000000.0)         // 怠速油门
#define TempPWMINStartUp                  (u16)(PWMINStartUp*TIM3_Fre/1000000.0)

#define TempDelayTime                     (u16)(DELAY_TIMEUS*TIM1_PSC/1000.0) // 续流屏蔽角度，单位° /
#define TempMaskTime                      (u16)(MASK_TIMEUS*TIM1_PSC/1000.0) // 续流屏蔽角度，单位° /
#define TempRampMaskTime                  (u16)(RampMaskTime*TIM1_PSC/1000.0) // 续流屏蔽角度，单位° //----------------------------------------------------------------------------------
/*Angle Control*/                                   
#define TEMPMASKANGLE                     (u16)(MASK_ANGLE*32767.0/60.0)          // 续流屏蔽角度，单位°
#define TEMPDELAYANGLE                    (u16)(DELAY_ANGLE*32767.0/60.0)         // 延迟换相角度，单位°
#define TEMPHALLADVANCEEANGLE             (s16)(HALLADVANCEEANGLE*32767.0/60.0)
//-----------------------------------------------------------------------------
//端子滤波时间 单位毫秒  小于10ms
#define KEY_FILTERNMS             (10)                          //单位ms %%
#define KEY_FILTERCOUNT           (KEY_FILTERNMS*(10))          //单位 -- %% 
#define MSCOUNTE                  (10)                          //单位 -- %%  

//-----------------------------------------------------------------------------
//速度计算
//Drv.speed.SpeedScaler = _IQ((60*(float)750000)/(6*(float)Ctl.Motor.PolePairs*Ctl.Motor.BaseSpeed)); 
#define SPEEDSCALER             (_IQ((60*(float)TIM1_PSC)/(6*(float)POLE_PAIR*BASE_SPEED)))
#define SPEEDSCALER1            ((60*(float)TIM1_PSC)/(6*(float)POLE_PAIR))
#define STB1SPEEDVALUE          ((u16)((float)SPEEDSCALER1/(float)STB1SPEED))
#define STB2SPEEDVALUE          ((u16)((float)SPEEDSCALER1/(float)STB2SPEED))
//-----------------------------------------------------------------------------
//ADC 电压采样
//Drv.AdcMeas.VdcMeasGain = (float)(RV_BUS_1+RV_BUS_2)/(float)RV_BUS_2;
//VGain = (float)(RV_BUS_1+RV_BUS_2)/(float)RV_BUS_2;
#define  V_GAIN                  (float)((float)(RV_BUS_1+RV_BUS_2)/(float)RV_BUS_2)
#define  VDCMEASEGAIN            (float)(5.0*(V_GAIN)/0x7FFF)

#define  MECASEOVERVOLTAGE        (OVERVOLTAGE/VDCMEASEGAIN)
#define  MECASEUNDERVOLTAGE       (UNDERVOLTAGE/VDCMEASEGAIN)
#define  MECASEOVREERVOLTAGE      (OVREERVOLTAGE/VDCMEASEGAIN) 
#define  MECASEUNREDERVOLTAGE     (UNREDERVOLTAGE/VDCMEASEGAIN)
//-----------------------------------------------------------------------------//电流采样
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