
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
#ifndef __MC_MOTORFUNCTION_LAYER_H
#define __MC_MOTORFUNCTION_LAYER_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
  {
    s16 ref;
    s16 fdb;
    s16 err;
  }Power_TypeDef;
extern Power_TypeDef Power;  
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern float Drv_PowerThermCalc(u16 VthMeas);     //PTC电阻温度计算模块
extern void MCL_OverLoadInit(u16 OL0A,u16 OL1A,u16 OL2A,u16 OL3A,u32 OL0ms,u32 OL1ms,u32 OL2ms,u32 OL3ms);//过载初始化
extern u8  MCL_OverLoadCalc(u16 Ibus);            //过载计算
extern u32 Drv_RotorCircleNumCalc(u8 value);      //运行圈数计算
extern void Mcl_MotorRestart(void);
extern u8  Mcl_StallRestart(void);                //堵转重启
extern void Mcl_NoloadCale(void);                 //判断电机是否空载
extern void Drv_PowerClosedCalc(void);
extern void Drv_Stb3Calc(void);
extern void Drv_BemfSetFRFun(void);               //电调应用 电机运行方向设定

  
#endif /*  */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/