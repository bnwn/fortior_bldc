
/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        : 警告：禁止修改,删除 结构体定义 否则会导致未知错误
********************************************************************************
/*******************************************************************************
* All Rights Reserved
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __CONSTANT_H_
#define __CONSTANT_H_

//------------------------------------------------------------------------
//默认电机旋转方向  
#define CW                  1              //单位-- %% 正转
#define CCW                 2              //单位-- %% 反转
// DIRECTION 设置参数为： CW CCW 0  当DIRECTION = 0时 如果Uc.flg.FR 没有赋值则不能启动 
#define DIRECTION           CW             //单位-- && 默认旋转方向
//------------------------------------------------------------------------
//功能选择层选择 会增加代码量 
#define SETVERSIONSEN     0                //Set_Versions  
#define FAILLOGEN         1                //故障信息记录          
#define FAILLAMPEN        1                //故障指示 LED闪烁  
#define FAILSTOREEN       0                //Flash 故障存储     

#define MOTORCIRCLECALEEN 0                //电机旋转圈数计算  Motor rotating ring number counting
#define LAMP_EN           (0)              //单位-- && 电动工具延时照明使能  //无操作延时控制
#define NOOPDELAYNMS      (10000)          //单位ms && NoOperationDelaynms

#define BEMFSETFR         (0)              //单位-- && 电调转向设定
#define BemfSetFRRomAddress  (16132)
//------------------------------------------------------------------------
//过载保护                              
#define  OVERLOAD_EN         (0)            //单位-  过载使能
#define  OVERLOAD0           (40.1)         //单位A  过流值
#define  OVERLOAD1           (42.2)         //单位A  过流值
#define  OVERLOAD2           (44.3)         //单位A  过流值
#define  OVERLOAD3           (46.4)         //单位A  过流值
  
#define  OL0NMS              (6000)         //单位ms 过流监测时间
#define  OL1NMS              (3000)         //单位ms 过流监测时间
#define  OL2NMS              (1000)         //单位ms 过流监测时间
#define  OL3NMS              (500)          //单位ms 过流监测时间
//------------------------------------------------------------------------
//空载判断
#define  NOLOAD_EN           (1)
#define  NOLOADCURRENT       (8.0)         //单位A 
#define  NOLOADNUM           (2)          //单位ms
  
//============================================================================
//速度给定曲线修正参数 ADC、PWMIN  ON/OFF 
//(X1,Y1) (X2,Y2) -->> (SPEED_REF_MAX,ADCSREFINMAX)  (SPEED_REF_MIN,ADCSREFINMIN) 
//A = (Y2,Y1)/(X2,X1)  B = Y2 - AX2                         
#define SPEED_REF_MIN        (_IQ(0.05))           //ADC和PWMIN输出 速度给定最小
#define SPEED_REF_MAX        (_IQ(1.0))           //ADC和PWMIN输出 速度给定最大
  
#define SREFCOUNT            (15)                 //滤波次数
#define ADCREFOFFVALUE       (_IQ(0.05))          //关机电平0.05*5 = 0.25V 
#define ADCREFONVALUE        (_IQ(0.1))           //开机电平0.1*5 = 0.5V
#define ADCSREFINMIN         (_IQ(0.1))           //ADC输入 最小
#define ADCSREFINMAX         (_IQ(0.95))           //ADC输入 最大

#define ADCAlineA            ((float)(SPEED_REF_MAX-SPEED_REF_MIN)/(float)(ADCSREFINMAX-ADCSREFINMIN))
#define ADCAlineB            (SPEED_REF_MAX - ADCSREFINMAX*ADCAlineA)
//PWMIN  电调滑板车 油门控制
#define PWMINALINE_EN        (1)                  // 油门校准使能
#define PWMIdling            (1040)               // 怠速油门
#define PWMINStartUp				 (1150)               // 正常启动油门
#define PWMHighMinDefault    (1000)               // 最低油门校准, us
#define PWMHighMaxDefault    (1900)               // 最高油门校准, us
#define PWMHighMinAline      (1200)               // 最低油门校准, us
#define PWMHighMaxAline      (1800)               // 最高油门校准, us
#define MotorBreakTime       (10)                 // 刹车油门时间 us
#define MotorOFFTimeErr      (10)                 // ONOFF时间偏差, us
#define MotorONTimeErr       (30)                 // ONOFF时间偏差, us
#define PWMINHighMinFilt     (400)                // 最低油门信号周期值, us
#define PWMINHighMaxFilt     (3000)               // 最高油门信号周期值, us

#if(PWMINSREF_EN)
  #define MOS_SELFINSPECTION  (0)                 //MOS自检测试只支持 fu68311Q QNF32
  #define BEEPSCAN_EN         (1)                 //电机鸣叫 提示音 取消电机提示音会同时取消 油门校准
  #define BEEP_VOL            (0.5)               //电机鸣叫声音 大小  volume
#endif
#endif
