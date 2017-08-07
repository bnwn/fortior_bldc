
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
#include "fu68xx_MCtime.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : TIM1_Config
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_Config(void)
{
  u8 temp;
/**********************************************************************	
噪声滤波使能及模式选择	
00;		4-machine cycle noise,4MHz
01;		8-machine cycle noise,2MHz
10		16-machine cycle noise,1MHz	
11;		32-machine cycle noise,0.5MHz		
**********************************************************************/

  SetBit(TIM1_CR2,INM00,1); 
  SetBit(TIM1_CR2,INM01,1); 
  SetBit(TIM1_CR2,INM10,1); 
  SetBit(TIM1_CR2,INM11,1); 
  SetBit(TIM1_CR2,INM20,1); 
  SetBit(TIM1_CR2,INM21,1); 
  
  SetBit(TIM1_CR0,INC0,1);            /*0:禁止TI0噪声滤波,1:使能TI0噪声滤波*/	
  SetBit(TIM1_CR0,INC1,1);            /*0:禁止TI1噪声滤波,1:使能TI1噪声滤波*/	
  SetBit(TIM1_CR0,INC2,1);            /*0:禁止TI2噪声滤波,1:使能TI2噪声滤波*/	

/********************************************************************
输入信号选择
0: TI0--COMP0_OUT    TI1--COMP1_OUT    TI2--COMP2_OUT
1: TI0--P1.4_IN      TI1--P1.6_IN      TI2--P2.1_IN
********************************************************************/
  #if (POSITION_FB_MODE == HALLSENSOR)
    #if (HallIC == HallSensor)
    SetBit(TIM1_CR2,TIS,0);   //此软件没有验证 20160222
    #elif (HallIC == HallIC)  
    SetBit(TIM1_CR2,TIS,1);
    #endif
  SetBit(TIM1_CR2,TIS,1);
  #elif (POSITION_FB_MODE == SENSORLESS)
  SetBit(TIM1_CR2,TIS,0);
  #endif
/********************************************************************
输入极性检测
00:不检测边沿		01:检测上升沿		10:检测下降沿		11:检测上升/下降沿
********************************************************************/
  SetBit(TIM1_CR0,CPE1,1);
  SetBit(TIM1_CR0,CPE0,1);

/********************************************************************
边沿检测使能
********************************************************************/
  SetBit(TIM1_CR0, IEE2, 1);          // 0:禁止TI2边沿检测,1:使能TI2边沿检测
  SetBit(TIM1_CR0, IEE1, 1);          // 0:禁止TI1边沿检测,1:使能TI1边沿检测
  SetBit(TIM1_CR0, IEE0, 1);          // 0:禁止TI0边沿检测,1:使能TI0边沿检测
  SetBit(TIM1_CR1, CMPE, 0);          // 0:边沿检测比较,   1:位置检测比较
/*CPD值设置------------------------------------------------------------------------*/
//  SetBit(TIM1_CR1, CPD2, 0);
//  SetBit(TIM1_CR1, CPD2, 0);
//  SetBit(TIM1_CR1, CPD2, 0);
/*RDA值设置------------------------------------------------------------------------*/
//  SetBit(TIM1_DRH, RDA2, 0);
//  SetBit(TIM1_DRH, RDA1, 0);
//  SetBit(TIM1_DRH, RDA0, 0);   
/********************************************************************
数据更新模式设置
000:软件写TIM1_BDBR更新TIM1_BDR
001:PTimer下溢触发TIM1_BDBR更新TIM1_BDR
010:位置检测输入触发TIM1_BDBR更新TIM1_BDR
011:位置检测输入启动PTimer，PTimer下溢更新TIM1_BDR
100:位置检测输入或者PTimer下溢更新TIM1_BDR
101:位置检测比较单次有效输入或PTimer单次下溢更新TIM1_BDR
110:位置检测比较单次有效输入触发TIM1_BDBR更新TIM1_BDR
111:位置检测比较单次有效输入启动PTimer，PTimer下溢更新TIM1_DBR
********************************************************************/
  SetBit(TIM1_CR3,OPS2,0);
  SetBit(TIM1_CR3,OPS1,0);
  SetBit(TIM1_CR3,OPS0,0);           //软件写DBR触发换相
/********************************************************************
PPG同步方式设置
WTS = 00: 无同步，立即更新输出   
WTS = 01: 上升沿同步输出   
WTS = 10: 下降沿同步输出  
WTS = 11: 上升/下降沿同步输出
********************************************************************/
  SetBit(TIM1_CR1,WTS1,0);            //无同步，立即更新输出
  SetBit(TIM1_CR1,WTS0,0);

/********************************************************************
Basic Timer & Preload Timer设置
********************************************************************/
  SetBit(TIM1_CR3,BCEN,0);            //停止16bit定时器

  #if (TIM1_PSC == TIM1PSC24M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,0);
  SetBit(TIM1_CR3,T1PSC1,0);
  SetBit(TIM1_CR3,T1PSC0,0);          //定时器分频 4 ，计数时钟为24MHz
  #elif (TIM1_PSC == TIM1PSC12M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,0);
  SetBit(TIM1_CR3,T1PSC1,0);
  SetBit(TIM1_CR3,T1PSC0,1);          //定时器分频 4 ，计数时钟为24MHz
  #elif (TIM1_PSC == TIM1PSC6M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,0);
  SetBit(TIM1_CR3,T1PSC1,1);
  SetBit(TIM1_CR3,T1PSC0,0);          //定时器分频 4 ，计数时钟为24MHz
  #elif (TIM1_PSC == TIM1PSC3M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,0);
  SetBit(TIM1_CR3,T1PSC1,1);
  SetBit(TIM1_CR3,T1PSC0,1);          //定时器分频 8 ，计数时钟为24MHz
  #elif (TIM1_PSC == TIM1PSC1_5M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,1);
  SetBit(TIM1_CR3,T1PSC1,0);
  SetBit(TIM1_CR3,T1PSC0,0);          //定时器分频 16 ，计数时钟为24MHz
  #elif (TIM1_PSC == TIM1PSC750K)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,1);
  SetBit(TIM1_CR3,T1PSC1,0);
  SetBit(TIM1_CR3,T1PSC0,1);          //定时器分频 32 ，计数时钟为24MHz
  #elif (TIM1_PSC == TIM1PSC375K)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,1);
  SetBit(TIM1_CR3,T1PSC1,1);
  SetBit(TIM1_CR3,T1PSC0,0);          //定时器分频 64 ，计数时钟为24MHz
  #elif (TIM1_PSC == TIM1PSC187_5K)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,1);
  SetBit(TIM1_CR3,T1PSC1,1);
  SetBit(TIM1_CR3,T1PSC0,1);          //定时器分频 128 ，计数时钟为24MHz
  #endif

  SetBit(TIM1_CR2,BRS,1);             //位置检测触发定时器复位 BSR 0写入时序复位 1位置检测复位
  TIM1_BARR = 0xFFFF;                 //
  TIM1_BCNTR = 1;         
  SetBit(TIM1_CR3,BCEN,1);            //启动16bit定时器

  SetBit(TIM1_CR1,RCEN,0);            //停止Preload定时器
  SetBit(TIM1_CR1,ROPM,1);            //使能OPM模式   单次模式
  TIM1_RARR = 0xffff;
  TIM1_RCNTR = 0xffff;

  /********************************************************************
                                               中断使能
  ********************************************************************/
  TIM1_SR = 0x00;                    //中断标志清零
  SetBit(TIM1_IER,CPIE,0);            //禁止比较中断
  SetBit(TIM1_IER,PDIE,1);            //使能位置检测中断 
  SetBit(TIM1_IER,WTIE,0);            //使能写入时序中断 	
  SetBit(TIM1_IER,RUIE,0);            //禁止Preload定时器下溢中断
  SetBit(TIM1_IER,BOIE,1);            //使能16bit定时上溢中断
   
  TIM1_DTR  = PWM_DEADTIMENUS*1000.0/41.67-1;
  if(TIM1_DTR < 5)
  {
    TIM1_DTR = 5;
  }
  else if(TIM1_DTR > 500)
  {
    TIM1_DTR = 500;
  }
    
 // DeadTime = (TIM1_DTR+1)/cpuclk,
/********************************************************************
使能输出
OCM = 00：强制输出低电平
OCM = 01：输出同相PPG（TIM2输出）
OCM = 10：输出反相PPG（TIM2输出）
OCM = 11：强制输出高电平
********************************************************************/ 

  PWMOUT_OFF;                          //
  MOE = 1;                             //使能主输出
}

