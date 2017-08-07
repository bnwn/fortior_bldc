/**************************** (C) COPYRIGHT 2015 Fortiortech shenzhen *****************************
* File Name          : FU68xx.h
* Author             : Billy Long Fortiortech  Market Dept
* Version            : V1.0
* Date               : 01/07/2015
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/ 

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __FU68xx_H_
#define __FU68xx_H_

/* Includes -------------------------------------------------------------------------------------*/
#include <absacc.h>						//absacc.h����ֱ�ӷ���8051��ͬ����洢���ĺ�
#include <intrins.h>					//intrins.h�����ղ���������λ�Ƶ���Ƕ����
#include <math.h>							//math.h���������������ѧ����
#include <stdlib.h>						//stdlib.h������������װ��������������ʹ洢����λ����
// #include <string.h>						//string.h�����ַ����ͻ����������
// #include <stdio.h>						//stdio.h��������������ĺ���ԭ��
// #include <ctype.h>						//ctype.h����ASCII�ַ��ķ����ת������
// #include <setjmp.h>						//setjmp.h����setjump��longjump�����jump_buf����
// #include <stdarg.h>						//stdarg.h�������ʺ��������ĺ�

/* Base Config Define ---------------------------------------------------------------------------*/
#define SET(reg,bit)					(reg |= (1<<bit))
#define CLR(reg,bit)					(reg &= ~(1<<bit))
#define SetBit(reg,bit,val)		val?(reg |= (1<<bit)):(reg &= ~(1<<bit))
#define GetBit(reg,bit)				(reg & (1<<bit))
#define SetReg(reg,val)	 			(reg = val)

/*���ú궨��-------------------------------------------------------------------------------------*/
//#define Q12(n)		(uint32)(n*4095.0)
//#define Q15(n)		(uint32)(n*32767.0)
//#define Q16(n)		(uint32)(n*65535.0)
#define Enable		1
#define Disable		0
#define True			1
#define False			0

/*�Զ����������ͼ��-----------------------------------------------------------------------------*/

typedef   signed char       int8;
typedef   signed int        int16;
typedef   signed long       int32;

typedef   unsigned char     uint8;
typedef   unsigned int      uint16;
typedef   unsigned long     uint32;

/*�Զ����������ͼ��-----------------------------------------------------------------------------*/
#define     __I     volatile const    /*!< defines 'read only' permissions      */
#define     __O     volatile          /*!< defines 'write only' permissions     */
#define     __IO    volatile          /*!< defines 'read / write' permissions   */

typedef signed char         s8;
typedef signed int          s16;
typedef signed long         s32;

typedef unsigned long       u32;
typedef unsigned int        u16;
typedef unsigned char       u8;

typedef  const int32  code  sc32;  /*!< Read Only */
typedef  const int16  code  sc16;  /*!< Read Only */
typedef  const int8   code  sc8;   /*!< Read Only */
typedef  const uint32 code  uc32;  /*!< Read Only */
typedef  const uint16 code  uc16;  /*!< Read Only */
typedef  const uint8  code  uc8;   /*!< Read Only */

typedef enum {FALSE = 0, TRUE = 1} bool;

/*FTC6801�豸�Ĵ���------------------------------------------------------------------------------*/
#include <FU68xx_SYSTEM.h>
#include <FU68xx_POWER.h>
#include <FU68xx_INT.h>
#include <FU68xx_FLASH.h>
#include <FU68xx_OSC.h>
#include <FU68xx_WDT.h>
#include <FU68xx_CRC.h>
#include <FU68xx_RTC.h>
#include <FU68xx_GPIO.h>
#include <FU68xx_TIMER.h>
#include <FU68xx_I2C.h>
#include <FU68xx_SPI.h>
#include <FU68xx_UART.h>
#include <FU68xx_ADC.h>
#include <FU68xx_CMP.h>
#include <FU68xx_AMP.h>
#include <FU68xx_MDU.h>
#include <FU68xx_SVPWM.h>
#include <FU68xx_FOC.h>
#include <FU68xx_PI.h>
#include <FU68xx_LPF.h>
#include <FU68xx_SINCOS.h>

#endif

