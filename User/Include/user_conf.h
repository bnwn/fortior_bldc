
/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        : ���棺��ֹ�޸�,ɾ�� �ṹ�嶨�� �ᵼ��δ֪����
********************************************************************************
/*******************************************************************************
* All Rights Reserved
*******************************************************************************/

#ifndef __USER_CONF_H
#define __USER_CONF_H

//&& ��д  %% ֻ��  ��λ *  ����ֵ -- �޵�λ
//_IQ15 ��С�ֱ��� 0.0000306 ��Χ-0.9999 ~0.9999
//------------------------------------------------------------------------
//ͣ����ʽ                
#define FREE_DOWN           (0xF1)              //��λ-- %%  ����ͣ��
#define SLOWING_DOWN        (0xF2)              //��λ-- %%  ����ͣ��   û�в���
#define BREAK_DOWN          (0xF3)              //��λ-- %%  ɲ��
#define BREAK_DOWNWALTNMS   (50)               //��λ-- &&  ɲ������ʱ�� ����ɲ��Nms ������������
#define BREAK_VALUE         _IQ(1.0)            //��λ-- &&  ɲ��ǿ�� 0.0~1.0 
#define STOPMODE            (FREE_DOWN)      //��λ-- && 

//�Ծٵ��ݳ���������                          //��λ-- && ���ų���ģʽ����Ҫ�����
#define CHARGEDUTY          _IQ(0.5)            //��λ** && ���ռ�ձ�
#define CHARGENMS           (0)                 //��λ-- &&  ���ʱ��

//�ϵ�ȴ�ʱ��
#define POWER_ON_NMS        (100)               //��λms && �ϵ�ȴ�ʱ��100ms 500ms 
//======================================================================
//λ�÷���ģʽ 
#define SENSORLESS        1                //��λ-- %% �޸�ģʽ
#define HALLSENSOR        2                //��λ-- %% HALLλ�ô��������λ��
#define POSITION_FB_MODE  SENSORLESS       //��λ-- && λ�÷�����ⷽʽ

//======================================================================
//----------------------------------------------------------------------
//HALLSENSOR ����������
//hall��װ��ʽ
#define HALLPTDPE        (0)                 //��λ-- && hall �ڲ�����ʹ��
#define DEGREES_120      (0)                 //��λ-- %% hall 120�Ȱ�װģʽ
#define DEGREES_60       (1)                 //��λ-- %% hall 60�Ȱ�װģʽ
#define HALL_SENSORS_PLACEMENT DEGREES_120   //��λ-- ѡ��

//HALLADVANCEEANGLE ���÷�Χ��-10~-50 ����0~30������ 
//1������ǰ����  ���÷�Χ-10~-50�ȳ�ǰ��   0~30 Ϊ�ͺ���
//2�����ó�ǰ����ʱ�����������������У������HALL��
//3������Ctl.direction == CW(��ת)ʱ ����HALL˳��Ϊ Drv.Hall.Section 1->2->3->4->5->6->1����
#define HALLADVANCEFIX    (0)               //������ǰ�������������в��������޸Ĵ˲��� 1 or 0
#define HALLADVANCEEANGLE (0)               //��λ�� && HALL��װ�Ƕȵ��� hall Advance Eangle  