/*******************************************************************************
* Function Name  : TIM2_Config
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_Config(void)
{
  /**************************************************************
  Timer 2 时钟分频设置
  000:cpuclk			001:cpuclk/2^1	010:cpuclk/2^2	011:cpuclk/2^3
  100:cpuclk/2^4   	101:cpuclk/2^5	110:cpuclk/2^6	111:cpuclk/2^7
  **************************************************************/
  SetBit(TIM2_CR0,T2PSC2,0);
  SetBit(TIM2_CR0,T2PSC1,0);
  SetBit(TIM2_CR0,T2PSC0,0);

  SetBit(TIM2_CR0,T2MODE,1);          //工作模式选择：1--输出模式，0--输入模式
  SetBit(TIM2_CR0,T2CES,0);           /*输入Counter模式时有效沿选择：1--上升沿，0--下降沿*/
  SetBit(TIM2_CR0,T2CTM,0);           /*输入模式选择：1--Counter,0--Timer*/	

  /*********************输出比较模式：******************************
  00--强制0 ，                
  01--强制1
  10-- TIMx_CNTR<=TIMx_DR为0 TIMx_CNTR>TIMx_DR为1
  11-- TIMx_CNTR<=TIMx_DR为1 TIMx_CNTR>TIMx_DR为0
  *****************************************************************/
  SetBit(TIM2_CR0,T2OCM1,1);
  SetBit(TIM2_CR0,T2OCM0,1);

  /*输出模式：比较匹配中断， 输入Timer模式：PWM周期检测中断，输入Counter模式：输入PWM计数匹配中断 */  
  SetBit(TIM2_CR1,T2IDE,1);			  //匹配中断使能

  /*输出模式：计数器上溢中断，输入Timer模式：计数器上溢中断，输入Counter模式：基本计数器上溢中断 */  
  SetBit(TIM2_CR1,T2IFE,1);			  //上溢中断使能

  SetBit(TIM2_CR1,T2FE,0);			  //输入噪声滤波使能，4CPU CLK		
  SetBit(TIM2_CR1,T2OPM,0);				/*禁止单次计数*/	

  TIM2_DR = 300;                    //PWM载波占空比
  TIM2_ARR = PWMARR;                //载波频率 = 24M/1500 =16K
  
  //		SetBit(P1_OE,P10,1);            //使能P1.0数字输出
  //		SetBit(PH_SEL,T2SEL,1);				  //使能P1.0作为Timer2引脚输出	

  SetBit(TIM2_CR1,T2CEN,1);				  /*启动计数*/	
}

