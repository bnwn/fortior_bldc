/**************************** (C) COPYRIGHT 2015 Fortiortech shenzhen *****************************
* File Name          : FU68xx_SYSTEM.h
* Author             : Billy Long Fortiortech  Market Dept
* Version            : V1.0
* Date               : 01/07/2015
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/ 

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __FU68xx_SYSTEM_H_
#define __FU68xx_SYSTEM_H_

/* Includes -------------------------------------------------------------------------------------*/
#include <absacc.h>

/* Base Config Define ---------------------------------------------------------------------------*/
#define SET(reg,bit)					(reg |= (1<<bit))
#define CLR(reg,bit)					(reg &= ~(1<<bit))
#define SetBit(reg,bit,val)		val?(reg |= (1<<bit)):(reg &= ~(1<<bit))
#define GetBit(reg,bit)				(reg & (1<<bit))
#define SetReg(reg,val)	 			(reg = val)

/* Register Define ------------------------------------------------------------------------------*/
sfr ACC = 0xe0;					// 累加寄存器

sfr B = 0xf0;						// B寄存器

sfr PSW = 0xd0;         // 程序状态寄存器
sbit CY	 = PSW^7;
sbit AC	 = PSW^6;
sbit F0  = PSW^5;
sbit RS1 = PSW^4;
sbit RS0 = PSW^3;
sbit OV  = PSW^2;
sbit F1  = PSW^1;
sbit P	 = PSW^0;

sfr PCON = 0x87;
#define GF4	 		7
#define GF3	 		5
#define GF2			4
#define GF1	 		3
#define GF0	 		2
#define STOP 		1
#define IDLE 		0

sfr RSTSRC = 0xc9;			// 复位状态寄存器
#define POR			7
#define EXTR		6
#define LVDR		5
#define EOSR		4
#define WDTR		3
#define FEDR		2
#define DBGR		1
#define RSTCLR	0

sfr SP = 0x81;					// 堆栈指针寄存器

sfr16 DP = 0x82;				// 数据指针寄存器
sfr DPL = 0x82;
sfr DPH = 0x83;

sfr EVT_FILT = 0xd9;		// 故障保护寄存器
#define TSDEN		 	 	7		
#define TSDADJ1			6
#define TSDADJ0		  5		
#define MCLREN		  4		
#define EFSRC				3
#define EFEN				2
#define EFDIV1		  1
#define EFDIV0		  0

#define CCFG1 XBYTE[0x401e]
#define LVDENB		7
#define LVWIE			6
#define WDTEN			5
#define CKMOD			0


/* System Clock Config---------------------------------------------------------------------------*/

#define InternalFastClock    0
#define ExternalFastClock    1	

/*-------------------------------------------------------------------------------------------------
	Function Name :	InternalFastClockConfig(Status)
	Description   :	内部快时钟配置，强制使能内部快时钟晶振电路，切换系统时钟为内部快时钟
	Input         :	Statue--使能控制，Disable或Enable	
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void InternalFastClockConfig(bit Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	SystemFastClockConfig(Mode)
	Description   :	系统快时钟在线切换，外部快时钟默认为无源晶体模式。
	Input         :	Mode--系统快时钟模式，InternalFastClock或ExternalFastClock
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void SystemFastClockConfig(bit Mode);


/*-------------------------------------------------------------------------------------------------
	Function Name :	ExternalSlowClockConfig(Status)
	Description   :	外部慢时钟配置，使能外部慢时钟晶振电路
	Input         :	Statue--使能控制，Disable或Enable	
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void ExternalSlowClockConfig(bit Status);


/* System Power Config---------------------------------------------------------------------------*/

#define VREF3_0     0
#define VREF4_0			1
#define VREF4_5			2
#define VREF5_0			3	

#define VDD5_Half   0
#define VREF_Half		1		


