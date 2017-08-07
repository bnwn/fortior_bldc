
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
#ifndef __MC_MOTORCOTROL_LAYER_H
#define __MC_MOTORCOTROL_LAYER_H

/* Includes ------------------------------------------------------------------*/
#include <FU68xx.h>
/* Exported types ------------------------------------------------------------*/

typedef enum
{ 
  MOTOR_NONE       = 0,     //        0
  MOTOR_INIT       = 1,     //初始化  1
  MOTOR_STOP       = 2,     //停止    2
  MOTOR_READY      = 3,     //准备    3
  MOTOR_STRACK     = 4,     //转速跟踪4
  MOTOR_PRECHARGE  = 5,     //充电    5
  MOTOR_ALIGNMENGT = 6,     //定位    6
  MOTOR_OPENLOOP   = 7,     //启动    7
  MOTOR_NORMAL     = 8,     //正常    8
  MOTOR_FAILURE    = 9      //错误    9
}Status_TypeDef;

typedef enum
{ 
    NONE      = 0,          //无故障           0
    E_FAIL    = 1,          //模块保护         1
    E_OC      = 2,          //过流保护         2
    E_OL      = 3,          //过载保护         3
    E_OV      = 4,          //过压保护         4
    E_UV      = 5,          //欠压保护         5
    E_STA     = 6,          //堵转失速保护     6 
    E_STB1    = 7,          //过速失速故障1    7 
    E_STB2    = 8,          //过速失速故障2    8 
    E_STB3    = 9,          //过速失速故障2    9 
    E_HALL    = 10,          //HALL断线故障    10
    E_QEP     = 11,         //编码器断线       11
    E_OH1     = 12,         //功率管过温保护   12
    E_OH2     = 13,         //电机过温保护     13
    E_OH3     = 14,         //电池过温保护     14
}Error_TypeDef;

 typedef struct 
  { 
    __IO u8 ErrorF;
    Error_TypeDef SysError;
    Status_TypeDef State;
    __IO u8 FR;
    u16  SpeedRef;
    u16  SpeedFdb;
    u16  ImeasBus;
    u16  VdcMeas;    
    __IO float  Therm;
    __IO float  Duty;
    __IO float  Ibus;
    __IO float  Vdc;
  } E_MESSSAGE_TypeDef ;

typedef struct
  {
   __IO u16 FoCounter;     //FO次数
   __IO u16 ReCounter;     //FO 
  }CBCC_TypeDef;

//CTL 过载判断
typedef struct
  {
    __IO s32   Nms;
    __IO s32   msCounter;
    __IO u16   Current; 
    __IO u16   flg:1; 
  }group_TypeDef;
  
typedef struct
  {
    __IO group_TypeDef Group[4];
    __IO u8 Value;                    //过载电流保护，过流标志
    __IO u8 msFlag;                   //过流检测ms标志  
  }OL_TypeDef;
//CTL 过流过载重启  过流
typedef struct
  {

    __IO u8  FlagCurrentLimit;
    
    __IO u8  u8ReNum;                  //过流重启次数
    __IO u16 u16nmsCount;              //过流重启等待时间
    __IO u16 u16Runms;                 //解除过流标识时间
    __IO u8  ReFlag;                   //重启标识    
  }OC_TypeDef;

typedef struct
  {
    __IO u8 ImeasBus;
    __IO u8 Counter;                    //过载电流保护，过流标志
    __IO u8 Flag;                       //过流检测ms标志  
    __IO s8 Num;                        //过流检测ms标志  
  }NoLoad_TypeDef;


typedef struct    
{ 
  __IO u16 S[8];  
  __IO u16 Per;
  __IO u16 Cur;
  __IO u16 Err;
  __IO s8 ErrCounter;                   //
  __IO s8 Counter;
}SECTION_TypeDef;  

//CTL  
typedef struct    
{ 
  __IO u16      WaitReatartNms;   //等待Nms重启
  __IO u16      u16NormalRunms;   //堵转重启时运行时间，用以解除堵转状态。
  __IO u8       u8Num;            //连续堵转次数
  __IO u8       u8FL;             //堵转状态
}Stall_TypeDef;  
//CTL
  
typedef struct 
  {  
    __IO _iq duty;
    __IO u16 timNms;
    __IO u16 NmsCount;
  }Alig_TypeDef;
//CTL  
typedef struct 
  { 
    __IO s8    cpmode;        //启动模式
    __IO s16   cptimSta;      //拖动时间
    __IO s16   cptimEnd;      //拖动时间
    __IO s16   cptimstep;
    _iq        cpDutySta;
    _iq        cpDutyEnd;
    _iq        cpDutystep;
    __IO s16   cpNms;          //换相时间
    __IO s16   cpNmsCount;     //换相计时器
    __IO s16   cpNumA;         //斜坡拖动次数
    __IO s16   cpNumB;         //斜坡完成拖动次数
    __IO s16   cpFinalNumB;    //斜坡完成后判断次数
    __IO u8    cpOver;

    __IO s8    cpCntErr;
    __IO s8    cpCntFail;
    __IO s8    cpNumFail;      
    __IO s8    cpCntNormal;    
    __IO u16   cpBEMFCnt;
    __IO u16   cpBEMFCntFilt;
    __IO u16   cpMaskTime;
    __IO u16   cpTimBufCur;
    __IO u16   cpTimBufPer;
  }Ramp_TypeDef;

  typedef struct
  {
    __IO u16 u16Num;         //过零点次数
    __IO u8  IRQ;            //BEMF中断
    __IO u8  Cheak_EN;       //检测使能
    __IO u8  Cheak_FL;       //检测到标志
    __IO u8  IRQCmd ;        //开启检测中断
    __IO u8  CmpOut;         //60度电角度
    __IO u16 MaskAngle;      //屏蔽角度 
    __IO u16 MaskTime;
    __IO u16 CTAngle;        //换相角度
    __IO u8  SPItest;        //SPI接口测试

  }BEMF_TypeDef; 
