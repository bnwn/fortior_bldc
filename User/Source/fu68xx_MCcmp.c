
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
#include "fu68xx_MCcmp.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : CMP_Iint
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CMP_Config(void)
{
  /*-----------------------------------------------------------------------------------
  CMP Input Pin Mode
  0: GPIO Mode, P1.4--CMP0_IN+, P1.6--CMP1_IN+, P2.1--CMP2_IN+
  P1.5--CMP0_IN-, P1.7--CMP1_IN-, P2.2--CMP2_IN-
  1: BEMF Mode, 比较器正端连接到内部星型连接电阻U、V、W的BMEF采样点，
  比较器负端连接到内部星型连接电阻的虚拟中性点
  比较器负端与P1.5/P1.7/P2.2断开，这三个GPIO可做其他用途
  -----------------------------------------------------------------------------------*/	
  SetBit(P2_AN, P26, 1);
  SetBit(P2_AN, P27, 1);    // CMP3
  SetBit(CMP_CR1, BEMFREN, 0);
    /*-------------------------------------------------------------------------------------------------
  比较器迟滞电压选择
  000: 无迟滞   001: +-2.5mV   010: -5mV   011: +5mV
  100: +-5mV   101: -7.5mV   110: +7.5mV   111: +-7.5mV
  -------------------------------------------------------------------------------------------------*/
  SetBit(CMP_CR1, CMP3HYS2, 1);
  SetBit(CMP_CR1, CMP3HYS1, 1);
  SetBit(CMP_CR1, CMP3HYS0, 1);   // 比较器3无迟滞电压
  
  /*-----------------------------------------------------------------------------------
  比较器中断模式配置
  00: 不产生中断  01: 上升沿产生中断  10: 下降沿产生中断  11: 上升/下降沿产生中断
  ------------------------------------------------------------------------------------*/
  CMP_SR &= 0xF7;               // clear interrupt flag
  #if (EFAL == FO_CMP)
  SetBit(CMP_CR0, CMP3IM1, 0);
  SetBit(CMP_CR0, CMP3IM0, 1); 
  #else
  SetBit(CMP_CR0, CMP3IM1, 0);
  SetBit(CMP_CR0, CMP3IM0, 0);   
  #endif
  
  /*比较器使能-----------------------------------------------------------------------*/
  SetBit(CMP_CR2, CMP3EN, 0);
  CLR(CMP_SR, CMP3INTR);
  
  #if (POSITION_FB_MODE == SENSORLESS)
  SetBit(CMP_CR1, BEMFREN, 1);
  // CMP Input Pin Mode
  SetBit(P1_AN, P14, 1);
  SetBit(P1_AN, P15, 1);  // CMP0
  SetBit(P1_AN, P16, 1);
  SetBit(P1_AN, P17, 1);  // CMP1
  SetBit(P2_AN, P21, 1);
  SetBit(P2_AN, P22, 1);  // CMP2  
  /*-------------------------------------------------------------------------------------------------
  比较器迟滞电压选择
  000: 无迟滞   001: +-2.5mV   010: -5mV   011: +5mV
  100: +-5mV   101: -7.5mV   110: +7.5mV   111: +-7.5mV
  -------------------------------------------------------------------------------------------------*/
  //比较器迟滞电压选择
  SetBit(CMP_CR1, CMP0HYS2, 0);
  SetBit(CMP_CR1, CMP0HYS1, 0);
  SetBit(CMP_CR1, CMP0HYS0, 1);   // 比较器0无迟滞电压  
  
  /*比较器0~2输出采样使能------------------------------------------------------------*/
  #if(CMPSAME_EN)
  SetBit(CMP_CR2, CMPSAME, 1);    // enable CMP output filter 
  #else
  SetBit(CMP_CR2, CMPSAME, 0);    // enable CMP output filter   
  #endif
  /*比较器输出选择配置---------------------------------------------------------------*/
  SetBit(CMP_CR2, CMPSEL1, 0);    
  SetBit(CMP_CR2, CMPSEL0, 1);    // select CMP2 output
  SetBit(CMP_CR2, CMPOE, 1);      // enable CMP output
  SetBit(P0_OE, P07, 1);  
  
  //比较器中断模式配置
  SetBit(CMP_CR0, CMP2IM1, 0);
  SetBit(CMP_CR0, CMP2IM0, 0);
  SetBit(CMP_CR0, CMP1IM1, 0);
  SetBit(CMP_CR0, CMP1IM0, 0);
  SetBit(CMP_CR0, CMP0IM1, 0);
  SetBit(CMP_CR0, CMP0IM0, 0);
  
  SetBit(CMP_CR2, CMP2EN, 1);
  SetBit(CMP_CR2, CMP1EN, 1);
  SetBit(CMP_CR2, CMP0EN, 1);  
  #endif
} 
  
