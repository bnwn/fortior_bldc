/**************************** (C) COPYRIGHT 2015 Fortiortech shenzhen *****************************
* File Name          : FU68xx_MDU.h
* Author             : Billy Long Fortiortech  Market Dept
* Version            : V1.0
* Date               : 01/07/2015
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/ 

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __FU68xx_MDU_H_
#define __FU68xx_MDU_H_

/* Includes -------------------------------------------------------------------------------------*/
#include <absacc.h>

/* Base Config Define ---------------------------------------------------------------------------*/
#define SET(reg,bit)					(reg |= (1<<bit))
#define CLR(reg,bit)					(reg &= ~(1<<bit))
#define SetBit(reg,bit,val)		val?(reg |= (1<<bit)):(reg &= ~(1<<bit))
#define GetBit(reg,bit)				(reg & (1<<bit))
#define SetReg(reg,val)	 			(reg = val)

/* Register Define ------------------------------------------------------------------------------*/
sfr MD_MODE = 0xc1;                    // MDU���üĴ���
#define	DIVDONE			7
#define	DIVERR			6
#define ALIGN1			3
#define ALIGN0			2
#define MDSN				1
#define DIVSTART		0

sfr16 MD_MA = 0xc2;											// �˷��Ĵ���
sfr MD_MAL = 0xc2;
sfr MD_MAH = 0xc3;

sfr16 MD_DAL = 0xc4;										// �����Ĵ���
sfr16 MD_DAH = 0xc6;
sfr MD_DA0 = 0xc4;
sfr MD_DA1 = 0xc5;
sfr MD_DA2 = 0xc6;
sfr MD_DA3 = 0xc7;

sfr16 MD_MB = 0xca;											// �˷��Ĵ���
sfr MD_MBL = 0xca;
sfr MD_MBH = 0xcb;

sfr16 MD_DBL = 0xcc;										// �����Ĵ���
sfr16 MD_DBH = 0xce;
sfr MD_DB0 = 0xcc;
sfr MD_DB1 = 0xcd;
sfr MD_DB2 = 0xce;
sfr MD_DB3 = 0xcf;


extern int16 MDU_MUL_S16(int16 TData0, int16 TData1);
extern uint16 MDU_MUL_U16(uint16 TData0, uint16 TData1);
extern int16 MDU_MULA_S16(int16 TData0, int16 TData1, uint8 ALIGN);
extern uint16 MDU_MULA_U16(uint16 TData0, uint16 TData1, uint8 ALIGN);
extern uint16 MDU_DIV_U16(uint16 xdata *TData0, uint16 xdata *TData1);

extern void MDU_MUL_S32(int16 TData0, int16 TData1, uint16 xdata *Result32);
extern void MDU_MUL_U32(uint16 TData0, uint16 TData1, uint16 xdata *Result32);
extern void MDU_MULA_S32(int16 TData0, int16 TData1, uint8 ALIGN, uint16 xdata *Result32);
extern void MDU_MULA_U32(uint16 TData0, uint16 TData1, uint8 ALIGN, uint16 xdata *Result32);
//extern void MDU_DIV_U32(uint16 xdata *TData0, uint16 xdata *TData1, uint16 xdata *Result32);
extern uint32 MDU_DIV_U32(uint32 TData0, uint32 TData1);
#endif