//CTL
typedef struct
  {
    __IO u16 u16PowerOnNms;    //上电等待时间
    __IO u16 u16chargeNms;     //充电时间
    __IO u16 OnOffnms;         //ON/OFF时间
    __IO u16 u16BrankwaitNms;  //刹车等待时间
    __IO u16 NoOperationDelaynms; //No operation time delay
    __IO u16 LED_OnOffms;      //LED ON/OFF时间
    __IO u8  LED_Cunter;       //LED闪烁次数
    __IO u16 LED_msCunter;     //LED闪烁次数
    __IO u16 UVnms;            //过压判断时间
    __IO u16 OVnms;            //欠压判断时间
    __IO u16 Nonms;            //电压恢复判断时间
    __IO u16 STAnms;           //堵转判断时间
    __IO u16 STB1nms;          //失速判断时间1
    __IO u16 STB2nms;          //失速判断时间2
    __IO s16 OCnms;            //过流判断时间
    __IO s16 OH1nms;           //过热判断时间1
    __IO s16 OH1REnms;         //过热恢复判断时间1
    __IO s16 OH2nms;           //过热恢复判断时间2
    __IO s16 OH2REnms;         //过热判断时间2
    __IO s16 OH3nms;           //过热恢复判断时间3
    __IO s16 OH3REnms;         //过热判断时间3
    __IO s16 NOloadCounter;    //空载判断
  }Tim_TypeDef;  
  
//CTL
typedef struct  
{ 
  __IO u8          PolePairs;          //!< Defines the number of pole pairs 
  __IO float       BaseVoltage;
  __IO float       BaseSpeed;
//  __IO float       Rr;                 //!< Defines the rotor resistance, ohm 
//  __IO float       Rs;                 //!< Defines the stator resistance, ohm 
//  __IO float       Ip;
//  __IO float       Ce;
//  __IO float       ratedFlux;          //!< Defines the rated flux, V*sec 
} MOTOR_Params; 

typedef struct
  { 
    s8  SwitchCount;      //启动计数器
    s8  SpeedShift;           //档位
    u16 IncValue;             //加速值
    u16 DecValue;             //减速值
    u16 refTar;               //目标值
    u16 refCur;               //当前给定值
    u16 rpm;                  //速度反馈
    u16 rpmavg;               //速度反馈平均值
    s32 ComNum;               //换相计数器
    s32 MechCircleNum;        //机械圈数 
    u8  RotorPosition ;       //转子位置
    u8  RotorPositionqPre;    //前一时刻转子位置
   
  }spd_TypeDef;

typedef struct
  { 
    u16 IncValue;
    u16 DecValue;
    u16 refTar;
    u16 refCur;
  }Is_TypeDef;
  
typedef struct
  {
    __IO u16 gIsrTicker;
    __IO u8 Start;                         //启停
    __IO u8 direction;                     //运行方向
    __IO u8 PowerOn;                       //上电标志  0X7F 已经上电
    __IO s8 Step;                          //
    __IO s8 StepPre;                       //
    __IO u8 FnStopmodeC;                   //停机模式 
    __IO Status_TypeDef State;             //系统状态
    __IO Error_TypeDef  SysError;          //故障代码
    __IO CBCC_TypeDef Cbcc;                //FO                  
    __IO E_MESSSAGE_TypeDef RD_message;    //故障锁存信息
    __IO E_MESSSAGE_TypeDef  E_message;    //故障锁存信息
    __IO MOTOR_Params   Motor;             //电机参数

    SECTION_TypeDef     Section;           //扇区
    __IO spd_TypeDef    spd;               //速度计算
    __IO Is_TypeDef     Is;                //电流
    __IO Tim_TypeDef    Tim;               //Tim

    __IO Stall_TypeDef  Stall;             //转速跟踪
    Alig_TypeDef        Alig;              //定位
    Ramp_TypeDef        Ramp;              //拖动
    BEMF_TypeDef        Bemf;              //反电势
   
    OL_TypeDef OL;                         //过载保护
    OC_TypeDef OC;                         //过流重启
    NoLoad_TypeDef Noload;                 //轻载判断

    __IO u8  counterCtrl;
    __IO u8  counterCurrent;       
    __IO u8  counterSpeed ;
    __IO u8  numTicksPerCtrl;      
    __IO u8  numTicksPerCurrent;  
    __IO u8  numTicksPerSpeed;  
  } MCL_TypeDef;
  extern MCL_TypeDef xdata Ctl;     //全局变量声明
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void MCL_MotorC(void);     //全局外部函数声明
extern void MCL_BKIN_IRQHandler(void);
extern void MainISR(void);        //全局外部函数声明
#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/
