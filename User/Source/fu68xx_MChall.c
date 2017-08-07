
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
#include "fu68xx_MChall.h"
#include "MC_MotorCotrol_layer.h" 
#include "MC_MotorDriver_layer.h"  

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 uc8 HALL2SECTIONCW[8]   = {0x7F,2,4,3,6,1,5,0xFF};
 uc8 HALL2SECTIONCCW[8]  = {0X7F,5,1,6,3,4,2,0xFF}; 
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Hall_Init      外部中断配置，hall使用tim1作为输入
* Description    : P14 P16 P21
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Hall_Init(void)
{
  #if(HALLPTDPE)
  SetBit(P1_PU, P14, 1);  // enable P14 pull up	
  SetBit(P1_PU, P16, 1);  // enable P16 pull up	
  SetBit(P2_PU, P21, 1);  // enable P21 pull up	
  #else
  SetBit(P1_PU, P14, 0);  // enable P14 pull up	
  SetBit(P1_PU, P16, 0);  // enable P16 pull up	
  SetBit(P2_PU, P21, 0);  // enable P21 pull up		
  #endif
}

/*******************************************************************************
* Function Name  : Hall_IRQHandler
* Description    : P14 P16 P21
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 Hall_IRQHandler(void)
{
  uint8 HallStatus = 0;
  
  if(HC == 1)
  {
    HallStatus += 4;
  }
  #if (HALL_SENSORS_PLACEMENT == DEGREES_60)
  if(HB == 0)
  {
    HallStatus += 2;
  }
  #elif (HALL_SENSORS_PLACEMENT == DEGREES_120)
  if(HB == 1)
  {
    HallStatus += 2;
  }
  #endif
  if(HA == 1)
  {
    HallStatus += 1;
  }
  //HALL状态
  //转子扇区
  if (Ctl.direction == CW)
  {
    Drv.Hall.Section = HALL2SECTIONCW[HallStatus];   
  }
  else if (Ctl.direction == CCW)
  {
    Drv.Hall.Section = HALL2SECTIONCCW[HallStatus];
  }  
  Ctl.Step = Drv.Hall.Section;
  return HallStatus;
}
