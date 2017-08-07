
/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        : ���棺��ֹ�޸�,ɾ�� �ṹ�嶨�� ����ᵼ��δ֪����
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
  MOTOR_INIT       = 1,     //��ʼ��  1
  MOTOR_STOP       = 2,     //ֹͣ    2
  MOTOR_READY      = 3,     //׼��    3
  MOTOR_STRACK     = 4,     //ת�ٸ���4
  MOTOR_PRECHARGE  = 5,     //���    5
  MOTOR_ALIGNMENGT = 6,     //��λ    6
  MOTOR_OPENLOOP   = 7,     //����    7
  MOTOR_NORMAL     = 8,     //����    8
  MOTOR_FAILURE    = 9      //����    9
}Status_TypeDef;

typedef enum
{ 
    NONE      = 0,          //�޹���           0
    E_FAIL    = 1,          //ģ�鱣��         1
    E_OC      = 2,          //��������         2
    E_OL      = 3,          //���ر���         3
    E_OV      = 4,          //��ѹ����         4
    E_UV      = 5,          //Ƿѹ����         5
    E_STA     = 6,          //��תʧ�ٱ���     6 
    E_STB1    = 7,          //����ʧ�ٹ���1    7 
    E_STB2    = 8,          //����ʧ�ٹ���2    8 
    E_STB3    = 9,          //����ʧ�ٹ���2    9 
    E_HALL    = 10,          //HALL���߹���    10
    E_QEP     = 11,         //����������       11
    E_OH1     = 12,         //���ʹܹ��±���   12
    E_OH2     = 13,         //������±���     13
    E_OH3     = 14,         //��ع��±���     14
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
   __IO u16 FoCounter;     //FO����
   __IO u16 ReCounter;     //FO 
  }CBCC_TypeDef;

//CTL �����ж�
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
    __IO u8 Value;                    //���ص���������������־
    __IO u8 msFlag;                   //�������ms��־  
  }OL_TypeDef;
//CTL ������������  ����
typedef struct
  {

    __IO u8  FlagCurrentLimit;
    
    __IO u8  u8ReNum;                  //������������
    __IO u16 u16nmsCount;              //���������ȴ�ʱ��
    __IO u16 u16Runms;                 //���������ʶʱ��
    __IO u8  ReFlag;                   //������ʶ    
  }OC_TypeDef;

typedef struct
  {
    __IO u8 ImeasBus;
    __IO u8 Counter;                    //���ص���������������־
    __IO u8 Flag;                       //�������ms��־  
    __IO s8 Num;                        //�������ms��־  
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
  __IO u16      WaitReatartNms;   //�ȴ�Nms����
  __IO u16      u16NormalRunms;   //��ת����ʱ����ʱ�䣬���Խ����ת״̬��
  __IO u8       u8Num;            //������ת����
  __IO u8       u8FL;             //��ת״̬
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
    __IO s8    cpmode;        //����ģʽ
    __IO s16   cptimSta;      //�϶�ʱ��
    __IO s16   cptimEnd;      //�϶�ʱ��
    __IO s16   cptimstep;
    _iq        cpDutySta;
    _iq        cpDutyEnd;
    _iq        cpDutystep;
    __IO s16   cpNms;          //����ʱ��
    __IO s16   cpNmsCount;     //�����ʱ��
    __IO s16   cpNumA;         //б���϶�����
    __IO s16   cpNumB;         //б������϶�����
    __IO s16   cpFinalNumB;    //б����ɺ��жϴ���
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
    __IO u16 u16Num;         //��������
    __IO u8  IRQ;            //BEMF�ж�
    __IO u8  Cheak_EN;       //���ʹ��
    __IO u8  Cheak_FL;       //��⵽��־
    __IO u8  IRQCmd ;        //��������ж�
    __IO u8  CmpOut;         //60�ȵ�Ƕ�
    __IO u16 MaskAngle;      //���νǶ� 
    __IO u16 MaskTime;
    __IO u16 CTAngle;        //����Ƕ�
    __IO u8  SPItest;        //SPI�ӿڲ���

  }BEMF_TypeDef; 
