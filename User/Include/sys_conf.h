/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        :  ���棺��ֹ�޸�,ɾ�� �ṹ�嶨�� ����ᵼ��δ֪����
********************************************************************************
/*******************************************************************************
* All Rights Reserved
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_CONF_H
#define __SYS_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "fu68xx_IQmath.h"
#include "user_conf.h"

//&& ��д  %% ֻ��  ��λ *  ����ֵ -- �޵�λ

/* define   ------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
//PWM PWM��������
#define SYSCLK_FREQ               (24000000)                    //��λ -- %% CPUFre = 24MHz
#define PWM_FREQ                  (16000)                       //��λ Hz && PWM_fre = 10kHz
#define PWM_DEADTIMENUS           (1.5)                         //��λ -- %%
                          
//-----------------------------------------------------------------------------
// PWM �͵�ƽ��Ч  FD6536 �ϡ����ŵ���Ч                                            
#define ActiveLowEnable         (0x0222)                       //��λ -- %%  ��ֹ�Ķ� �͵�ƽ��Ч
#define ActiveHighEnable        (0)                            //��λ -- %%  ��ֹ�Ķ� �ߵ�ƽ��Ч

#define H_MOSActive             (ActiveHighEnable)              //����HVIC������Ч��ƽ
#define L_MOSActive             (ActiveHighEnable)              //����HVIC������Ч��ƽ
//-----------------------------------------------------------------------------
//PWM ���Ʒ�ʽ                                                  
#define  M_Hpwm_Lon               1                             //��λ -- %% ���ŵ��� @@
#define  M_Hon_Lpwm               2                             //��λ -- %% ���ŵ��� @@
#define  M_HPWM_LPWM              3                             //��λ -- %% ����PWM������PWM 
#define  M_HLPWM_Lon              4                             //��λ -- %% �������������H
#define  M_HLPWM_Lpwm             5                             //��λ -- %% �������������PWM

#define  PWM_MODE                 (M_HLPWM_Lon)                 //��λ -- && 

//-----------------------------------------------------------------------------
//Ӳ������ ���뷽ʽ���� IPM����FD6536����FO_INT 
//���������ڲ��Ƚ�������FO#define FO_CMP          (1)           //�ڲ��Ƚ�����ΪӲ������
#define FO_INT          (2)           //�ⲿ�ź���Ϊ��Ӳ������

#define EFAL            (FO_CMP)      //��λ -- && FO_CMP FO_INT ���� ���޸�  @@

//-----------------------------------------------------------------------------
//Hallģʽ����
#define HallIC                    (0)                           //��λ -- %%  IC     @@
#define HallSensor                (1)                           //��λ -- %%  Sebsor --
#define HallMode                  (HallIC)                      //��λ --  &&

//------------------------------------------------------------------------------
//PWM
#define PWM_BITCON        (L_MOSActive*4+H_MOSActive)   //000 ����Ч   AAA ����Ч 222���ŵ� 888 ���ŵ�

#define DRV_OE_OFF        {MOE = 0;}           //��λ -- %% 
#define DRV_OE_ON         {MOE = 1;}           //��λ -- %% 

#define TPWMOUT_OFF        0x000  //��λ -- %% ��ֹ���
#define TPWMOUT_ENABLE     0x000  //��λ -- %% �������
#define TPWM_BREAK         0x888  //��λ -- %% ɲ��
#define TPWM_UH_PWM        0x001  //��λ -- %% 
#define TPWM_VH_PWM        0x010  //��λ -- %% 
#define TPWM_WH_PWM        0x100  //��λ -- %% 
#define TPWM_UL_PWM        0x004  //��λ -- %% 
#define TPWM_VL_PWM        0x040  //��λ -- %% 
#define TPWM_WL_PWM        0x400  //��λ -- %%

#define TPWM_UH_ON         0x002  //��λ -- %% 
#define TPWM_VH_ON         0x020  //��λ -- %% 
#define TPWM_WH_ON         0x200  //��λ -- %%   
#define TPWM_UL_ON         0x008  //��λ -- %% 
#define TPWM_VL_ON         0x080  //��λ -- %% 
#define TPWM_WL_ON         0x800  //��λ -- %% 

#define TPWM_ULVL_ON       0x880  //��λ -- %% 
#define TPWM_ULVLWL_ON     0x888  //��λ -- %% 

#define TPWM_ULVLWL_PWM    0x444  //��λ -- %%   
#define TPWM_UHVLWL_PWM    0x441  //��λ -- %% 

#define TPWM_UHVL_ON       0x082  //��λ -- %% 
#define TPWM_UHWL_ON       0x802  //��λ -- %% 
#define TPWM_VHUL_ON       0x028  //��λ -- %% 

#if (PWM_MODE == M_HPWM_LPWM)
  #define TUVW_OFF     0x0000
  #define TUH_VL       0x0041
  #define TUH_WL       0x0401
  #define TVH_WL       0x0410
  #define TVH_UL       0x0014
  #define TWH_UL       0x0104
  #define TWH_VL       0x0140
  #define TULVLWL_ON   0x0888
#elif (PWM_MODE == M_Hon_Lpwm)
  #define TUVW_OFF     0x0000
  #define TUH_VL       0x0042
  #define TUH_WL       0x0402
  #define TVH_WL       0x0420
  #define TVH_UL       0x0024
  #define TWH_UL       0x0204
  #define TWH_VL       0x0240
  #define TULVLWL_ON   0x0888
#elif (PWM_MODE == M_Hpwm_Lon)           
  #define TUVW_OFF     0x0000
  #define TUH_VL       0x0018
  #define TUH_WL       0x0108
  #define TVH_WL       0x0180
  #define TVH_UL       0x0081
  #define TWH_UL       0x0801
  #define TWH_VL       0x0810
  #define TULVLWL_ON   0x0888
#elif (PWM_MODE == M_HLPWM_Lon)   
  #define TUVW_OFF     0x0000
  #define TUH_VL       0x0085
  #define TUH_WL       0x0805
  #define TVH_WL       0x0850
  #define TVH_UL       0x0058
  #define TWH_UL       0x0508
  #define TWH_VL       0x0580
  #define TULVLWL_ON   0x0888  
#elif (PWM_MODE == M_HLPWM_Lpwm)   
  #define TUVW_OFF     0x0000
  #define TUH_VL       0x0045
  #define TUH_WL       0x0405
  #define TVH_WL       0x0450
  #define TVH_UL       0x0054
  #define TWH_UL       0x0544
  #define TWH_VL       0x0540
  #define TULVLWL_ON   0x0888  
#endif
  
  
#define PWMOUT_OFF        {TIM1_DBR = (TPWMOUT_OFF^PWM_BITCON);}      //��λ -- %% ��ֹ���
#define PWMOUT_ENABLE     {TIM1_DBR = (TPWMOUT_ENABLE^PWM_BITCON);}   //��λ -- %% �������
#define PWM_BREAK         {TIM1_DBR = (TPWM_BREAK^PWM_BITCON);}       //��λ -- %% ɲ��

#define PWM_UH_PWM        {TIM1_DBR = (TPWM_UH_PWM^PWM_BITCON);}      //��λ -- %% 
#define PWM_VH_PWM        {TIM1_DBR = (TPWM_VH_PWM^PWM_BITCON);}      //��λ -- %% 
#define PWM_WH_PWM        {TIM1_DBR = (TPWM_WH_PWM^PWM_BITCON);}      //��λ -- %% 
#define PWM_UL_PWM        {TIM1_DBR = (TPWM_UL_PWM^PWM_BITCON);}      //��λ -- %% 
#define PWM_VL_PWM        {TIM1_DBR = (TPWM_VL_PWM^PWM_BITCON);}      //��λ -- %% 
#define PWM_WL_PWM        {TIM1_DBR = (TPWM_WL_PWM^PWM_BITCON);}      //��λ -- %%

#define PWM_UH_ON         {TIM1_DBR = (TPWM_UH_ON^PWM_BITCON);}       //��λ -- %% 
#define PWM_VH_ON         {TIM1_DBR = (TPWM_VH_ON^PWM_BITCON);}       //��λ -- %% 
#define PWM_WH_ON         {TIM1_DBR = (TPWM_WH_ON^PWM_BITCON);}       //��λ -- %%   
#define PWM_UL_ON         {TIM1_DBR = (TPWM_UL_ON^PWM_BITCON);}       //��λ -- %% 
#define PWM_VL_ON         {TIM1_DBR = (TPWM_VL_ON^PWM_BITCON);}       //��λ -- %% 
#define PWM_WL_ON         {TIM1_DBR = (TPWM_WL_ON^PWM_BITCON);}       //��λ -- %% 

#define PWM_ULVLWL_ON     {TIM1_DBR = (TPWM_ULVLWL_ON^PWM_BITCON);}   //��λ -- %% 
#define PWM_ULVLWL_PWM    {TIM1_DBR = (TPWM_ULVLWL_PWM^PWM_BITCON);}  //��λ -- %%   
#define PWM_UHVLWL_PWM    {TIM1_DBR = (TPWM_UHVLWL_PWM^PWM_BITCON);}  //��λ -- %% 

#define PWM_ULVL_ON       {TIM1_DBR = (TPWM_ULVL_ON^PWM_BITCON);}     //��λ -- %% 
#define PWM_UHVL_ON       {TIM1_DBR = (TPWM_UHVL_ON^PWM_BITCON);}     //��λ -- %% 
#define PWM_UHWL_ON       {TIM1_DBR = (TPWM_UHWL_ON^PWM_BITCON);}     //��λ -- %% 
#define PWM_VHUL_ON       {TIM1_DBR = (TPWM_VHUL_ON^PWM_BITCON);}     //��λ -- %% 

#define UVW_OFF           (TUVW_OFF^PWM_BITCON) 
#define UH_VL             (TUH_VL^PWM_BITCON)
#define UH_WL             (TUH_WL^PWM_BITCON)
#define VH_WL             (TVH_WL^PWM_BITCON)
#define VH_UL             (TVH_UL^PWM_BITCON)
#define WH_UL             (TWH_UL^PWM_BITCON)
#define WH_VL             (TWH_VL^PWM_BITCON)
#define ULVLWL_ON         (TULVLWL_ON^PWM_BITCON)

#endif
/* Exported constants --------------------------------------------------------*/
#include "constant.h"
#include "tempconstant.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __HD_init_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/