/*******************************************************************************
* Function Name  : TIM3_Config
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_Config(void)
{
  SetBit(TIM3_CR1, T3CEN, 0);                          // 停止计数*/

  /*-------------------------------------------------------------------------------------------------
  时钟分频设置(T5PSC)  750k
  000:cpuclk			001:cpuclk/2^1	010:cpuclk/2^2	011:cpuclk/2^3
  100:cpuclk/2^4	101:cpuclk/2^5	110:cpuclk/2^6	111:cpuclk/2^7	
  -------------------------------------------------------------------------------------------------*/
  SetBit(TIM3_CR0, T3PSC2, 1);
  SetBit(TIM3_CR0, T3PSC1, 0);
  SetBit(TIM3_CR0, T3PSC0, 1);

  /*-------------------------------------------------------------------------------------------------
  比较输出模式
  OCM = 00：强制输出低电平
  OCM = 01：强制输出高电平
  OCM = 10：PWM模式1，CNTR<DR输出低电平，CNTR>DR输出高电平
  OCM = 11：PWM模式2，CNTR<DR输出高电平，CNTR>DR输出低电平
  -------------------------------------------------------------------------------------------------*/
  SetBit(TIM3_CR0, T3MODE, 1);                            // 选择输出模式				
  SetBit(TIM3_CR0, T3OCM1, 1);
  SetBit(TIM3_CR0, T3OCM0, 0);                             // 输出比较模式2,0-->1
  SetBit(TIM3_CR1, T3FE, 1);                               // 使能输入滤波

  CLRFlag_T3IR;
  CLRFlag_T3IP;
  CLRFlag_T3IF;
  SetBit(TIM3_CR1, T3IDE, 0);				                       // 禁止输出比较/PWM周期检测中断
  SetBit(TIM3_CR1, T3IFE, 0);				                       // 使能溢出中断	

  #if (PWMINONOFF_EN)
  {
    TIM3_ARR = 1;							                               // TIM3 Period = 100us				
    TIM3_DR = 0;
    TIM3_CNTR = 1;
    SetBit(TIM3_CR0, T3MODE, 0);			                       // 选择输入模式	
    SetBit(TIM3_CR0, T3CTM, 0);	                             // 输入定时器模式
    SetBit(P1_OE, P11, 0);                                   // config P21 as input
    SetBit(P1_PU, P11, 1);                                   // enable P21 pull up	
    SetBit(P1_AN, P11, 0);                                   // diasable P21analog function		
    SetBit(TIM3_CR1, T3IDE, 1);				                       // 禁止输出比较/PWM周期检测中断
    SetBit(PH_SEL, T3SEL, 1);					                       // GP11选择Capture Timer输入/输出(for test)
    SetBit(TIM3_CR1, T3IFE, 1);				                       // 使能溢出中断	
  }
  #endif

  #if (IRONOFF_EN)
  {
    /*PWMPin Config*/
    SetBit(P1_OE, P11, 0);                                   // config P21 as input
    SetBit(P1_PU, P11, 1);                                   // enable P21 pull up	
    SetBit(P1_AN, P11, 0);                                   // diasable P21analog function
    CLR(P1IF, P11);					                                 // clear P21 interrupt flag
    SetBit(P1IE, P11, 1);		                                 // config P21 as the source of EXTI1		
      
    TIM3_ARR = 60000;							                               // TIM3 Period = 100us				
    TIM3_DR = TIM3_ARR >> 1;;	
    TIM3_CNTR = 1;
    SetBit(TIM3_CR1, T3IFE, 1);				                       // 使能溢出中断	
    
  }
  #endif

  SetBit(TIM3_CR1, T3CEN, 1);				                       // 启动计数	
}
/*******************************************************************************
* Function Name  : TIM4_Config 
* Description    : Main program. P0.1     做100us定时器用
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_Config(void)
{
  //SetBit(PH_SEL, T4SEL, 1);       //GP01选择Capture Timer输入/输出(for test)
  SetBit(TIM4_CR1, T4CEN, 0);         //停止计数*/

  /*-----------------------------------------------------------------------------------
  时钟分频设置(T5PSC)
  000:cpuclk			001:cpuclk/2^1	010:cpuclk/2^2	011:cpuclk/2^3
  100:cpuclk/2^4	101:cpuclk/2^5	110:cpuclk/2^6	111:cpuclk/2^7	
  -----------------------------------------------------------------------------------*/			
  SetBit(TIM4_CR0, T4PSC2, 0);
  SetBit(TIM4_CR0, T4PSC1, 0);
  SetBit(TIM4_CR0, T4PSC0, 0);

  /*-----------------------------------------------------------------------------------
  比较输出模式
  OCM = 00：强制输出低电平
  OCM = 01：强制输出高电平
  OCM = 10：PWM模式1，CNTR<DR输出低电平，CNTR>DR输出高电平
  OCM = 11：PWM模式2，CNTR<DR输出高电平，CNTR>DR输出低电平
  -----------------------------------------------------------------------------------*/		
  SetBit(TIM4_CR0, T4MODE, 1);      //选择输出模式				
  SetBit(TIM4_CR0, T4OCM1, 1);
  SetBit(TIM4_CR0, T4OCM0, 0);      //输出比较模式2,0-->1

  CLR(TIM4_CR1, T4IR);
  CLR(TIM4_CR1, T4IP);
  CLR(TIM4_CR1, T4IF);
  SetBit(TIM4_CR1, T4IDE, 0);       //禁止输出比较/下降沿检测中断和上升沿检测中断									
  SetBit(TIM4_CR1, T4IFE, 1);       //使能溢出中断	

  TIM4_ARR = 2400;                  // TIM4 Period = 100us				
  TIM4_DR = TIM4_ARR >> 1; 
  TIM4_CNTR = 1;

  SetBit(TIM4_CR1, T4CEN, 1);       //启动计数	

}