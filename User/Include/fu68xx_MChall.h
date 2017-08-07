
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
#ifndef __FU68XX_HALL_H
#define __FU68XX_HALL_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

#if (HallMode == HallIC)
  #define	HA	GP14
  #define	HB	GP16
  #define	HC	GP21
#elif (HallMode == HallSensor)
//  #define	HA	GetBit(CMP_SR, CMP0OUT)
//  #define	HB	GetBit(CMP_SR, CMP1OUT)
//  #define	HC	GetBit(CMP_SR, CMP2OUT)

  #define	HA	GetBit((CMP_SR>>CMP0OUT)&&0x01)   //Ã»ÓÐ²âÊÔ 20160222
  #define	HB	GetBit((CMP_SR>>CMP1OUT)&&0x01)
  #define	HC	GetBit((CMP_SR>>CMP2SOUT)&&0x01)
#endif
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void Hall_Init(void);
extern u8 Hall_IRQHandler(void);
#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/