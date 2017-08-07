/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        :  警告：禁止修改,删除 结构体定义 否则会导致未知错误
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

//&& 读写  %% 只读  单位 *  标幺值 -- 无单位

/* define   ------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
//PWM PWM参数配置
#define SYSCLK_FREQ               (24000000)                    //单位 -- %% CPUFre = 24MHz
#define PWM_FREQ                  (16000)                       //单位 Hz && PWM_fre = 10kHz
#define PWM_DEADTIMENUS           (1.5)                         //单位 -- %%
                          
//-----------------------------------------------------------------------------
// PWM 低电平有效  FD6536 上、下桥低有效                                            
#define ActiveLowEnable         (0x0222)                       //单位 -- %%  禁止改动 低电平有效
#define ActiveHighEnable        (0)                            //单位 -- %%  禁止改动 高电平有效

#define H_MOSActive             (ActiveHighEnable)              //上桥HVIC驱动有效电平
#define L_MOSActive             (ActiveHighEnable)              //下桥HVIC驱动有效电平
//-----------------------------------------------------------------------------
//PWM 调制方式                                                  
#define  M_Hpwm_Lon               1                             //单位 -- %% 上桥调制 @@
#define  M_Hon_Lpwm               2                             //单位 -- %% 下桥调试 @@
#define  M_HPWM_LPWM              3                             //单位 -- %% 上桥PWM，下桥PWM 
#define  M_HLPWM_Lon              4                             //单位 -- %% 互补输出，下桥H
#define  M_HLPWM_Lpwm             5                             //单位 -- %% 互补输出，下桥PWM

#define  PWM_MODE                 (M_HLPWM_Lon)                 //单位 -- && 

//-----------------------------------------------------------------------------
//硬件保护 输入方式设置 IPM或者FD6536设置FO_INT 
//其他设置内部比较器触发FO#define FO_CMP          (1)           //内部比较器作为硬件过流
#define FO_INT          (2)           //外部信号作为，硬件保护

#define EFAL            (FO_CMP)      //单位 -- && FO_CMP FO_INT 参数 可修改  @@

//-----------------------------------------------------------------------------
//Hall模式配置
#define HallIC                    (0)                           //单位 -- %%  IC     @@
#define HallSensor                (1)                           //单位 -- %%  Sebsor --
#define HallMode                  (HallIC)                      //单位 --  &&

//------------------------------------------------------------------------------
//PWM
#define PWM_BITCON        (L_MOSActive*4+H_MOSActive)   //000 高有效   AAA 地有效 222上桥低 888 下桥低

#define DRV_OE_OFF        {MOE = 0;}           //单位 -- %% 
#define DRV_OE_ON         {MOE = 1;}           //单位 -- %% 

#define TPWMOUT_OFF        0x000  //单位 -- %% 禁止输出
#define TPWMOUT_ENABLE     0x000  //单位 -- %% 允许输出
#define TPWM_BREAK         0x888  //单位 -- %% 刹车
#define TPWM_UH_PWM        0x001  //单位 -- %% 
#define TPWM_VH_PWM        0x010  //单位 -- %% 
#define TPWM_WH_PWM        0x100  //单位 -- %% 
#define TPWM_UL_PWM        0x004  //单位 -- %% 
#define TPWM_VL_PWM        0x040  //单位 -- %% 
#define TPWM_WL_PWM        0x400  //单位 -- %%

#define TPWM_UH_ON         0x002  //单位 -- %% 
#define TPWM_VH_ON         0x020  //单位 -- %% 
#define TPWM_WH_ON         0x200  //单位 -- %%   
#define TPWM_UL_ON         0x008  //单位 -- %% 
#define TPWM_VL_ON         0x080  //单位 -- %% 
#define TPWM_WL_ON         0x800  //单位 -- %% 

#define TPWM_ULVL_ON       0x880  //单位 -- %% 
#define TPWM_ULVLWL_ON     0x888  //单位 -- %% 

#define TPWM_ULVLWL_PWM    0x444  //单位 -- %%   
#define TPWM_UHVLWL_PWM    0x441  //单位 -- %% 

#define TPWM_UHVL_ON       0x082  //单位 -- %% 
#define TPWM_UHWL_ON       0x802  //单位 -- %% 
#define TPWM_VHUL_ON       0x028  //单位 -- %% 

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
  
  
#define PWMOUT_OFF        {TIM1_DBR = (TPWMOUT_OFF^PWM_BITCON);}      //单位 -- %% 禁止输出
#define PWMOUT_ENABLE     {TIM1_DBR = (TPWMOUT_ENABLE^PWM_BITCON);}   //单位 -- %% 允许输出
#define PWM_BREAK         {TIM1_DBR = (TPWM_BREAK^PWM_BITCON);}       //单位 -- %% 刹车

#define PWM_UH_PWM        {TIM1_DBR = (TPWM_UH_PWM^PWM_BITCON);}      //单位 -- %% 
#define PWM_VH_PWM        {TIM1_DBR = (TPWM_VH_PWM^PWM_BITCON);}      //单位 -- %% 
#define PWM_WH_PWM        {TIM1_DBR = (TPWM_WH_PWM^PWM_BITCON);}      //单位 -- %% 
#define PWM_UL_PWM        {TIM1_DBR = (TPWM_UL_PWM^PWM_BITCON);}      //单位 -- %% 
#define PWM_VL_PWM        {TIM1_DBR = (TPWM_VL_PWM^PWM_BITCON);}      //单位 -- %% 
#define PWM_WL_PWM        {TIM1_DBR = (TPWM_WL_PWM^PWM_BITCON);}      //单位 -- %%

#define PWM_UH_ON         {TIM1_DBR = (TPWM_UH_ON^PWM_BITCON);}       //单位 -- %% 
#define PWM_VH_ON         {TIM1_DBR = (TPWM_VH_ON^PWM_BITCON);}       //单位 -- %% 
#define PWM_WH_ON         {TIM1_DBR = (TPWM_WH_ON^PWM_BITCON);}       //单位 -- %%   
#define PWM_UL_ON         {TIM1_DBR = (TPWM_UL_ON^PWM_BITCON);}       //单位 -- %% 
#define PWM_VL_ON         {TIM1_DBR = (TPWM_VL_ON^PWM_BITCON);}       //单位 -- %% 
#define PWM_WL_ON         {TIM1_DBR = (TPWM_WL_ON^PWM_BITCON);}       //单位 -- %% 

#define PWM_ULVLWL_ON     {TIM1_DBR = (TPWM_ULVLWL_ON^PWM_BITCON);}   //单位 -- %% 
#define PWM_ULVLWL_PWM    {TIM1_DBR = (TPWM_ULVLWL_PWM^PWM_BITCON);}  //单位 -- %%   
#define PWM_UHVLWL_PWM    {TIM1_DBR = (TPWM_UHVLWL_PWM^PWM_BITCON);}  //单位 -- %% 

#define PWM_ULVL_ON       {TIM1_DBR = (TPWM_ULVL_ON^PWM_BITCON);}     //单位 -- %% 
#define PWM_UHVL_ON       {TIM1_DBR = (TPWM_UHVL_ON^PWM_BITCON);}     //单位 -- %% 
#define PWM_UHWL_ON       {TIM1_DBR = (TPWM_UHWL_ON^PWM_BITCON);}     //单位 -- %% 
#define PWM_VHUL_ON       {TIM1_DBR = (TPWM_VHUL_ON^PWM_BITCON);}     //单位 -- %% 

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
