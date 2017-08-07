
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
#include "MC_MotorCotrol_layer.h"  
#include "MC_key.h"


/** @addtogroup FT68xx
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define X0_EN                  0         
#define X1_EN                  1
#define X2_EN                  0
#define X3_EN                  0

#define X3_GPIO_PIN           GP03
#define X2_GPIO_PIN           GP02
#define X1_GPIO_PIN           GP01
#define X0_GPIO_PIN           GP00
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
key_TypeDef xdata X0;
key_TypeDef xdata X1;
key_TypeDef xdata X2;
key_TypeDef xdata X3;

u8  xdata u8KeyForbid;            //按键禁止标志

/* Private function prototypes -----------------------------------------------*/
void Key_Config(void);
void Key_init(void);
void Key_Filtrate(void);
/* Private functions ---------------------------------------------------------*/

void Key_Config(void)
{
//端子设置 X1设置输入
  #if(X0_EN)
  SetBit(P0_OE,P00,0); //输入使能
  SetBit(P0_PU,P00,1); //上拉电阻
  #endif
  #if(X1_EN)
  SetBit(P0_OE,P01,0); //输入使能
  SetBit(P0_PU,P01,1); //上拉电阻
  #endif
  #if(X2_EN)
  SetBit(P0_OE,P02,0); //输入使能
  SetBit(P0_PU,P02,1); //上拉电阻
  #endif
  #if(X3_EN)
  SetBit(P0_OE,P03,0); //输入使能
  SetBit(P0_PU,P03,1); //上拉电阻
  #endif
}
void Key_init(void)
{
  X0.XCount = 0;
  X0.Xflg = FALSE;
  X0.Kflg = FALSE;
  X0.KNum = FALSE;

  X1.XCount = 0;
  X1.Xflg = FALSE;
  X1.Kflg = FALSE;
  X1.KNum = FALSE;

  X2.XCount = 0;
  X2.Xflg = FALSE;
  X2.Kflg = FALSE;
  X2.KNum = FALSE;
  
  X3.XCount = 0;
  X3.Xflg = FALSE;
  X3.Kflg = FALSE;
  X3.KNum = FALSE;
}
/*******************************************************************************
* Function Name  : Key_Filtrate
* Description    : 
* Input          : None
* Output         : X1.Kflg  按键按下标志（脉冲有效）    X1.Xflg 端子按下标志（电平有效）
* Return         : None
*******************************************************************************/

void Key_Filtrate(void)
{
  //if((Ctl.State != MOTOR_NORMAL)&&(u8KeyForbid != 0X7F))    //X1 X2 在停机下有效
  {
    //X0
    #if(X0_EN)
    if(X0_GPIO_PIN)  
    {
      X0.XCount++;
      if(X0.KNum == TRUE)            //如果按键滤波ok，等待按键释放
      {
        X0.Kflg = TRUE;              //按键按下并释放
      }
    }
    else
    {
      X0.XCount--;                   //按键按下计时
    }

    if(X0.XCount >= KEY_FILTERCOUNT)
    {
      X0.Xflg = FALSE;               //端子
      
      X0.XCount = KEY_FILTERCOUNT;
    }
    else if(X0.XCount <= -KEY_FILTERCOUNT) 
    {
      X0.Xflg = TRUE;                //端子按下
      X0.KNum = TRUE;                //按键
      
      X0.XCount = -KEY_FILTERCOUNT;
    }
  #endif

  #if(X1_EN)
    //X1
    if(X1_GPIO_PIN)  
    {
      X1.XCount++;
      if(X1.KNum == TRUE)            //如果按键滤波ok，等待按键释放
      {
        X1.Kflg = TRUE;              //按键按下并释放
      }
    }
    else
    {
      X1.XCount--;                   //按键按下计时
    }

    if(X1.XCount > KEY_FILTERCOUNT)
    {
      X1.Xflg = FALSE;               //端子
      
      X1.XCount = KEY_FILTERCOUNT;
    }
    else if(X1.XCount < -KEY_FILTERCOUNT) 
    {      X1.Xflg = TRUE;                //端子按下
      X1.KNum = TRUE;                //按键
      
      X1.XCount = -KEY_FILTERCOUNT;
    }
  #endif

  #if(X2_EN)
    //X2 
    if(X2_GPIO_PIN)  
    {
      X2.XCount++;
      if(X2.KNum == TRUE)            //如果按键滤波ok，等待按键释放
      {
        X2.Kflg = TRUE;              //按键按下并释放
      }
    }
    else
    {
      X2.XCount--;                   //按键按下计时
    }
    
    if(X2.XCount > KEY_FILTERCOUNT)
    {
      X2.Xflg = FALSE;               //端子
      
      X2.XCount = KEY_FILTERCOUNT;
    }
    else if(X2.XCount < -KEY_FILTERCOUNT) 
    {
      X2.Xflg = TRUE;                //端子按下
      X2.KNum = TRUE;                //按键
      
      X2.XCount = -KEY_FILTERCOUNT;
    } 
  #endif
  }
  
  //X3 
  #if(X3_EN)
  if(X3_GPIO_PIN)  
  {
    X3.XCount++;
    if(X3.KNum == TRUE)            //如果按键滤波ok，等待按键释放
    {
      X3.Kflg = TRUE;              //按键按下并释放
    }
  }
  else
  {
    X3.XCount--;                   //按键按下计时
  }

  if(X3.XCount > KEY_FILTERCOUNT)
  {
    X3.Xflg = FALSE;               //端子
    
    X3.XCount = KEY_FILTERCOUNT;
  }
  else if(X3.XCount < -KEY_FILTERCOUNT) 
  {
    X3.Xflg = TRUE;                //端子按下
    X3.KNum = TRUE;                //按键
    
    X3.XCount = -KEY_FILTERCOUNT;
  }    
  #endif  
} 
