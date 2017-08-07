
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
    __IO u8 START:1;        //��ͣ����
    __IO u8 FR:2;           //����ת����
    __IO u8 FAULT:1;        //����
    __IO u8 FO:1;           //Ӳ������
    __IO u8 KEY3:1;         
    __IO u8 KEY2:1; 
    __IO u8 KEY1:1; 
}bit_TypeDef; 

typedef struct
  {
    bit_TypeDef  flg; 
  }Uc_TypeDef;

extern Uc_TypeDef xdata Uc;  //ȫ�ֱ�������
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void UI(void);        //ȫ�ֺ�������

#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/