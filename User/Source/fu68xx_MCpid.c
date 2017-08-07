
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
#include "fu68xx_MCpid.h"

/** @addtogroup FT68xx
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PIDREG3 idata pid_spd ;                       //速度环 
PIDREG3 idata pid_is ;                        //电流环
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Pid_Config(void);                        //pid模块配置
void Pid_IsInit(void);
void Pid_SpdInit(void);
s16  Pid_calc( PIDREG3 *v);                   //计算

void Pid_Config(void)
{
/*-----------------------------------------------------------------------------------
	PI数据格式
	Q = PIRANGE + 8(Q8~Q23数据格式)
  给寄存器赋值时要统一数据格式
-----------------------------------------------------------------------------------*/		
  SetBit(PL_CR, PIRANGE3, 0);
  SetBit(PL_CR, PIRANGE2, 1);
  SetBit(PL_CR, PIRANGE1, 1);
  SetBit(PL_CR, PIRANGE0, 1);				//PI截位Q=PIRANGE+8，即PI数据格式							

  PI_KP = 0;												//寄存器数据类型：int16 Q12格式，PI_KP=Kp*2^12，
  PI_KI = 0;												//寄存器数据类型：int16 Q12格式，PI_KI=Kp*2^12
  PI_EK = 0;												
  PI_UK = 0;												//寄存器数据类型：int16
  PI_UKMAX = 0;											//寄存器数据类型：int16
  PI_UKMIN = 0;											//寄存器数据类型：int16
}


/*******************************************************************************
* Function Name  : PI_Init
* Description    : 
* Input          : None
* Output         : 
* Return         : None
*******************************************************************************/
void Pid_SpdInit(void)
{
  pid_spd.Ref = 0;
  pid_spd.Fdb = 0;
  
//  pid_spd.Kp = SPEED_PTERM; //Q15格式
//  pid_spd.Ki = SPEED_ITERM; //Q15格式
  pid_spd.Err = 0;
  pid_spd.Err_Last1 = 0;
  pid_spd.Err_Err = 0;
  pid_spd.Out = 0;

  pid_spd.OutMax = SPEED_OUTMAX;
  pid_spd.OutMin = SPEED_OUTMIN;    
}

/*******************************************************************************
* Function Name  : PI_Init
* Description    : 
* Input          : None
* Output         : 
* Return         : None
*******************************************************************************/
void Pid_IsInit(void)
{
  pid_is.Ref = 0;
  pid_is.Fdb = 0;
//  pid_is.Kp = CURRENT_PTERM; //Q15格式
//  pid_is.Ki = CURRENT_ITERM; //Q15格式
  pid_is.Err = 0;
  pid_is.Err_Last1 = 0;
  pid_is.Err_Err = 0;
  pid_is.Out = 0;

  pid_is.OutMax = CURRENT_OUTMAX ;
  pid_is.OutMin = CURRENT_OUTMIN;
}

/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : None
* Output         : 
* Return         : None
*******************************************************************************/
s16 Pid_calc(PIDREG3 *v)   
{
//  /*指针类型数据判断执行时间2.5us*/
  PI_KP = v->Kp;									//寄存器数据类型：int16 Q12格式，PI_KP=Kp*2^12，
  PI_KI = v->Ki;									//寄存器数据类型：int16 Q12格式，PI_KI=Kp*2^12
  PI_EK = v->Err;												
  PI_UK = v->Out;									//寄存器数据类型：int16
  PI_UKMAX = v->OutMax;						//寄存器数据类型：int16
  PI_UKMIN = v->OutMin;						//寄存器数据类型：int16

  /*赋值运算时间3.2us*/	
  v->Err = v->Ref - v->Fdb;								//计算PID当前偏差  

  /*PI硬核运算时间1.8us*/
  PI_EK = v->Err;										//PI输入
  PI_UK = v->Out;							  		//寄存器数据类型：int16
  SetBit(PL_CR,PISTA,1);
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();

  v->Out = PI_UK;										//PI输出
  return v->Out;
}