//HALLSENSOR ��������������
//======================================================================
//----------------------------------------------------------------------
//SENSORLESS����������
//��HALL����ģʽ �ȴ� ���� ����ģʽ   ������ڴ˹��������У����������һ������
#define NO_WAIT           0                //��λ-- %% �޵ȴ�
#define WAIT_STRACK       4                //��λ-- %% ת�ٸ���
#define WAIT_PRECHARGE    5                //��λ-- %% ���
#define WAIT_ALIGNMENGT   6                //��λ-- %% ��λ
#define WAIT_RAMPUP       7                //��λ-- %% �϶�
#define WAIT_STEP         NO_WAIT          //��λ-- && �ȴ�״̬
//MOSI �����   NSS���ι�����ź�
#define BEMF_TEST         (1)              //��λ-- && BEMF�����ź����ʹ�� 
//----------------------------------------------------------------------
//ת�ٸ�������
#define STRACK_EN          (2)              //��λ-- &&ת�ٸ�������ʹ�� 1��ת�ȴ�  2��ת�Զ�ɲ��  
#define STKNMS             (30)             //��λms ת�ٸ��ټ��ʱ��
#define SRKBNUM            (5)              //��λ-- ת�ٸ��ټ�����
//----------------------------------------------------------------------
//��λ��������     ��Gģʽ2 20 5 10 10000 10000
#define ALIGNMENTNMS      (0)              //��λms ��λʱ��                
#define ALIGNMENT_DUTY    _IQ(0.05)         //��λms ��λ����            
//Ramp Up�������� 
#define RAMP_MODE         (1)              //��λ-- &&  pamp ģʽ   1 2 3
#define PAMP_PWM_FREQ     (8000)           //��λHz &&  ����Ƶ��          
#define RAMP_TIM_STA      (15)             //��λms &&  ���¿�ʼ����ʱ�䣬 
#define RAMP_TIM_END      (8)              //��λms &&  ���½�������ʱ�䣬     
#define RAMP_TIM_STEP     (35)             //��λms &&  ���²���ʱ��ݼ������� 
#define RAMP_DUTY_STA     _IQ(0.2)      //��λ* &&   ���¿�ʼ����   
#define RAMP_DUTY_END     _IQ(0.22)       //��λ* &&   ���½�������   
#define RAMP_DUTY_INC     _IQ(0.01)        //��λ*  &&  ���²�����������
#define RAMP_STEP_COUNTER  (5)             //��λ-- &&  ���½�����ά�ֲ���  pamp ģʽ 2��Ч

#define RampMaskTime      (0.1)            //��λms &&  ��������ʱ��
#define RampNumFail       (2)              //��λ-- &&  
#define RampDetecBEMFCnt  (100)             //��λ-- &&  �������BEMF��������
#define RampDetecBEMFCntFilt (50)           //��λ-- &&  ����������BEMF��������
//�����������
#define MASK_ANGLE        (0)              //��λ�� && �������νǶȣ���λ��
#define DELAY_ANGLE       (0)              //��λ�� && ������ǽǶȣ���λ�� 

//----------------------------------------------------------------------
#define CMPSAME_EN        (2)              //��λ-- TIM2�����Ƚ�������ʹ�� 0ʧ�� 1ʹ�� 2ʹ��+�л�  ��������PWM�ߵ�ƽ�м�λ��
#define CMPSAMESWITCH     (RAMP_DUTY_END+_IQ(0.0))  //��λ* && ����ģʽ�л���ֵ
//SENSORLESS��������������
//======================================================================
//���ٷ�ʽ �����������constant.h�ļ�
#define  ADCSREF_EN         (0)               //��λ-- &&ģ�����ʹ��
#define  PWMINSREF_EN       (1)               //��λ-- &&PWMIN����ʹ��

#define  ADCONOFF_EN        (0)               //��λ-- && SREF����ONOFFʹ��
#define  PWMINONOFF_EN      (1)               //��λ-- && PWMIN������ͣ
#define  KEYONOFF_EN        (0)               //��λ-- && Key/���� ����ONOFFʹ��   1 �ᴥʽ���� 2�����ǿ���
//----------------------------------------------------------------------
//�����ջ�����  �������ڻ�
#define  CURRENT_LIMIT_EN   (0)                //��λ-- && ��������ʹ�� 
#define  CURRENT_LIMIT_MAXREF (35)            //��λA  && ���Ƶ���

#define  CURRENT_CLOSE_EN   (0) 
#define  CURRENT_CTL_CNT    (3)                  //��λ-- ��������Ƶ�ʼ�����
#define  CURRENT_PTERM      _IQ(300.0/32767.0)   //��λ* ������kp
#define  CURRENT_ITERM      _IQ(50.0/32767.0)    //��λ* ������ki
#define  CURRENT_INMAX      _IQ(3000.0/32767.0)  //��λ* �������������޷�ֵ

#define  CURRENT_OUTMIN     (_IQ(8000.0/32767.0))//��λ* ����������޷�
#define  CURRENT_OUTMAX     (_IQ(1.0))             //��λ* ����������޷�
//----------------------------------------------------------------------
//�ٶȿ���  
#define  SPEED_CALC_EN      (0)                //��λ-- &&ת�ټ���ʹ�� ʧ���Ż�����ʱ�� 0->������   1->����ֵ  2->����ֵ+ʵ��ת��
#define  SPEED_CLOSE_EN     (0)                //��λ-- �ٶȱջ�ʹ��
#define  SPEED_CTL_CNT      (20)               //��λ-- �ٶȵ���Ƶ�ʼ�����
#define  SPEED_PTERM        _IQ(20.0/32767.0)  //��λ* �ٶȻ�kp
#define  SPEED_ITERM        _IQ(50.0/32767.0)  //��λ* �ٶȻ�ki
#define  SPEED_OUTMIN       _IQ(8000.0/32767.0)//��λ* �ٶȻ� 
#define  SPEED_OUTMAX       _IQ(1.0)           //��λ* �ٶȻ� 

#define  SPEED_REF_TAR      _IQ(0.5)           //��λ* ����Ŀ���ٶ� Ĭ��ֵ     �ٶȱջ� 
#define  SPEED_REF_INIT     _IQ(0.001)         //��λ* ����Ŀ���ٶ� ��ʼֵ     �ٶȱջ� 
//����
#define  MOTOR_TARGRT_DUTY   _IQ(0.1)          //��λ* ����Ŀ��ռ�ձ� Ĭ��ֵ   �ٶȿ�������
#define  MOTOR_INIT_DUTY     _IQ(0.01)         //��λ* HALLģʽ��ʼռ�ձ�      �ٶȿ�������

#define  SPEED_INCVALUE     (500)               //��λ* �������²������� ÿ100us     100
#define  SPEED_DECVALUE     (500)               //��λ* �������²������� ÿ100us     100

//----------------------------------------------------------------------
//����޷�
#define  MOTOR_VS_MAX        _IQ(1.0)      //��λ*   ������ռ�ձ�
#define  MOTOR_VS_MIN        _IQ(0.01)      //��λ*   ��С���ռ�ձ�
//======================================================================
//----------------------------------------------------------------------
//���Ϻͱ�����������  ע�⣺��λ�÷��� һ���ת��������Ϊ����1000ms�� ʧ�ٱ����ر�
//��תʧ�ٱ���
#define  STA_EN              (1)            //��ת����ʹ��
#define  STANMS              (15)           //��λms  ��ת����ʱ��  

#define  STB1_EN             (1)            //���ٱ���ʹ��
#define  STB1SPEED           (300000)        //��λrpm &&  
#define  STB1NMS             (100)          //��λms  ʧ�ټ��ʱ��

#define  STB2_EN             (1)            //���ٱ���ʹ��
#define  STB2SPEED           (500)          //��λrpm &&  
#define  STB2NMS             (100)          //��λms  ʧ�ټ��ʱ��

#if (POSITION_FB_MODE == SENSORLESS)
  #define  STB3_EN             (0)             //ʧ�ٱ���ʹ��
#else
  #define  STB3_EN             (0)             //��HALL�ر� �ٶ�3���
#endif

#define  STB3WAIT            (100)             //����3
#define  SRB3TIMEFILT        (20)              //StepTime�˲�ֵ
#define  STB3ERRVALUE        (20)              //������
  
