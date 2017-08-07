/**
  ******************************************************************************
  * @file BLDC/inc/HD_init.h 
  * @author  
  * @version  V1.0.0
  * @date  04/28/2014
  * @brief  Header for main.c module
  ******************************************************************************
  * @copy
  *
  *
  * <h2><center>&copy; COPYRIGHT 2014 FT</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HD_INIT_H
#define __HD_INIT_H

/* Includes ------------------------------------------------------------------*/
#include "fu68xx_driver.h"
/* Exported types ------------------------------------------------------------*/
extern Uc_TypeDef xdata Uc; 
extern uc8 HALL2SECTIONCW[8];
extern uc8 HALL2SECTIONCCW[8];
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void InitSysCtrl(void);
extern void ApplicationInit(void);
#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/