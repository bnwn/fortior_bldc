/**************************** (C) COPYRIGHT 2015 Fortiortech shenzhen *****************************
* File Name          : FU68xx_TIMER.h
* Author             : Billy Long Fortiortech  Market Dept
* Version            : V1.0
* Date               : 01/07/2015
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/ 

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __FU68xx_TIMER_H_
#define __FU68xx_TIMER_H_

/* Includes -------------------------------------------------------------------------------------*/
#include <absacc.h>

/* Base Config Define ---------------------------------------------------------------------------*/
#define SET(reg,bit)					(reg |= (1<<bit))
#define CLR(reg,bit)					(reg &= ~(1<<bit))
#define SetBit(reg,bit,val)		val?(reg |= (1<<bit)):(reg &= ~(1<<bit))
#define GetBit(reg,bit)				(reg & (1<<bit))
#define SetReg(reg,val)	 			(reg = val)


/*�жϱ�־����ָ��-------------------------------------------------------------------------------*/
/*TIM0�жϱ�־����ָ��*/
#define CLRFlag_COMIF 				{TIM0_SR1 = ~(1<<COMIF);}
#define CLRFlag_CC4IF   			{TIM0_SR1 = ~(1<<CC4IF);}
#define CLRFlag_CC3IF   			{TIM0_SR1 = ~(1<<CC3IF);}
#define CLRFlag_CC2IF   			{TIM0_SR1 = ~(1<<CC2IF);}
#define CLRFlag_CC1IF   			{TIM0_SR1 = ~(1<<CC1IF);}
#define CLRFlag_UIF   				{TIM0_SR1 = ~(1<<UIF);}

/*TIM1�жϱ�־����ָ��*/
#define CLRFlag_BOIF   				{TIM1_SR = ~(1<<BOIF);}
#define CLRFlag_RUIF 					{TIM1_SR = ~(1<<RUIF);}
#define CLRFlag_WTIF   				{TIM1_SR = ~(1<<WTIF);}
#define CLRFlag_PDIF   				{TIM1_SR = ~(1<<PDIF);}
#define CLRFlag_CPIF   				{TIM1_SR = ~(1<<CPIF);}

/*TIM2�жϱ�־����ָ��*/
#define CLRFlag_T2IR 					{TIM2_CR1 = TIM2_CR1 & (~(1<<T2IR)) | 0x60;}
#define CLRFlag_T2IP   				{TIM2_CR1 = TIM2_CR1 & (~(1<<T2IP)) | 0xa0;}
#define CLRFlag_T2IF   				{TIM2_CR1 = TIM2_CR1 & (~(1<<T2IF)) | 0xc0;}

/*TIM3�жϱ�־����ָ��*/
#define CLRFlag_T3IR 					{TIM3_CR1 = TIM3_CR1 & (~(1<<T3IR)) | 0x60;}
#define CLRFlag_T3IP   				{TIM3_CR1 = TIM3_CR1 & (~(1<<T3IP)) | 0xa0;}
#define CLRFlag_T3IF   				{TIM3_CR1 = TIM3_CR1 & (~(1<<T3IF)) | 0xc0;}

/*TIM3�жϱ�־����ָ��*/
#define CLRFlag_T4IR 					{TIM4_CR1 = TIM4_CR1 & (~(1<<T4IR)) | 0x60;}
#define CLRFlag_T4IP   				{TIM4_CR1 = TIM4_CR1 & (~(1<<T4IP)) | 0xa0;}
#define CLRFlag_T4IF   				{TIM4_CR1 = TIM4_CR1 & (~(1<<T4IF)) | 0xc0;}

/*TIM3�жϱ�־����ָ��*/
#define CLRFlag_T5IR 					{TIM5_CR1 = TIM5_CR1 & (~(1<<T5IR)) | 0x60;}
#define CLRFlag_T5IP   				{TIM5_CR1 = TIM5_CR1 & (~(1<<T5IP)) | 0xa0;}
#define CLRFlag_T5IF   				{TIM5_CR1 = TIM5_CR1 & (~(1<<T5IF)) | 0xc0;}

/* Register Define ------------------------------------------------------------------------------*/
/*TIM0��ؼĴ���*/
sfr TIM0_IER = 0xb9;										// TIM0�ж�ʹ�ܼĴ���
#define COMIE		5
#define CC4IE		4
#define CC3IE		3
#define CC2IE		2
#define CC1IE		1
#define UIE			0

