
/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        : 警告：禁止修改,删除 结构体定义 否则会导致未知错误
********************************************************************************
/*******************************************************************************
* All Rights Reserved
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_KEY_H
#define __MC_KEY_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  s8 XCount;         //
  u8  Xflg;           //

  u8  KNum;           //
  u8  Kflg;           //
}key_TypeDef;

extern key_TypeDef xdata X0;
extern key_TypeDef xdata X1;
extern key_TypeDef xdata X2;
extern key_TypeDef xdata X3;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void Key_init(void);
extern void Key_Filtrate(void);
extern void Key_Config(void);
#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/