/*-------------------------------------------------------------------------------------------------
	Function Name :	LVDPowerDownDetectConfig(Status)
	Description   :	掉电检测使能，检测到VCC电压低于设定值后触发预警或者VDD5电压低于设定
	                值后触发复位。
	Input         :	Statue--使能控制，1--Disable或0--Enable	
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void LVDPowerDownDetectConfig(bit Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	LVDPowerDownWarnIEConfig(Status)
	Description   :	掉电低压预警中断使能，检测到VCC电压低于设定值后触发预警，如果低压预
                  警中断则响应中断。
	Input         :	Statue--使能控制，Disable或Enable	
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void LVDPowerDownWarnIEConfig(bit Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	VREFConfig(Value, Status) 
	Description   :	参考电压VREF配置，如果使能VREF模块，则内部产生VREF输入到ADC作为ADC
									参考电压，如果禁止VREF模块，则由外部提供VREF输入到ADC作为ADC参考电压。
	Input         :	Value--VCC低电压预警值
                  0: VREF3_0, 参考电压VREF输出为3.0V
									1: VREF4_0, 参考电压VREF输出为4.0V
									2: VREF4_5, 参考电压VREF输出为4.5V
									3: VREF5_0, 参考电压VREF输出为5.0V	
                  Statue--使能控制，Disable或Enable。 																								
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void VREFConfig(uint8 Value, bit Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	VHALFConfig(Mode, Status)
	Description   :	基准电压VHALF配置，使能VHALF工作模块，选择VREF/2或者VDD5/2作为基准
									电压VHALF输出，VHALF可用作运放基准电压。
	Input         :	Mode--VHALF输出选择，VREF_Half或者VDD5_Half。
                  Statue--使能控制，Disable或Enable。 																								
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void VHALFConfig(bit Mode, bit Status);


/* WatchDog Config-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
	Function Name ：void WatchDogRefresh(void
	Description   ：看门狗定时函数初始化，看门狗使能和复位使能，定时配置
	Input         ：Value--定时时间，单位ms，最小定时时间8ms，最大定时1800ms
                  Statue--使能控制，Disable或Enable	
  Output				：None
-------------------------------------------------------------------------------------------------*/
extern void WatchDogConfig(uint16 Value, bit Status);

/*-------------------------------------------------------------------------------------------------
	Function Name ：WatchDogRefresh(Value ,Status)
	Description   ：刷新看门狗计数器
	Input         ：None
  Output				：None
-------------------------------------------------------------------------------------------------*/
extern void WatchDogRefresh(void);



/* Flash Program Config--------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint8 Flash_Sector_Erase(uint8 xdata *FlashAddress)
	Description   :	扇区自擦除: 指定将要擦除的Flash扇区，每个扇区128Byte，共128个扇区，
									扇区0~127对应Flash地址0x0000~0x3fff，通过指定Flash地址来指定要擦除
									的Flash地址所在扇区。一次只能擦除一个扇区，自擦除数据为任意值，一定
									要在解锁后才给DPTR赋值。
	Input         :	FlashAddress--Flash自擦除扇区内任意地址
  Output				:	0--Flash自擦除成功，1--Flash自擦除失败
-------------------------------------------------------------------------------------------------*/
extern uint8 Flash_Sector_Erase(uint8 xdata *FlashAddress);

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint8 Flash_Sector_Write(uint8 xdata *FlashAddress, uint8 FlashData)
	Description   :	Flash自烧写: 对扇区预编程和自擦除后，可以对扇区内的地址进行Flash烧写，
                  一次烧写一个byte,一定要在解锁后才给DPTR赋值
	Input         :	FlashAddress--Flash烧写地址
									FlashData--Flash烧写数据
  Output				:	0--Flash自烧写成功，1--Flash自烧写失败	
-------------------------------------------------------------------------------------------------*/
extern uint8 Flash_Sector_Write(uint8 xdata *FlashAddress, uint8 FlashData);


#endif
