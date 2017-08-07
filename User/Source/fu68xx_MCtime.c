
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
#include "fu68xx_MCtime.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : TIM1_Config
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_Config(void)
{
  u8 temp;
/**********************************************************************	
�����˲�ʹ�ܼ�ģʽѡ��	
00;		4-machine cycle noise,4MHz
01;		8-machine cycle noise,2MHz
10		16-machine cycle noise,1MHz	
11;		32-machine cycle noise,0.5MHz		
**********************************************************************/

  SetBit(TIM1_CR2,INM00,1); 
  SetBit(TIM1_CR2,INM01,1); 
  SetBit(TIM1_CR2,INM10,1); 
  SetBit(TIM1_CR2,INM11,1); 
  SetBit(TIM1_CR2,INM20,1); 
  SetBit(TIM1_CR2,INM21,1); 
  
  SetBit(TIM1_CR0,INC0,1);            /*0:��ֹTI0�����˲�,1:ʹ��TI0�����˲�*/	
  SetBit(TIM1_CR0,INC1,1);            /*0:��ֹTI1�����˲�,1:ʹ��TI1�����˲�*/	
  SetBit(TIM1_CR0,INC2,1);            /*0:��ֹTI2�����˲�,1:ʹ��TI2�����˲�*/	

/********************************************************************
�����ź�ѡ��
0: TI0--COMP0_OUT    TI1--COMP1_OUT    TI2--COMP2_OUT
1: TI0--P1.4_IN      TI1--P1.6_IN      TI2--P2.1_IN
********************************************************************/
  #if (POSITION_FB_MODE == HALLSENSOR)
    #if (HallIC == HallSensor)
    SetBit(TIM1_CR2,TIS,0);   //�����û����֤ 20160222
    #elif (HallIC == HallIC)  
    SetBit(TIM1_CR2,TIS,1);
    #endif
  SetBit(TIM1_CR2,TIS,1);
  #elif (POSITION_FB_MODE == SENSORLESS)
  SetBit(TIM1_CR2,TIS,0);
  #endif
/********************************************************************
���뼫�Լ��
00:��������		01:���������		10:����½���		11:�������/�½���
********************************************************************/
  SetBit(TIM1_CR0,CPE1,1);
  SetBit(TIM1_CR0,CPE0,1);

/********************************************************************
���ؼ��ʹ��
********************************************************************/
  SetBit(TIM1_CR0, IEE2, 1);          // 0:��ֹTI2���ؼ��,1:ʹ��TI2���ؼ��
  SetBit(TIM1_CR0, IEE1, 1);          // 0:��ֹTI1���ؼ��,1:ʹ��TI1���ؼ��
  SetBit(TIM1_CR0, IEE0, 1);          // 0:��ֹTI0���ؼ��,1:ʹ��TI0���ؼ��
  SetBit(TIM1_CR1, CMPE, 0);          // 0:���ؼ��Ƚ�,   1:λ�ü��Ƚ�
/*CPDֵ����------------------------------------------------------------------------*/
//  SetBit(TIM1_CR1, CPD2, 0);
//  SetBit(TIM1_CR1, CPD2, 0);
//  SetBit(TIM1_CR1, CPD2, 0);
/*RDAֵ����------------------------------------------------------------------------*/
//  SetBit(TIM1_DRH, RDA2, 0);
//  SetBit(TIM1_DRH, RDA1, 0);
//  SetBit(TIM1_DRH, RDA0, 0);   
/********************************************************************
���ݸ���ģʽ����
000:���дTIM1_BDBR����TIM1_BDR
001:PTimer���紥��TIM1_BDBR����TIM1_BDR
010:λ�ü�����봥��TIM1_BDBR����TIM1_BDR
011:λ�ü����������PTimer��PTimer�������TIM1_BDR
100:λ�ü���������PTimer�������TIM1_BDR
101:λ�ü��Ƚϵ�����Ч�����PTimer�����������TIM1_BDR
110:λ�ü��Ƚϵ�����Ч���봥��TIM1_BDBR����TIM1_BDR
111:λ�ü��Ƚϵ�����Ч��������PTimer��PTimer�������TIM1_DBR
********************************************************************/
  SetBit(TIM1_CR3,OPS2,0);
  SetBit(TIM1_CR3,OPS1,0);
  SetBit(TIM1_CR3,OPS0,0);           //���дDBR��������
/********************************************************************
PPGͬ����ʽ����
WTS = 00: ��ͬ���������������   
WTS = 01: ������ͬ�����   
WTS = 10: �½���ͬ�����  
WTS = 11: ����/�½���ͬ�����
********************************************************************/
  SetBit(TIM1_CR1,WTS1,0);            //��ͬ���������������
  SetBit(TIM1_CR1,WTS0,0);

/********************************************************************
Basic Timer & Preload Timer����
********************************************************************/
  SetBit(TIM1_CR3,BCEN,0);            //ֹͣ16bit��ʱ��

  #if (TIM1_PSC == TIM1PSC24M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,0);
  SetBit(TIM1_CR3,T1PSC1,0);
  SetBit(TIM1_CR3,T1PSC0,0);          //��ʱ����Ƶ 4 ������ʱ��Ϊ24MHz
  #elif (TIM1_PSC == TIM1PSC12M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,0);
  SetBit(TIM1_CR3,T1PSC1,0);
  SetBit(TIM1_CR3,T1PSC0,1);          //��ʱ����Ƶ 4 ������ʱ��Ϊ24MHz
  #elif (TIM1_PSC == TIM1PSC6M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,0);
  SetBit(TIM1_CR3,T1PSC1,1);
  SetBit(TIM1_CR3,T1PSC0,0);          //��ʱ����Ƶ 4 ������ʱ��Ϊ24MHz
  #elif (TIM1_PSC == TIM1PSC3M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,0);
  SetBit(TIM1_CR3,T1PSC1,1);
  SetBit(TIM1_CR3,T1PSC0,1);          //��ʱ����Ƶ 8 ������ʱ��Ϊ24MHz
  #elif (TIM1_PSC == TIM1PSC1_5M)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,1);
  SetBit(TIM1_CR3,T1PSC1,0);
  SetBit(TIM1_CR3,T1PSC0,0);          //��ʱ����Ƶ 16 ������ʱ��Ϊ24MHz
  #elif (TIM1_PSC == TIM1PSC750K)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,1);
  SetBit(TIM1_CR3,T1PSC1,0);
  SetBit(TIM1_CR3,T1PSC0,1);          //��ʱ����Ƶ 32 ������ʱ��Ϊ24MHz
  #elif (TIM1_PSC == TIM1PSC375K)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,1);
  SetBit(TIM1_CR3,T1PSC1,1);
  SetBit(TIM1_CR3,T1PSC0,0);          //��ʱ����Ƶ 64 ������ʱ��Ϊ24MHz
  #elif (TIM1_PSC == TIM1PSC187_5K)
  SetBit(TIM1_CR3,T1PSC3,0);          //
  SetBit(TIM1_CR3,T1PSC2,1);
  SetBit(TIM1_CR3,T1PSC1,1);
  SetBit(TIM1_CR3,T1PSC0,1);          //��ʱ����Ƶ 128 ������ʱ��Ϊ24MHz
  #endif

  SetBit(TIM1_CR2,BRS,1);             //λ�ü�ⴥ����ʱ����λ BSR 0д��ʱ��λ 1λ�ü�⸴λ
  TIM1_BARR = 0xFFFF;                 //
  TIM1_BCNTR = 1;         
  SetBit(TIM1_CR3,BCEN,1);            //����16bit��ʱ��

  SetBit(TIM1_CR1,RCEN,0);            //ֹͣPreload��ʱ��
  SetBit(TIM1_CR1,ROPM,1);            //ʹ��OPMģʽ   ����ģʽ
  TIM1_RARR = 0xffff;
  TIM1_RCNTR = 0xffff;

  /********************************************************************
                                               �ж�ʹ��
  ********************************************************************/
  TIM1_SR = 0x00;                    //�жϱ�־����
  SetBit(TIM1_IER,CPIE,0);            //��ֹ�Ƚ��ж�
  SetBit(TIM1_IER,PDIE,1);            //ʹ��λ�ü���ж� 
  SetBit(TIM1_IER,WTIE,0);            //ʹ��д��ʱ���ж� 	
  SetBit(TIM1_IER,RUIE,0);            //��ֹPreload��ʱ�������ж�
  SetBit(TIM1_IER,BOIE,1);            //ʹ��16bit��ʱ�����ж�
   
  TIM1_DTR  = PWM_DEADTIMENUS*1000.0/41.67-1;
  if(TIM1_DTR < 5)
  {
    TIM1_DTR = 5;
  }
  else if(TIM1_DTR > 500)
  {
    TIM1_DTR = 500;
  }
    
 // DeadTime = (TIM1_DTR+1)/cpuclk,
/********************************************************************
ʹ�����
OCM = 00��ǿ������͵�ƽ
OCM = 01�����ͬ��PPG��TIM2�����
OCM = 10���������PPG��TIM2�����
OCM = 11��ǿ������ߵ�ƽ
********************************************************************/ 

  PWMOUT_OFF;                          //
  MOE = 1;                             //ʹ�������
}

