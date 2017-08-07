
#include <FU68xx.h>
#include "sys_conf.h"

void fu68xx_xram_erase(void);
void Driver_Init(void);
void SystemInit(void);

void SystemInit(void)
{
//-----------------------------------------
//Xram ����
  fu68xx_xram_erase();

//-----------------------------------------
//����ģʽ 
  Driver_Init();
/*-----------------------------------------------------------------------------------
  5��ADC�ο���ѹ����
  6���˷Ż�׼��ѹ����
-----------------------------------------------------------------------------------*/
  VREFConfig(VREF5_0, Enable);								// ADC�ο���ѹ����
  VHALFConfig(VREF_Half, Enable);							// �˷Ż�׼��ѹ����
  
  /*---------------------------------------------------------------------------------
  MOE Protect Config
  1��Ӳ������ʹ�ܣ�����Ӳ��������Ӳ���ر��������MOE=0��ͬʱ����Ӳ�������ж�
  2��ѡ��Ӳ�����������ź�Դ��
  1���ⲿ�ж�0  
  0���Ƚ���3�жϡ�
  3��Ӳ�����������ź��˲����á�
   00-4cpu clock    01-8cpu clock    10-16cpu clock    11-24cpu clock 
   ----------------------------------------------------------------------------------*/
  #if(HARD_OC_EN)
  SetBit(EVT_FILT, MCLREN, 1);                // ʹ��Ӳ������
  #else
  SetBit(EVT_FILT, MCLREN, 0);                // ʧ��Ӳ������
  #endif

  #if (EFAL == FO_CMP)
  //�Ƚ���������
  SetBit(EVT_FILT, EFSRC, 0);                 // Ӳ�����������ź�ΪCMP3���
  #else (EFAL == FO_INT)
  IT01 = 0;                                  //
  IT00 = 1;                                  //�½��ش���
  
  EX0 = 0;                                   //�ն�ʹ��

  SetBit(EVT_FILT, EFSRC, 1);                 // Ӳ�����������ź�Ϊint0���
  #endif
  SetBit(EVT_FILT, EFEN, 1);                  // ʹ��Ӳ�����������ź��˲�
  SetBit(EVT_FILT, EFDIV1, 0);
  SetBit(EVT_FILT, EFDIV0, 0);                // Ӳ�������ź��˲����Ϊ24cpuclock
}


/*******************************************************************************
* Function Name  : fu68xx_xram_erase
* Description    : xram ����ģ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void fu68xx_xram_erase(void)
{
  unsigned char xdata *port  ;
  
  port = 0;
  while(port<=0XFFF)
  {
    *port  = 0 ;
    port++;
  }
}

/*******************************************************************************
* Function Name  : Driver_Init
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Driver_Init(void)
{
  u32 PRDRVCnt;

  /*-------------------------------------------------------------------------------------------------
  DRV_CTL��PWM��Դѡ��    
  OCS1 = 0, OCS1 = X: TIM0 PWM
  OCS1 = 1, OCS1 = 0: TIM1 PWM
  OCS1 = 1, OCS1 = 1: FOC 6 PWM
  -------------------------------------------------------------------------------------------------*/
  /*TIM1 6 PWM output*/
  SetBit(DRV_CTL, OCS1, 0);                     // TIM1 6 PWM output
  SetBit(DRV_CTL, OCS0, 1);

  SetBit(DRV_CTL, PRDRVEN, 1);                 //Predriverʹ��λ   
  for(PRDRVCnt=0;PRDRVCnt<24000;PRDRVCnt++);   //vina 
  
  SetBit(DRV_CTL, DRVOE, 1);                   // gata driverʹ��λ

  /*-------------------------------------------------------------------------------------------------
  ���е�ƽ����
  -------------------------------------------------------------------------------------------------*/ 
  OISWL = 0;                      // OC5���е�ƽ����
  OISWH = 0;                      // OC4���е�ƽ����
  OISVL = 0;                      // OC3���е�ƽ����
  OISVH = 0;                      // OC2���е�ƽ����
  OISUL = 0;                      // OC1���е�ƽ����
  OISUH = 0;                      // OC0���е�ƽ����
}