//CTL
typedef struct
  {
    __IO u16 u16PowerOnNms;    //�ϵ�ȴ�ʱ��
    __IO u16 u16chargeNms;     //���ʱ��
    __IO u16 OnOffnms;         //ON/OFFʱ��
    __IO u16 u16BrankwaitNms;  //ɲ���ȴ�ʱ��
    __IO u16 NoOperationDelaynms; //No operation time delay
    __IO u16 LED_OnOffms;      //LED ON/OFFʱ��
    __IO u8  LED_Cunter;       //LED��˸����
    __IO u16 LED_msCunter;     //LED��˸����
    __IO u16 UVnms;            //��ѹ�ж�ʱ��
    __IO u16 OVnms;            //Ƿѹ�ж�ʱ��
    __IO u16 Nonms;            //��ѹ�ָ��ж�ʱ��
    __IO u16 STAnms;           //��ת�ж�ʱ��
    __IO u16 STB1nms;          //ʧ���ж�ʱ��1
    __IO u16 STB2nms;          //ʧ���ж�ʱ��2
    __IO s16 OCnms;            //�����ж�ʱ��
    __IO s16 OH1nms;           //�����ж�ʱ��1
    __IO s16 OH1REnms;         //���Ȼָ��ж�ʱ��1
    __IO s16 OH2nms;           //���Ȼָ��ж�ʱ��2
    __IO s16 OH2REnms;         //�����ж�ʱ��2
    __IO s16 OH3nms;           //���Ȼָ��ж�ʱ��3
    __IO s16 OH3REnms;         //�����ж�ʱ��3
    __IO s16 NOloadCounter;    //�����ж�
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
    s8  SwitchCount;      //����������
    s8  SpeedShift;           //��λ
    u16 IncValue;             //����ֵ
    u16 DecValue;             //����ֵ
    u16 refTar;               //Ŀ��ֵ
    u16 refCur;               //��ǰ����ֵ
    u16 rpm;                  //�ٶȷ���
    u16 rpmavg;               //�ٶȷ���ƽ��ֵ
    s32 ComNum;               //���������
    s32 MechCircleNum;        //��еȦ�� 
    u8  RotorPosition ;       //ת��λ��
    u8  RotorPositionqPre;    //ǰһʱ��ת��λ��
   
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
    __IO u8 Start;                         //��ͣ
    __IO u8 direction;                     //���з���
    __IO u8 PowerOn;                       //�ϵ��־  0X7F �Ѿ��ϵ�
    __IO s8 Step;                          //
    __IO s8 StepPre;                       //
    __IO u8 FnStopmodeC;                   //ͣ��ģʽ 
    __IO Status_TypeDef State;             //ϵͳ״̬
    __IO Error_TypeDef  SysError;          //���ϴ���
    __IO CBCC_TypeDef Cbcc;                //FO                  
    __IO E_MESSSAGE_TypeDef RD_message;    //����������Ϣ
    __IO E_MESSSAGE_TypeDef  E_message;    //����������Ϣ
    __IO MOTOR_Params   Motor;             //�������

    SECTION_TypeDef     Section;           //����
    __IO spd_TypeDef    spd;               //�ٶȼ���
    __IO Is_TypeDef     Is;                //����
    __IO Tim_TypeDef    Tim;               //Tim

    __IO Stall_TypeDef  Stall;             //ת�ٸ���
    Alig_TypeDef        Alig;              //��λ
    Ramp_TypeDef        Ramp;              //�϶�
    BEMF_TypeDef        Bemf;              //������
   
    OL_TypeDef OL;                         //���ر���
    OC_TypeDef OC;                         //��������
    NoLoad_TypeDef Noload;                 //�����ж�

    __IO u8  counterCtrl;
    __IO u8  counterCurrent;       
    __IO u8  counterSpeed ;
    __IO u8  numTicksPerCtrl;      
    __IO u8  numTicksPerCurrent;  
    __IO u8  numTicksPerSpeed;  
  } MCL_TypeDef;
  extern MCL_TypeDef xdata Ctl;     //ȫ�ֱ�������
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void MCL_MotorC(void);     //ȫ���ⲿ��������
extern void MCL_BKIN_IRQHandler(void);
extern void MainISR(void);        //ȫ���ⲿ��������
#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2014 FT *****END OF FILE****/
