
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

/* Includes ------------------------------------------------------------------*/
#ifndef __CONSTANT_H_
#define __CONSTANT_H_

//------------------------------------------------------------------------
//Ĭ�ϵ����ת����  
#define CW                  1              //��λ-- %% ��ת
#define CCW                 2              //��λ-- %% ��ת
// DIRECTION ���ò���Ϊ�� CW CCW 0  ��DIRECTION = 0ʱ ���Uc.flg.FR û�и�ֵ�������� 
#define DIRECTION           CW             //��λ-- && Ĭ����ת����
//------------------------------------------------------------------------
//����ѡ���ѡ�� �����Ӵ����� 
#define SETVERSIONSEN     0                //Set_Versions  
#define FAILLOGEN         1                //������Ϣ��¼          
#define FAILLAMPEN        1                //����ָʾ LED��˸  
#define FAILSTOREEN       0                //Flash ���ϴ洢     

#define MOTORCIRCLECALEEN 0                //�����תȦ������  Motor rotating ring number counting
#define LAMP_EN           (0)              //��λ-- && �綯������ʱ����ʹ��  //�޲�����ʱ����
#define NOOPDELAYNMS      (10000)          //��λms && NoOperationDelaynms

#define BEMFSETFR         (0)              //��λ-- && ���ת���趨
#define BemfSetFRRomAddress  (16132)
//------------------------------------------------------------------------
//���ر���                              
#define  OVERLOAD_EN         (0)            //��λ-  ����ʹ��
#define  OVERLOAD0           (40.1)         //��λA  ����ֵ
#define  OVERLOAD1           (42.2)         //��λA  ����ֵ
#define  OVERLOAD2           (44.3)         //��λA  ����ֵ
#define  OVERLOAD3           (46.4)         //��λA  ����ֵ
  
#define  OL0NMS              (6000)         //��λms �������ʱ��
#define  OL1NMS              (3000)         //��λms �������ʱ��
#define  OL2NMS              (1000)         //��λms �������ʱ��
#define  OL3NMS              (500)          //��λms �������ʱ��
//------------------------------------------------------------------------
//�����ж�
#define  NOLOAD_EN           (1)
#define  NOLOADCURRENT       (8.0)         //��λA 
#define  NOLOADNUM           (2)          //��λms
  
//============================================================================
//�ٶȸ��������������� ADC��PWMIN  ON/OFF 
//(X1,Y1) (X2,Y2) -->> (SPEED_REF_MAX,ADCSREFINMAX)  (SPEED_REF_MIN,ADCSREFINMIN) 
//A = (Y2,Y1)/(X2,X1)  B = Y2 - AX2                         
#define SPEED_REF_MIN        (_IQ(0.05))           //ADC��PWMIN��� �ٶȸ�����С
#define SPEED_REF_MAX        (_IQ(1.0))           //ADC��PWMIN��� �ٶȸ������
  
#define SREFCOUNT            (15)                 //�˲�����
#define ADCREFOFFVALUE       (_IQ(0.05))          //�ػ���ƽ0.05*5 = 0.25V 
#define ADCREFONVALUE        (_IQ(0.1))           //������ƽ0.1*5 = 0.5V
#define ADCSREFINMIN         (_IQ(0.1))           //ADC���� ��С
#define ADCSREFINMAX         (_IQ(0.95))           //ADC���� ���

#define ADCAlineA            ((float)(SPEED_REF_MAX-SPEED_REF_MIN)/(float)(ADCSREFINMAX-ADCSREFINMIN))
#define ADCAlineB            (SPEED_REF_MAX - ADCSREFINMAX*ADCAlineA)
//PWMIN  ������峵 ���ſ���
#define PWMINALINE_EN        (1)                  // ����У׼ʹ��
#define PWMIdling            (1040)               // ��������
#define PWMINStartUp				 (1150)               // ������������
#define PWMHighMinDefault    (1000)               // �������У׼, us
#define PWMHighMaxDefault    (1900)               // �������У׼, us
#define PWMHighMinAline      (1200)               // �������У׼, us
#define PWMHighMaxAline      (1800)               // �������У׼, us
#define MotorBreakTime       (10)                 // ɲ������ʱ�� us
#define MotorOFFTimeErr      (10)                 // ONOFFʱ��ƫ��, us
#define MotorONTimeErr       (30)                 // ONOFFʱ��ƫ��, us
#define PWMINHighMinFilt     (400)                // ��������ź�����ֵ, us
#define PWMINHighMaxFilt     (3000)               // ��������ź�����ֵ, us

#if(PWMINSREF_EN)
  #define MOS_SELFINSPECTION  (0)                 //MOS�Լ����ֻ֧�� fu68311Q QNF32
  #define BEEPSCAN_EN         (1)                 //������� ��ʾ�� ȡ�������ʾ����ͬʱȡ�� ����У׼
  #define BEEP_VOL            (0.5)               //����������� ��С  volume
#endif
#endif