//��ת������������  STA_EN  STB1_EN  STB2_EN STB3_EN ���Ͼ��Զ�������ϣ�����                
#define  STALLRESTART_EN     (1)           //��λ-- && ��ת��������ʹ��  
#define  STALLRESTARTNUM     (1)         //��λ-- && ��ת��������   
#define  STALLRESTARTTIM     (1)           //��λ1ms ��ת�����ӳ�ʱ�� 
//----------------------------------------------------------------------
//Ӳ������ FO�����������ر����
#define  HARD_OC_EN          (0)           //��λ- ʹ��Ӳ������    ��ֹ�ر�
//������ ʹ����������ȡ��Ӳ���������� cycle  by  cycle  current protection
//0 ȡ����������Ӳ��FOֱ�ӱ���  1 ����CBCCP_NUM��FO�źű��� 2���ᱨ������ֻ����
//��ѹһ�㲻���������� ��֤�˹�������
#define  CBCCP_EN            (0)           //��λ- && ������ʹ�� 
#define  CBCCP_NUM           (100)         //��λ- && ������ʹ�� 
//����������������
#define  IBUS_CALC_EN        (0)           //��λ-  ʧ�ܣ�����رգ���Ӱ���������
#define  OVERCURRENT_EN      (0)           //��λ-  ��������
#define  OVERCURRENT         (60)          //��λA  ����ֵ
#define  OCNMS               (4)           //��λms �������ʱ��

//����������������                         
#define  OCRESTART_EN        (1)           //��λ- && ��������ʹ��  ����Ӳ������ ������� ����
#define  OCRESTARTNUM        (50)           //��λ* && ĸ�߹�����������
#define  OCRESTARTTIM        (5)           //��λms && ���������ӳ�ʱ��

//----------------------------------------------------------------------
//��ѹ��Ƿѹ������������ 
#define  VBUS_CALC_EN        (1)           //��λ-  ʧ��,����رգ���Ӱ���Ƿѹ���� AD2
#define  OVERVOLTAGE_EN      (0)           //��λ-  ��ѹ����ʹ��  
#define  UNDERVOLTAGE_EN     (0)           //��λ-  Ƿѹ����ʹ��
#define  VBUSRECOVER_EN      (0)           //��λ-  ĸ�ߵ�ѹ�ָ�����ʹ��

#define  DCVOLTAGE           (36.0)        //��λV   ������������ѹ
#define  OVERVOLTAGE         (80.0)        //��λV   ��ѹ������ѹ    //(DCVOLTAGE*1.2) 
#define  UNDERVOLTAGE        (10.0)        //��λV   Ƿѹ������ѹ    //(DCVOLTAGE*0.8)  
#define  OVREERVOLTAGE       (65.0)        //��λV   �ز��ѹ        //(DCVOLTAGE*1.15)
#define  UNREDERVOLTAGE      (12.0)        //��λV   �ز��ѹ        //(DCVOLTAGE*0.85) 
#define  UVNMS               (500)         //��λms  ĸ�߹�ѹ�ж�ʱ�䣬
#define  OVNMS               (500)         //��λms  ĸ��Ƿѹ�ж�ʱ��
#define  NONMS               (500)         //��λms  ĸ�߻ָ��ж�ʱ��

//----------------------------------------------------------------------
//���ȱ���
#define  OH1_EN              (0)           //��λ- ����ʹ��
#define  OH2_EN              (0)           //��λ- ����ʹ��                        
#define  OH3_EN              (0)           //����ʹ��              
#define  OHRE_EN             (0)           //��λ- �ָ�����
#define  OH1NMS              (5000)        //��λ- ���ȼ��ʱ�� OH1
#define  OH2NMS              (5000)        //��λ- ���ȼ��ʱ�� OH2

//======================================================================

//����������� ���ѡ��
#define  MOTOR_USER_CP       001   //�ͻ���Ʒ��������  
//...
#define  MOTOR_VERSION       MOTOR_USER_CP   //���ѡ��

