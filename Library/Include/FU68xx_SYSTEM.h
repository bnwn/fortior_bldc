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
sfr ACC = 0xe0;					// �ۼӼĴ���

sfr B = 0xf0;						// B�Ĵ���

sfr PSW = 0xd0;         // ����״̬�Ĵ���
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

sfr RSTSRC = 0xc9;			// ��λ״̬�Ĵ���
#define POR			7
#define EXTR		6
#define LVDR		5
#define EOSR		4
#define WDTR		3
#define FEDR		2
#define DBGR		1
#define RSTCLR	0

sfr SP = 0x81;					// ��ջָ��Ĵ���

sfr16 DP = 0x82;				// ����ָ��Ĵ���
sfr DPL = 0x82;
sfr DPH = 0x83;

sfr EVT_FILT = 0xd9;		// ���ϱ����Ĵ���
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
	Description   :	�ڲ���ʱ�����ã�ǿ��ʹ���ڲ���ʱ�Ӿ����·���л�ϵͳʱ��Ϊ�ڲ���ʱ��
	Input         :	Statue--ʹ�ܿ��ƣ�Disable��Enable	
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void InternalFastClockConfig(bit Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	SystemFastClockConfig(Mode)
	Description   :	ϵͳ��ʱ�������л����ⲿ��ʱ��Ĭ��Ϊ��Դ����ģʽ��
	Input         :	Mode--ϵͳ��ʱ��ģʽ��InternalFastClock��ExternalFastClock
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void SystemFastClockConfig(bit Mode);


/*-------------------------------------------------------------------------------------------------
	Function Name :	ExternalSlowClockConfig(Status)
	Description   :	�ⲿ��ʱ�����ã�ʹ���ⲿ��ʱ�Ӿ����·
	Input         :	Statue--ʹ�ܿ��ƣ�Disable��Enable	
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
	Description   :	������ʹ�ܣ���⵽VCC��ѹ�����趨ֵ�󴥷�Ԥ������VDD5��ѹ�����趨
	                ֵ�󴥷���λ��
	Input         :	Statue--ʹ�ܿ��ƣ�1--Disable��0--Enable	
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void LVDPowerDownDetectConfig(bit Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	LVDPowerDownWarnIEConfig(Status)
	Description   :	�����ѹԤ���ж�ʹ�ܣ���⵽VCC��ѹ�����趨ֵ�󴥷�Ԥ���������ѹԤ
                  ���ж�����Ӧ�жϡ�
	Input         :	Statue--ʹ�ܿ��ƣ�Disable��Enable	
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void LVDPowerDownWarnIEConfig(bit Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	VREFConfig(Value, Status) 
	Description   :	�ο���ѹVREF���ã����ʹ��VREFģ�飬���ڲ�����VREF���뵽ADC��ΪADC
									�ο���ѹ�������ֹVREFģ�飬�����ⲿ�ṩVREF���뵽ADC��ΪADC�ο���ѹ��
	Input         :	Value--VCC�͵�ѹԤ��ֵ
                  0: VREF3_0, �ο���ѹVREF���Ϊ3.0V
									1: VREF4_0, �ο���ѹVREF���Ϊ4.0V
									2: VREF4_5, �ο���ѹVREF���Ϊ4.5V
									3: VREF5_0, �ο���ѹVREF���Ϊ5.0V	
                  Statue--ʹ�ܿ��ƣ�Disable��Enable�� 																								
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void VREFConfig(uint8 Value, bit Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	VHALFConfig(Mode, Status)
	Description   :	��׼��ѹVHALF���ã�ʹ��VHALF����ģ�飬ѡ��VREF/2����VDD5/2��Ϊ��׼
									��ѹVHALF�����VHALF�������˷Ż�׼��ѹ��
	Input         :	Mode--VHALF���ѡ��VREF_Half����VDD5_Half��
                  Statue--ʹ�ܿ��ƣ�Disable��Enable�� 																								
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void VHALFConfig(bit Mode, bit Status);


/* WatchDog Config-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
	Function Name ��void WatchDogRefresh(void
	Description   �����Ź���ʱ������ʼ�������Ź�ʹ�ܺ͸�λʹ�ܣ���ʱ����
	Input         ��Value--��ʱʱ�䣬��λms����С��ʱʱ��8ms�����ʱ1800ms
                  Statue--ʹ�ܿ��ƣ�Disable��Enable	
  Output				��None
-------------------------------------------------------------------------------------------------*/
extern void WatchDogConfig(uint16 Value, bit Status);

/*-------------------------------------------------------------------------------------------------
	Function Name ��WatchDogRefresh(Value ,Status)
	Description   ��ˢ�¿��Ź�������
	Input         ��None
  Output				��None
-------------------------------------------------------------------------------------------------*/
extern void WatchDogRefresh(void);



/* Flash Program Config--------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint8 Flash_Sector_Erase(uint8 xdata *FlashAddress)
	Description   :	�����Բ���: ָ����Ҫ������Flash������ÿ������128Byte����128��������
									����0~127��ӦFlash��ַ0x0000~0x3fff��ͨ��ָ��Flash��ַ��ָ��Ҫ����
									��Flash��ַ����������һ��ֻ�ܲ���һ���������Բ�������Ϊ����ֵ��һ��
									Ҫ�ڽ�����Ÿ�DPTR��ֵ��
	Input         :	FlashAddress--Flash�Բ��������������ַ
  Output				:	0--Flash�Բ����ɹ���1--Flash�Բ���ʧ��
-------------------------------------------------------------------------------------------------*/
extern uint8 Flash_Sector_Erase(uint8 xdata *FlashAddress);

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint8 Flash_Sector_Write(uint8 xdata *FlashAddress, uint8 FlashData)
	Description   :	Flash����д: ������Ԥ��̺��Բ����󣬿��Զ������ڵĵ�ַ����Flash��д��
                  һ����дһ��byte,һ��Ҫ�ڽ�����Ÿ�DPTR��ֵ
	Input         :	FlashAddress--Flash��д��ַ
									FlashData--Flash��д����
  Output				:	0--Flash����д�ɹ���1--Flash����дʧ��	
-------------------------------------------------------------------------------------------------*/
extern uint8 Flash_Sector_Write(uint8 xdata *FlashAddress, uint8 FlashData);


#endif