sfr TIM0_SR1 = 0xb1;										// TIM0�ж�״̬�Ĵ���
#define COMIF		5
#define CC4IF		4
#define CC3IF		3
#define CC2IF		2
#define CC1IF		1
#define UIF			0

sfr16 TIM0_CCR1 = 0xb6;									// TIM0ͨ��1�Ƚ�����Ĵ���
sfr TIM0_CCR1L = 0xb6;
sfr TIM0_CCR1H = 0xb7;

sfr16 TIM0_CCR2 = 0xba;									// TIM0ͨ��2�Ƚ�����Ĵ���
sfr TIM0_CCR2L = 0xba;
sfr TIM0_CCR2H = 0xbb;

sfr16 TIM0_CCR3 = 0xbc;									// TIM0ͨ��3�Ƚ�����Ĵ���
sfr TIM0_CCR3L = 0xbc;
sfr TIM0_CCR3H = 0xbd;

sfr16 TIM0_CCR4 = 0xbe;									// TIM0ͨ��4�Ƚ�����Ĵ���
sfr TIM0_CCR4L = 0xbe;
sfr TIM0_CCR4H = 0xbf;

#define TIM0_CR XBYTE[0x4058]						// TIM0���ƼĴ���
#define ARPE		7		
#define CMS1		6		
#define CMS0		5		
#define DIR			4		
#define OPM			3		
#define URS			2		
#define UDIS		1		
#define CEN			0		

#define TIM0_EGR XBYTE[0x4059]    			// TIM0�¼��Ĵ���
#define	COMG 		5
#define	CC4G 		4
#define	CC3G 		3
#define	CC2G 		2
#define	CC1G		1
#define	UG			0

#define TIM0_CCMR1 XBYTE[0x405A]				// TIM0���ģʽ�Ĵ���1
#define	OC2M2 	7
#define	OC2M1		6
#define	OC2M0		5
#define	OC2PE 	4
#define	OC1M2 	3
#define	OC1M1		2
#define	OC1M0		1
#define	OC1PE 	0

#define TIM0_CCMR2 XBYTE[0x405B] 				// TIM0���ģʽ�Ĵ���2
#define	OC4M2 	7
#define	OC4M1		6
#define	OC4M0		5
#define	OC4PE 	4
#define	OC3M2 	3
#define	OC3M1		2
#define	OC3M0		1
#define	OC3PE 	0

#define TIM0_CCER1 XBYTE[0x405C]				// TIM0���ʹ��/���ԼĴ���1
#define	CC2NP 	7
#define	CC2NE 	6
#define	CC2P 		5
#define	CC2E 		4
#define	CC1NP 	3
#define	CC1NE		2
#define	CC1P 		1
#define	CC1E 		0

#define TIM0_CCER2 XBYTE[0x405D]				// TIM0���ʹ��/���ԼĴ���2
#define	CCPC 		6
#define	CC4P 		5
#define	CC4E 		4
#define	CC3NP 	3
#define	CC3NE 	2
#define	CC3P		1
#define	CC3E 		0

#define TIM0_CNTR *(volatile unsigned int xdata *)0x405E   // TIM0�������Ĵ���
#define TIM0_CNTRH XBYTE[0x405E]
#define TIM0_CNTRL XBYTE[0x405F]
	
#define TIM0_ARR *(volatile unsigned int xdata *)0x4060    // TIM0�Զ����ؼĴ���
#define TIM0_ARRH XBYTE[0x4060]
#define TIM0_ARRL XBYTE[0x4061]

#define TIM0_PSCR XBYTE[0x4062]					// TIM0Ԥ��Ƶ�Ĵ���

#define TIM0_RCR XBYTE[0x4063]					// TIM0�ظ������Ĵ���

#define TIM0_DTR XBYTE[0x4064]					// TIM0�����Ĵ���


/*TIM1��ؼĴ���*/
#define TIM1_CR0 XBYTE[0x4068]					// TIM1���ƼĴ���0
#define	CPE1	 	7
#define	CPE0	 	6
#define	INC2	 	5
#define	INC1	 	4
#define	INC0	 	3
#define	IEE2		2
#define	IEE1		1
#define	IEE0		0