//����ѡ�� ���Ӳ���ѡ��
#define  FU68xx_USER_CP      001   //�ͻ���Ʒ�����
#define  FU6831_XQ_DDGJ      101   //20.0   2.0   0.002  30.0  1.0
#define  FU68xx_ZY_DEMO      107   //20.0   2.0   0.002  51.0  2.0 
#define  FU6811_FD6536_DEMO  106   //990.0  12.0  0.05   12.0  2.0 
#define  FU68xx_DT_DEMO      301   //10.0   2.0   0.001  20.0  2.0
//...
#define  BOARD_VERSION       FU68xx_USER_CP    //����ѡ��

//�������� �������趨  ��ѹ���� ���ݰ����趨
#if (MOTOR_VERSION == MOTOR_USER_CP)
    #define POLE_PAIR     1          //��λ* ���������         Y
    #define BASE_VOLTAGE  310        //��λV ������ѹ       Y
    #define BASE_SPEED    400000       //��λrpm ����ת��*1.5 Y
    #define BASE_Rr       23.8        //��λ��   ������ӵ���     NC
    #define BASE_Ce       35.0        //��λ*   ���������ϵ��   NC
#endif
//------------------------------------------------------------------------
//The board version         

#if (BOARD_VERSION == FU68xx_USER_CP) 
    //------------------------------------------------------------------------
    //ĸ�ߵ�ѹ����
    #define RV_BUS_1 (10.0)           //��λK�� ��ѹ����    Y
    #define RV_BUS_2 (2.0)            //��λK�� ��������    Y
    //------------------------------------------------------------------------
    //��������
    #define Rs    (0.002)             //��λ��   ��������    Y
    #define RI_BUS_1   (20.0)         //��λK��  ����Ŵ������� Y
    #define RI_BUS_2   (2.0)          //��λK��  ����Ŵ������� Y
    #define IBUSOFFSET (0)   

#elif (BOARD_VERSION == FU68xx_DT_DEMO) 
    //------------------------------------------------------------------------
    //ĸ�ߵ�ѹ����
    #define RV_BUS_1 (10.0)           //��λK�� ��ѹ����    Y
    #define RV_BUS_2 (2.0)            //��λK�� ��������    Y
    //------------------------------------------------------------------------
    //��������
    #define Rs    (0.01)             //��λ��   ��������    Y
    #define RI_BUS_1   (20.0)         //��λK��  ����Ŵ������� Y
    #define RI_BUS_2   (2.0)          //��λK��  ����Ŵ������� Y
    #define IBUSOFFSET (0)  
    
#elif (BOARD_VERSION == FU68xx_ZY_DEMO) 
    //------------------------------------------------------------------------
    //ĸ�ߵ�ѹ����
    #define RV_BUS_1 (20.0)           //��λK�� ��ѹ����    Y
    #define RV_BUS_2 (1.0)            //��λK�� ��������    Y
    //------------------------------------------------------------------------
    //��������
    #define Rs    (0.002)             //��λ��   ��������    Y
    #define RI_BUS_1   (24.0)         //��λK��  ����Ŵ������� Y
    #define RI_BUS_2   (2.0)          //��λK��  ����Ŵ������� Y
    #define IBUSOFFSET (0)   

#elif (BOARD_VERSION == FU6811_FD6536_DEMO) 
    //------------------------------------------------------------------------
    //ĸ�ߵ�ѹ����
    #define RV_BUS_1 (990.0)           //��λK�� ��ѹ����    Y
    #define RV_BUS_2 (12.0)            //��λK�� ��������    Y
    //------------------------------------------------------------------------
    //��������
    #define Rs    (0.05)             //��λ��   ��������    Y
    #define RI_BUS_1   (12.0)         //��λK��  ����Ŵ������� Y
    #define RI_BUS_2   (2.0)          //��λK��  ����Ŵ������� Y
    #define IBUSOFFSET (0)            //N
#endif

#endif /*__USER_CONF_H*/

