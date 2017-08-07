
#include <FU68xx.h>
#include "sys_conf.h"

void fu68xx_xram_erase(void);
void Driver_Init(void);
void SystemInit(void);

void SystemInit(void)
{
//-----------------------------------------
//Xram 清零
  fu68xx_xram_erase();

//-----------------------------------------
//驱动模式 
  Driver_Init();
/*-----------------------------------------------------------------------------------
  5、ADC参考电压配置
  6、运放基准电压配置
-----------------------------------------------------------------------------------*/
  VREFConfig(VREF5_0, Enable);								// ADC参考电压配置
  VHALFConfig(VREF_Half, Enable);							// 运放基准电压配置
  
  /*---------------------------------------------------------------------------------
  MOE Protect Config
  1、硬件保护使能，触发硬件保护后硬件关闭驱动输出MOE=0，同时产生硬件保护中断
  2、选择硬件保护触发信号源，
  1：外部中断0  
  0：比较器3中断。
  3、硬件保护触发信号滤波配置。
   00-4cpu clock    01-8cpu clock    10-16cpu clock    11-24cpu clock 
   ----------------------------------------------------------------------------------*/
  #if(HARD_OC_EN)
  SetBit(EVT_FILT, MCLREN, 1);                // 使能硬件保护
  #else
  SetBit(EVT_FILT, MCLREN, 0);                // 失能硬件保护
  #endif

  #if (EFAL == FO_CMP)
  //比较器中配置
  SetBit(EVT_FILT, EFSRC, 0);                 // 硬件保护触发信号为CMP3输出
  #else (EFAL == FO_INT)
  IT01 = 0;                                  //
  IT00 = 1;                                  //下降沿触发
  
  EX0 = 0;                                   //终端使能

  SetBit(EVT_FILT, EFSRC, 1);                 // 硬件保护触发信号为int0输出
  #endif
  SetBit(EVT_FILT, EFEN, 1);                  // 使能硬件保护触发信号滤波
  SetBit(EVT_FILT, EFDIV1, 0);
  SetBit(EVT_FILT, EFDIV0, 0);                // 硬件触发信号滤波宽度为24cpuclock
}


/*******************************************************************************
* Function Name  : fu68xx_xram_erase
* Description    : xram 清零模块
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void fu68xx_xram_erase(void)
{
  unsigned char xdata *port  ;
  
  port = 0;
  while(port<=0XFFF)
  {
    *port  = 0 ;
    port++;
  }
}

/*******************************************************************************
* Function Name  : Driver_Init
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Driver_Init(void)
{
  u32 PRDRVCnt;

  /*-------------------------------------------------------------------------------------------------
  DRV_CTL：PWM来源选择    
  OCS1 = 0, OCS1 = X: TIM0 PWM
  OCS1 = 1, OCS1 = 0: TIM1 PWM
  OCS1 = 1, OCS1 = 1: FOC 6 PWM
  -------------------------------------------------------------------------------------------------*/
  /*TIM1 6 PWM output*/
  SetBit(DRV_CTL, OCS1, 0);                     // TIM1 6 PWM output
  SetBit(DRV_CTL, OCS0, 1);

  SetBit(DRV_CTL, PRDRVEN, 1);                 //Predriver使能位   
  for(PRDRVCnt=0;PRDRVCnt<24000;PRDRVCnt++);   //vina 
  
  SetBit(DRV_CTL, DRVOE, 1);                   // gata driver使能位

  /*-------------------------------------------------------------------------------------------------
  空闲电平设置
  -------------------------------------------------------------------------------------------------*/ 
  OISWL = 0;                      // OC5空闲电平设置
  OISWH = 0;                      // OC4空闲电平设置
  OISVL = 0;                      // OC3空闲电平设置
  OISVH = 0;                      // OC2空闲电平设置
  OISUL = 0;                      // OC1空闲电平设置
  OISUH = 0;                      // OC0空闲电平设置
}