/*******************************************************************************
* Function Name  : TIM2_Config
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_Config(void)
{
  /**************************************************************
  Timer 2 ʱ�ӷ�Ƶ����
  000:cpuclk			001:cpuclk/2^1	010:cpuclk/2^2	011:cpuclk/2^3
  100:cpuclk/2^4   	101:cpuclk/2^5	110:cpuclk/2^6	111:cpuclk/2^7
  **************************************************************/
  SetBit(TIM2_CR0,T2PSC2,0);
  SetBit(TIM2_CR0,T2PSC1,0);
  SetBit(TIM2_CR0,T2PSC0,0);

  SetBit(TIM2_CR0,T2MODE,1);          //����ģʽѡ��1--���ģʽ��0--����ģʽ
  SetBit(TIM2_CR0,T2CES,0);           /*����Counterģʽʱ��Ч��ѡ��1--�����أ�0--�½���*/
  SetBit(TIM2_CR0,T2CTM,0);           /*����ģʽѡ��1--Counter,0--Timer*/	

  /*********************����Ƚ�ģʽ��******************************
  00--ǿ��0 ��                
  01--ǿ��1
  10-- TIMx_CNTR<=TIMx_DRΪ0 TIMx_CNTR>TIMx_DRΪ1
  11-- TIMx_CNTR<=TIMx_DRΪ1 TIMx_CNTR>TIMx_DRΪ0
  *****************************************************************/
  SetBit(TIM2_CR0,T2OCM1,1);
  SetBit(TIM2_CR0,T2OCM0,1);

  /*���ģʽ���Ƚ�ƥ���жϣ� ����Timerģʽ��PWM���ڼ���жϣ�����Counterģʽ������PWM����ƥ���ж� */  
  SetBit(TIM2_CR1,T2IDE,1);			  //ƥ���ж�ʹ��

  /*���ģʽ�������������жϣ�����Timerģʽ�������������жϣ�����Counterģʽ�����������������ж� */  
  SetBit(TIM2_CR1,T2IFE,1);			  //�����ж�ʹ��

  SetBit(TIM2_CR1,T2FE,0);			  //���������˲�ʹ�ܣ�4CPU CLK		
  SetBit(TIM2_CR1,T2OPM,0);				/*��ֹ���μ���*/	

  TIM2_DR = 300;                    //PWM�ز�ռ�ձ�
  TIM2_ARR = PWMARR;                //�ز�Ƶ�� = 24M/1500 =16K
  
  //		SetBit(P1_OE,P10,1);            //ʹ��P1.0�������
  //		SetBit(PH_SEL,T2SEL,1);				  //ʹ��P1.0��ΪTimer2�������	

  SetBit(TIM2_CR1,T2CEN,1);				  /*��������*/	
}