#define TIM1_CR1 XBYTE[0x4069]					// TIM1���ƼĴ���1
#define	RCEN		7
#define	ROPM		6
#define	WTS1 		5
#define	WTS0	 	4
#define	CPD2	 	3
#define	CPD1		2
#define	CPD0		1
#define	CMPE		0

#define TIM1_CR2 XBYTE[0x406a]					// TIM1���ƼĴ���2
#define	BRS			7		
#define	TIS		 	6
#define	INM21 	5
#define	INM20 	4
#define	INM11 	3
#define	INM10		2
#define	INM01		1
#define	INM00		0

#define TIM1_CR3 XBYTE[0x406b]					// TIM1���ƼĴ���3
#define T1PSC3	7
#define T1PSC2	6
#define T1PSC1	5
#define T1PSC0	4
#define OPS2		3
#define OPS1		2
#define OPS0		1
#define BCEN		0

#define TIM1_IER XBYTE[0x406c]					// TIM1�ж�ʹ�ܼĴ���
#define BOIE		4
#define	RUIE	 	3
#define	WTIE		2
#define	PDIE		1
#define	CPIE		0

#define TIM1_SR XBYTE[0x406d]						// TIM1�ж�״̬�Ĵ���
#define BOIF		4
#define	RUIF	 	3
#define	WTIF	 	2
#define	PDIF	 	1
#define	CPIF	 	0

#define TIM1_DR *(volatile unsigned int xdata *)0x406e  // TIM1����Ĵ���
#define TIM1_DRH XBYTE[0x406e]
#define	RDA2 		6
#define	RDA1 		5
#define	RDA0 		4
#define	OC3NP 	3
#define	OC3NE		2
#define	OC3P		1
#define	OC3E		0

#define TIM1_DRL XBYTE[0x406f]
#define	OC2NP 	7
#define	OC2NE 	6
#define	OC2P 		5
#define	OC2E 		4
#define	OC1NP 	3
#define	OC1NE		2
#define	OC1P		1
#define	OC1E		0

#define TIM1_DBR *(volatile unsigned int xdata *)0x4070  		// TIM1�������Ĵ���
#define TIM1_DBRH XBYTE[0x4070]
#define TIM1_DBRL XBYTE[0x4071]

#define TIM1_BCCR *(volatile unsigned int xdata *)0x4072 		// TIM1������ʱ������Ĵ���
#define TIM1_BCCRH XBYTE[0x4072]
#define TIM1_BCCRL XBYTE[0x4073]

#define TIM1_RARR *(volatile unsigned int xdata *)0x4074 		// TIM1���ض�ʱ���Զ����ؼĴ���
#define TIM1_RARRH XBYTE[0x4074]
#define TIM1_RARRL XBYTE[0x4075]

#define TIM1_RCNTR *(volatile unsigned int xdata *)0x4076 	// TIM1���ض�ʱ���������Ĵ���
#define TIM1_RCNTRH XBYTE[0x4076]
#define TIM1_RCNTRL XBYTE[0x4077]

#define TIM1_BARR *(volatile unsigned int xdata *)0x4078    // TIM1������ʱ���Զ����ؼĴ���
#define TIM1_BARRH XBYTE[0x4078]
#define TIM1_BARRL XBYTE[0x4079]

#define TIM1_BCNTR *(volatile unsigned int xdata *)0x407a		// TIM1������ʱ���������Ĵ���
#define TIM1_BCNTRH XBYTE[0x407a]
#define TIM1_BCNTRL XBYTE[0x407b]

#define TIM1_DTR XBYTE[0x4064]															// TIM1�����Ĵ���


/*TIM2��ؼĴ���*/
sfr TIM2_CR0 = 0xa1;												// TIM2���ƼĴ���0
#define T2PSC2		7
#define T2PSC1		6
#define T2PSC0		5
#define T2OCM1		4
#define T2OCM0		3
#define T2CES			2
#define T2CTM			1
#define T2MODE		0

sfr TIM2_CR1 = 0xa9;												// TIM2���ƼĴ���1
#define T2IR			7
#define T2IP			6
#define T2IF			5
#define T2IDE			4
#define T2IFE			3
#define T2FE			2
#define T2OPM			1
#define T2CEN			0

sfr16 TIM2_CNTR = 0xaa;											// TIM2�������Ĵ���
sfr TIM2_CNTRL = 0xaa;
sfr TIM2_CNTRH = 0xab;

sfr16 TIM2_DR = 0xac;												// TIM2�Ƚ�ƥ��Ĵ���
sfr TIM2_DRL = 0xac;
sfr TIM2_DRH = 0xad;

