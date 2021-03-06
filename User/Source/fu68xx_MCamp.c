
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
#include "fu68xx_MCamp.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void AMP_Config(void)
{
  /*AMP管脚配置----------------------------------------------------------------------*/
  SetBit(P2_AN, P27, 1);
  SetBit(P3_AN, P30, 1);
  SetBit(P3_AN, P31, 1);      // AMP0

  //SetBit(P1_AN, P16, 1);
  //SetBit(P1_AN, P17, 1);
  //SetBit(P2_AN, P20, 1);    // AMP1

  //SetBit(P2_AN, P21, 1);
  //SetBit(P2_AN, P22, 1);
  //SetBit(P2_AN, P23, 1);    // AMP2

  /*运放使能-----------------------------------------------------------------------*/
  SetBit(AMP_CR, AMP0EN, 1);  
  //SetBit(AMP_CR, AMP1EN, 1);
  //SetBit(AMP_CR, AMP2EN, 1);
}