/*******************************************************************************
* Function Name  : TIM3_Config
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_Config(void)
{
  SetBit(TIM3_CR1, T3CEN, 0);                          // ֹͣ����*/

  /*-------------------------------------------------------------------------------------------------
  ʱ�ӷ�Ƶ����(T5PSC)  750k
  000:cpuclk			001:cpuclk/2^1	010:cpuclk/2^2	011:cpuclk/2^3
  100:cpuclk/2^4	101:cpuclk/2^5	110:cpuclk/2^6	111:cpuclk/2^7	
  -------------------------------------------------------------------------------------------------*/
  SetBit(TIM3_CR0, T3PSC2, 1);
  SetBit(TIM3_CR0, T3PSC1, 0);
  SetBit(TIM3_CR0, T3PSC0, 1);

  /*-------------------------------------------------------------------------------------------------
  �Ƚ����ģʽ
  OCM = 00��ǿ������͵�ƽ
  OCM = 01��ǿ������ߵ�ƽ
  OCM = 10��PWMģʽ1��CNTR<DR����͵�ƽ��CNTR>DR����ߵ�ƽ
  OCM = 11��PWMģʽ2��CNTR<DR����ߵ�ƽ��CNTR>DR����͵�ƽ
  -------------------------------------------------------------------------------------------------*/
  SetBit(TIM3_CR0, T3MODE, 1);                            // ѡ�����ģʽ				
  SetBit(TIM3_CR0, T3OCM1, 1);
  SetBit(TIM3_CR0, T3OCM0, 0);                             // ����Ƚ�ģʽ2,0-->1
  SetBit(TIM3_CR1, T3FE, 1);                               // ʹ�������˲�

  CLRFlag_T3IR;
  CLRFlag_T3IP;
  CLRFlag_T3IF;
  SetBit(TIM3_CR1, T3IDE, 0);				                       // ��ֹ����Ƚ�/PWM���ڼ���ж�
  SetBit(TIM3_CR1, T3IFE, 0);				                       // ʹ������ж�	

  #if (PWMINONOFF_EN)
  {
    TIM3_ARR = 1;							                               // TIM3 Period = 100us				
    TIM3_DR = 0;
    TIM3_CNTR = 1;
    SetBit(TIM3_CR0, T3MODE, 0);			                       // ѡ������ģʽ	
    SetBit(TIM3_CR0, T3CTM, 0);	                             // ���붨ʱ��ģʽ
    SetBit(P1_OE, P11, 0);                                   // config P21 as input
    SetBit(P1_PU, P11, 1);                                   // enable P21 pull up	
    SetBit(P1_AN, P11, 0);                                   // diasable P21analog function		
    SetBit(TIM3_CR1, T3IDE, 1);				                       // ��ֹ����Ƚ�/PWM���ڼ���ж�
    SetBit(PH_SEL, T3SEL, 1);					                       // GP11ѡ��Capture Timer����/���(for test)
    SetBit(TIM3_CR1, T3IFE, 1);				                       // ʹ������ж�	
  }
  #endif

  #if (IRONOFF_EN)
  {
    /*PWMPin Config*/
    SetBit(P1_OE, P11, 0);                                   // config P21 as input
    SetBit(P1_PU, P11, 1);                                   // enable P21 pull up	
    SetBit(P1_AN, P11, 0);                                   // diasable P21analog function
    CLR(P1IF, P11);					                                 // clear P21 interrupt flag
    SetBit(P1IE, P11, 1);		                                 // config P21 as the source of EXTI1		
      
    TIM3_ARR = 60000;							                               // TIM3 Period = 100us				
    TIM3_DR = TIM3_ARR >> 1;;	
    TIM3_CNTR = 1;
    SetBit(TIM3_CR1, T3IFE, 1);				                       // ʹ������ж�	
    
  }
  #endif

  SetBit(TIM3_CR1, T3CEN, 1);				                       // ��������	
}
/*******************************************************************************
* Function Name  : TIM4_Config 
* Description    : Main program. P0.1     ��100us��ʱ����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_Config(void)
{
  //SetBit(PH_SEL, T4SEL, 1);       //GP01ѡ��Capture Timer����/���(for test)
  SetBit(TIM4_CR1, T4CEN, 0);         //ֹͣ����*/

  /*-----------------------------------------------------------------------------------
  ʱ�ӷ�Ƶ����(T5PSC)
  000:cpuclk			001:cpuclk/2^1	010:cpuclk/2^2	011:cpuclk/2^3
  100:cpuclk/2^4	101:cpuclk/2^5	110:cpuclk/2^6	111:cpuclk/2^7	
  -----------------------------------------------------------------------------------*/			
  SetBit(TIM4_CR0, T4PSC2, 0);
  SetBit(TIM4_CR0, T4PSC1, 0);
  SetBit(TIM4_CR0, T4PSC0, 0);

  /*-----------------------------------------------------------------------------------
  �Ƚ����ģʽ
  OCM = 00��ǿ������͵�ƽ
  OCM = 01��ǿ������ߵ�ƽ
  OCM = 10��PWMģʽ1��CNTR<DR����͵�ƽ��CNTR>DR����ߵ�ƽ
  OCM = 11��PWMģʽ2��CNTR<DR����ߵ�ƽ��CNTR>DR����͵�ƽ
  -----------------------------------------------------------------------------------*/		
  SetBit(TIM4_CR0, T4MODE, 1);      //ѡ�����ģʽ				
  SetBit(TIM4_CR0, T4OCM1, 1);
  SetBit(TIM4_CR0, T4OCM0, 0);      //����Ƚ�ģʽ2,0-->1

  CLR(TIM4_CR1, T4IR);
  CLR(TIM4_CR1, T4IP);
  CLR(TIM4_CR1, T4IF);
  SetBit(TIM4_CR1, T4IDE, 0);       //��ֹ����Ƚ�/�½��ؼ���жϺ������ؼ���ж�									
  SetBit(TIM4_CR1, T4IFE, 1);       //ʹ������ж�	

  TIM4_ARR = 2400;                  // TIM4 Period = 100us				
  TIM4_DR = TIM4_ARR >> 1; 
  TIM4_CNTR = 1;

  SetBit(TIM4_CR1, T4CEN, 1);       //��������	

}