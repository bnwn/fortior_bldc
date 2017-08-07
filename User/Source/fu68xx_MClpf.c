
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
#include "fu68xx_MClpf.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/u8 xdata LPF_DONE = 0X7F ;
/* Private function prototypes -----------------------------------------------*/
uint16 MC_LPF(uint16 tXn1, uint16 tXn0, uint16 tK);
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : LPF
* Description    : µÍÍ¨ÂË²¨
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16 LPF(uint16 Xn1, uint16 Xn0, uint16 K)
{	
  LPF_K = K;
  LPF_X = Xn1;
  LPF_Y = Xn0;	
  SetBit(PL_CR, LPFSTA, 1);
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  return LPF_Y;
}

uint16 MC_LPF(uint16 tXn1, uint16 tXn0, uint16 tK)
{
  uint16 MC_LPF_Y;

  if(LPF_DONE == 0X7F)
  {
    LPF_DONE = 0XFF;               //Ã¦
    MC_LPF_Y = LPF(tXn1,tXn0,tK);
    LPF_DONE = 0x7F;               //¿ÕÏÐ
    return MC_LPF_Y;
  }
  else
  {
    ;//return tXn0;
  }
}