sfr16 TIM2_ARR = 0xae;											// TIM2�Զ����ؼĴ���
sfr TIM2_ARRL = 0xae;
sfr TIM2_ARRH = 0xaf;

sfr16 TIM2_CMTR = 0xb2;											// �Ƚ���CMP0/1/2������������Ĵ���
sfr TIM2_CMTRL = 0xb2;
sfr TIM2_CMTRH = 0xb3;

sfr16 TIM2_ADTR = 0xb4;											// ADCͨ��4���������Ĵ���
sfr TIM2_ADTRL = 0xb4;
sfr TIM2_ADTRH = 0xb5;


/*TIM3��ؼĴ���*/
sfr TIM3_CR0 = 0x9c;												// TIM3���ƼĴ���0
#define T3PSC2		7
#define T3PSC1		6
#define T3PSC0		5
#define T3OCM1		4
#define T3OCM0		3
#define T3CES			2
#define T3CTM			1
#define T3MODE		0

sfr TIM3_CR1 = 0x9d;												// TIM3���ƼĴ���1
#define T3IR			7
#define T3IP			6
#define T3IF			5
#define T3IDE			4
#define T3IFE			3
#define T3FE			2
#define T3OPM			1
#define T3CEN			0

sfr16 TIM3_CNTR = 0xa2;											// TIM3�������Ĵ���
sfr TIM3_CNTRL = 0xa2;
sfr TIM3_CNTRH = 0xa3;

sfr16 TIM3_DR = 0xa4;												// TIM3�Ƚ�ƥ��Ĵ���
sfr TIM3_DRL = 0xa4;
sfr TIM3_DRH = 0xa5;

sfr16 TIM3_ARR = 0xa6;											// TIM3�Զ����ؼĴ���
sfr TIM3_ARRL = 0xa6;
sfr TIM3_ARRH = 0xa7;


/*TIM4��ؼĴ���*/
sfr TIM4_CR0 = 0x9e;												// TIM4���ƼĴ���0
#define T4PSC2		7
#define T4PSC1		6
#define T4PSC0		5
#define T4OCM1		4
#define T4OCM0		3
#define T4CES			2
#define T4CTM			1
#define T4MODE		0

sfr TIM4_CR1 = 0x9f;												// TIM4���ƼĴ���1
#define T4IR			7
#define T4IP			6
#define T4IF			5
#define T4IDE			4
#define T4IFE			3
#define T4FE			2
#define T4OPM			1
#define T4CEN			0

sfr16 TIM4_CNTR = 0x92;											// TIM4�������Ĵ���
sfr TIM4_CNTRL = 0x92;
sfr TIM4_CNTRH = 0x93;

sfr16 TIM4_DR = 0x94;												// TIM4�Ƚ�ƥ��Ĵ���
sfr TIM4_DRL = 0x94;
sfr TIM4_DRH = 0x95;

sfr16 TIM4_ARR = 0x96;											// TIM4�Զ����ؼĴ���
sfr TIM4_ARRL = 0x96;
sfr TIM4_ARRH = 0x97;


/*TIM4��ؼĴ���*/
sfr TIM5_CR0 = 0x89;												// TIM5���ƼĴ���0
#define T5PSC2		7
#define T5PSC1		6
#define T5PSC0		5
#define T5OCM1		4
#define T5OCM0		3
#define T5CES			2
#define T5CTM			1
#define T5MODE		0

sfr TIM5_CR1 = 0x91;												// TIM5���ƼĴ���1
#define T5IR			7
#define T5IP			6
#define T5IF			5
#define T5IDE			4
#define T5IFE			3
#define T5FE			2
#define T5OPM			1
#define T5CEN     0

sfr16 TIM5_CNTR = 0x8a;											// TIM5�������Ĵ���
sfr TIM5_CNTRL = 0x8a;
sfr TIM5_CNTRH = 0x8b;

sfr16 TIM5_DR = 0x8c;												// TIM5�Ƚ�ƥ��Ĵ���
sfr TIM5_DRL = 0x8c;
sfr TIM5_DRH = 0x8d;

sfr16 TIM5_ARR = 0x8e;											// TIM5�Զ����ؼĴ���
sfr TIM5_ARRL = 0x8e;
sfr TIM5_ARRH = 0x8f;



#endif
