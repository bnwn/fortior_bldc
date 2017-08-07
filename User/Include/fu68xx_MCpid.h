
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
    int16 Ref;           //�ο�ֵ
    int16 Fdb;           //����ֵ
    int16 Kp;            //����PID����ϵ��
    int16 Ki;            //����PID����ϵ��
    int16 Err;           //����PID��ǰƫ��
    int16 Err_Last1;     //����PID�ϴ�ƫ��
    int16 Err_Err;       //����PID��ǰƫ����ϴ�ƫ��֮�Err_Err=Err-Err_Last1
    int16 Out;           //����PID���
    int16 OutMax;        //����PID�����������ֵ
    int16 OutMin;        //����PID�����С�����ֵ
}PIDREG3;

/*------------------------------------------------------------------------------
Prototypes for the functions in PIDREG3.C
------------------------------------------------------------------------------*/
extern PIDREG3 idata pid_spd ;                       //�ٶȻ� 
extern PIDREG3 idata pid_is ;                        //������

extern void Pid_Config(void);
extern void Pid_IsInit(void);
extern void Pid_SpdInit(void);
extern s16 Pid_calc( PIDREG3 *v);

#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/