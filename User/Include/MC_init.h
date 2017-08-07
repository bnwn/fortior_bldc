
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_INIT_H
#define __MC_INIT_H

/* Includes ------------------------------------------------------------------*/
#include "fu68xx_MCDevice.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported define --------------------------------------------------------*/

//端口定义 START F/R FO FG PWMIN SREF LED UART SPI  HALL
//------------------------------------------------------------------------------
//FO     故障输入   IPM保护信号，禁止修改 
#define FO              GP00         //作为 FO信号时，禁止占用
#define FO_PIN          P00
#define FO_GPIO_PORT    P0_OE

//------------------------------------------------------------------------------
//FG     FG输出 
#define FG              GP36
#define FG_PIN          P36 
#define FG_GPIO_PORT    P3_OE
#define FG_ON           {FG = 0;}
#define FG_OFF          {FG = 1;}
#define FG_ONOFF        {FG = ~FG;}

//------------------------------------------------------------------------------
//SPI     MOSI输出 
#define NSS              GP04
#define NSS_PIN          P04 
#define NSS_GPIO_PORT    P0_OE
#define NSS_ON           {NSS = 0;}
#define NSS_OFF          {NSS = 1;}
#define NSS_ONOFF        {NSS = ~NSS;}

#define MOSI              GP37
#define MOSI_PIN          P37 
#define MOSI_GPIO_PORT    P3_OE
#define MOSI_ON           {MOSI = 0;}
#define MOSI_OFF          {MOSI = 1;}
#define MOSI_ONOFF        {MOSI = ~MOSI;}

#define MISO              GP06
#define MISO_PIN          P06 
#define MISO_GPIO_PORT    P0_OE
#define MISO_ON           {MISO = 0;}
#define MISO_OFF          {MISO = 1;}
#define MISO_ONOFF        {MISO = ~MISO;}

#define SCLK              GP07
#define SCLK_PIN          P07 
#define SCLK_GPIO_PORT    P0_OE
#define SCLK_ON           {SCLK = 0;}
#define SCLK_OFF          {SCLK = 1;}
#define SCLK_ONOFF        {SCLK = ~SCLK;}
//------------------------------------------------------------------------------
//PDELAY     power dealy 输出 
#define PDELAY           GP36
#define PDELAY_PIN       P36 
#define PDELAY_GPIO_PORT P3_OE
#define PDELAY_ON       {PDELAY = 1;}
#define PDELAY_OFF      {PDELAY = 0;}
#define PDELAY_ONOFF    {PDELAY = ~PDELAY;}
//------------------------------------------------------------------------------
//FAULT  故障输出 
#define FAULT              GP20
#define FAULT_PIN          P20
#define FAULT_GPIO_PORT    P2_OE

#define FAULT_ON           {FAULT = 0;}
#define FAULT_OFF          {FAULT = 1;}
#define FAULT_ONOFF        {FAULT = ~FAULT;}

//------------------------------------------------------------------------------
//FD6536  使能
#define FD6536           GP36
#define FD6536_PIN       P36 
#define FD6536_GPIO_PORT P3_OE

#define FD6536_EN        {FD6536 = 0;}
#define FD6536_DIS       {FD6536 = 1;}
//------------------------------------------------------------------------------
//PWMIN  调速输入
#define PWMIN              GP11
#define PWMIN_PIN          P11
#define PWMIN_GPIO_PORT    P1_OE

#define PWMIN_ON           {PWMIN = 0;}
#define PWMIN_OFF          {PWMIN = 1;}
#define PWMIN_ONOFF        {PWMIN = ~PWMIN;}
//------------------------------------------------------------------------------
//SREF   调速输入

//------------------------------------------------------------------------------
//LED    显示

#define LED1              GP33
#define LED1_PIN          P33 
#define LED1_GPIO_PORT    P3_OE

#define LED2              GP37
#define LED2_PIN          P37 
#define LED2_GPIO_PORT    P3_OE
//…………
#define LED1_ON           {LED1 = 0;}
#define LED1_OFF          {LED1 = 1;}
#define LED1_ONOFF        {LED1 = ~LED1;}

#define LED2_ON           {LED2 = 0;}
#define LED2_OFF          {LED2 = 1;}
#define LED2_ONOFF        {LED2 = ~LED2;}
//…………

//------------------------------------------------------------------------------
//UART   通信
//------------------------------------------------------------------------------
//SPI    通信
//------------------------------------------------------------------------------
//HALL   接口 
//管脚定义
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void SoftwareInit(void);
extern void MCL_ModuleDefault(void);
extern void MCL_ModuleInstance(void); //模块声明
extern void MCL_ModuleInit(void);     //模块初始化
extern void MCL_DefaultInit(void);    //
extern u8 Delay(u16 timer);
extern u8 Delayus(u16 timer);

#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/

