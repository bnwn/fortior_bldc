
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

#ifndef __MC_USERINTERFACE_H
#define __MC_USERINTERFACE_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct { 
    __IO u8 START:1;        //启停命令
    __IO u8 FR:2;           //正反转命令
    __IO u8 FAULT:1;        //故障
    __IO u8 FO:1;           //硬件过流
    __IO u8 KEY3:1;         
    __IO u8 KEY2:1; 
    __IO u8 KEY1:1; 
}bit_TypeDef; 

typedef struct
  {
    bit_TypeDef  flg; 
  }Uc_TypeDef;

extern Uc_TypeDef xdata Uc;  //全局变量声明
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void UI(void);        //全局函数声明

#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/