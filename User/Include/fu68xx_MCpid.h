
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
#ifndef __FU68XX_MCPID_H
#define __FU68XX_MCPID_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
typedef struct 
{
    int16 Ref;           //参考值
    int16 Fdb;           //反馈值
    int16 Kp;            //定义PID比例系数
    int16 Ki;            //定义PID积分系数
    int16 Err;           //定义PID当前偏差
    int16 Err_Last1;     //定义PID上次偏差
    int16 Err_Err;       //定义PID当前偏差和上次偏差之差，Err_Err=Err-Err_Last1
    int16 Out;           //定义PID输出
    int16 OutMax;        //定义PID输出最大溢出阀值
    int16 OutMin;        //定义PID输出最小溢出阀值
}PIDREG3;

/*------------------------------------------------------------------------------
Prototypes for the functions in PIDREG3.C
------------------------------------------------------------------------------*/
extern PIDREG3 idata pid_spd ;                       //速度环 
extern PIDREG3 idata pid_is ;                        //电流环

extern void Pid_Config(void);
extern void Pid_IsInit(void);
extern void Pid_SpdInit(void);
extern s16 Pid_calc( PIDREG3 *v);

#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/