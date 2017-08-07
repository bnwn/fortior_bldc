
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
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

int main(void)
{ 
  /*System Init*/
  SystemInit();

  /*Software Init*/
  SoftwareInit();
  
  /*Module Init*/
  MCL_ModuleInit();

  Ctl.State = MOTOR_INIT;
  //ÆôÍ£¿ØÖÆ     ²ÎÊý: TRUE OR FALSE      
  Uc.flg.START = FALSE; 

  while(1)
  {
    UI();
    MCL_MotorC();
  }
}
