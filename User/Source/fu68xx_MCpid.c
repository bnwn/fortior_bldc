
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

/* Includes ------------------------------------------------------------------*/
#include <FU68xx.h>
#include "sys_conf.h"
#include "fu68xx_MCpid.h"

/** @addtogroup FT68xx
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PIDREG3 idata pid_spd ;                       //�ٶȻ� 
PIDREG3 idata pid_is ;                        //������
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Pid_Config(void);                        //pidģ������
void Pid_IsInit(void);
void Pid_SpdInit(void);
s16  Pid_calc( PIDREG3 *v);                   //����

void Pid_Config(void)
{
/*-----------------------------------------------------------------------------------
	PI���ݸ�ʽ
	Q = PIRANGE + 8(Q8~Q23���ݸ�ʽ)
  ���Ĵ�����ֵʱҪͳһ���ݸ�ʽ
-----------------------------------------------------------------------------------*/		
  SetBit(PL_CR, PIRANGE3, 0);
  SetBit(PL_CR, PIRANGE2, 1);
  SetBit(PL_CR, PIRANGE1, 1);
  SetBit(PL_CR, PIRANGE0, 1);				//PI��λQ=PIRANGE+8����PI���ݸ�ʽ							

  PI_KP = 0;												//�Ĵ����������ͣ�int16 Q12��ʽ��PI_KP=Kp*2^12��
  PI_KI = 0;												//�Ĵ����������ͣ�int16 Q12��ʽ��PI_KI=Kp*2^12
  PI_EK = 0;												
  PI_UK = 0;												//�Ĵ����������ͣ�int16
  PI_UKMAX = 0;											//�Ĵ����������ͣ�int16
  PI_UKMIN = 0;											//�Ĵ����������ͣ�int16
}


/*******************************************************************************
* Function Name  : PI_Init
* Description    : 
* Input          : None
* Output         : 
* Return         : None
*******************************************************************************/
void Pid_SpdInit(void)
{
  pid_spd.Ref = 0;
  pid_spd.Fdb = 0;
  
//  pid_spd.Kp = SPEED_PTERM; //Q15��ʽ
//  pid_spd.Ki = SPEED_ITERM; //Q15��ʽ
  pid_spd.Err = 0;
  pid_spd.Err_Last1 = 0;
  pid_spd.Err_Err = 0;
  pid_spd.Out = 0;

  pid_spd.OutMax = SPEED_OUTMAX;
  pid_spd.OutMin = SPEED_OUTMIN;    
}

/*******************************************************************************
* Function Name  : PI_Init
* Description    : 
* Input          : None
* Output         : 
* Return         : None
*******************************************************************************/
void Pid_IsInit(void)
{
  pid_is.Ref = 0;
  pid_is.Fdb = 0;
//  pid_is.Kp = CURRENT_PTERM; //Q15��ʽ
//  pid_is.Ki = CURRENT_ITERM; //Q15��ʽ
  pid_is.Err = 0;
  pid_is.Err_Last1 = 0;
  pid_is.Err_Err = 0;
  pid_is.Out = 0;

  pid_is.OutMax = CURRENT_OUTMAX ;
  pid_is.OutMin = CURRENT_OUTMIN;
}

/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : None
* Output         : 
* Return         : None
*******************************************************************************/
s16 Pid_calc(PIDREG3 *v)   
{
//  /*ָ�����������ж�ִ��ʱ��2.5us*/
  PI_KP = v->Kp;									//�Ĵ����������ͣ�int16 Q12��ʽ��PI_KP=Kp*2^12��
  PI_KI = v->Ki;									//�Ĵ����������ͣ�int16 Q12��ʽ��PI_KI=Kp*2^12
  PI_EK = v->Err;												
  PI_UK = v->Out;									//�Ĵ����������ͣ�int16
  PI_UKMAX = v->OutMax;						//�Ĵ����������ͣ�int16
  PI_UKMIN = v->OutMin;						//�Ĵ����������ͣ�int16

  /*��ֵ����ʱ��3.2us*/	
  v->Err = v->Ref - v->Fdb;								//����PID��ǰƫ��  

  /*PIӲ������ʱ��1.8us*/
  PI_EK = v->Err;										//PI����
  PI_UK = v->Out;							  		//�Ĵ����������ͣ�int16
  SetBit(PL_CR,PISTA,1);
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();

  v->Out = PI_UK;										//PI���
  return v->Out;
}