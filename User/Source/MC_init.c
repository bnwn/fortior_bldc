
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
#include <Myproject.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//ȫ�أ�UH->VL,UH->WL,VH->WL,VH->UL,WH->UL,WH->VL,ɲ��
uc16  DRV_SECTION2OCM[8] = {UVW_OFF,UH_VL,UH_WL,VH_WL,VH_UL,WH_UL,WH_VL,ULVLWL_ON}; 
 
extern u8 xdata WriteRomValue;
extern u8 xdata ReadRomValue;
extern u8 xdata u8KeyForbid;  
extern DRV_TypeDef xdata Drv; 
/* Private function prototypes -----------------------------------------------*/

void SoftwareInit(void);          //�����ʼ��
static void GPIO_Config(void);    //��̬����
static void Interrupt_Config(void);
void MCL_ModuleInstance(void);    //����
void MCL_ModuleInit(void);        //��ʼ��
void MCL_ModuleDefault(void);     //Ĭ��ֵ
u8 Delay(u16 timer);
u8 Delayus(u16 timer);

static void PWMinit(void);
static void Bemfinit(void);
static void Hallinit(void);
static void BemfDefault(void);
static void TimNmsDefault(void);

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : ApplicationInit   Peripheral
* Description    :�������ʼ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SoftwareInit(void)
{  
  // GPIO Configuration 
  GPIO_Config(); 
  // Time1 Configuration 
  TIM1_Config();
  // TIM2 Configuration 
  TIM2_Config();
  // TIM3 Configuration 
  TIM3_Config();
  // TIM4 Configuration 
  TIM4_Config();
  // TIM5 Configuration 
  //TIM5_Config();  
  // AD Configuration 
  ADC_Config();
  // CMP Configuration
  CMP_Config();
  // AMP Configuration
  AMP_Config();
  // SPI Configuration
  //SPI_Config();
  //KEY Configuration	
  Key_Config();
  //Hall Configuration
  Hall_Init();

  //Pid Configuration
  //Pid_Config();
  MDUInit();
  #if((PWMINSREF_EN)||(PWMINONOFF_EN))
  PWMINInit();
  #endif
  //Pid Configuration
  Interrupt_Config();  
  //�ϵ�ȴ�ģ�飬�ȴ���Դ�ȶ�������
  Ctl.Tim.u16PowerOnNms = 0;                //
  Ctl.PowerOn == 0XFF;

  while(Ctl.Tim.u16PowerOnNms <= POWER_ON_NMS){}; 

  Ctl.PowerOn = 0x7F;//                              //�ϵ����
  Ctl.SysError = NONE;   
}

/*******************************************************************************
* Function Name  : Interrupt_Config   
* Description    : �ж����ȼ��ж�
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Interrupt_Config(void)
{
  EA = 0;									                                 // ��ֹȫ���ж�

  /*EXTI�ж�����*/
  PX01 = 1;                                                //���ȼ�3
  PX00 = 1;
  
//  PX11 = 1;
//  PX10 = 0;								                               // �ж����ȼ���Ϊ2	

  /*ADC�ж�����*/
  PADC1 = 0;
  PADC0 = 0;										                           // �ж����ȼ���Ϊ0

  /*CMP�ж�����*/
  PCMP1 = 0;
  PCMP0 = 0;									                             // �ж����ȼ���Ϊ3

  /*TIM1�ж�����*/
  PTIM11 = 1;
  PTIM10 = 1;										                           // �ж����ȼ���Ϊ3

  /*TIM2/3�ж�����*/
  PTIM231 = 0;
  PTIM230 = 1;                                            //��TIM2���ж����ȼ����һ�����ṩ�����Ͷ�ʱ
  
  /*TIM4/5�ж�����*/
  PTIM451 = 0;
  PTIM450 = 1;										                         // �ж����ȼ���Ϊ1
  
  EA = 1;									                                 // ʹ��ȫ���ж�
}
/*******************************************************************************
* Function Name  : GPIO_Config
* Description    : GPIO����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Config(void)
{    
  //-------------------------------------  
  //FD6536 ʹ�� 
  #if(DriverFD6536_EN)  
  SetBit(FD6536_GPIO_PORT,FD6536_PIN,1); 
  FD6536_DIS;
  #endif

  #if (POSITION_FB_MODE == SENSORLESS)
  SetBit(NSS_GPIO_PORT,NSS_PIN,1); 
  SetBit(MOSI_GPIO_PORT,MOSI_PIN,1); 
  SetBit(MISO_GPIO_PORT,MISO_PIN,1);   
  SetBit(SCLK_GPIO_PORT,SCLK_PIN,1);  
  #endif  
  //------------------------------------  
  #if(LAMP_EN)
  SetBit(PDELAY_GPIO_PORT,PDELAY_PIN,1); 
  PDELAY_ON;
  #endif
  
  //-------------------------------------  
  //FG
  SetBit(FG_GPIO_PORT,FG_PIN,1); 
  //-------------------------------------  
  //�������
  SetBit(FAULT_GPIO_PORT,FAULT_PIN,1);
  FAULT_ON;
  //LED��ʾ����       ������ʾ
  SetBit(LED1_GPIO_PORT,LED1_PIN,1); 
  SetBit(LED2_GPIO_PORT,LED2_PIN,1); 
}

/*******************************************************************************
* Function Name  : LED_show
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void MCL_ModuleInit(void)
{
  //----------------------------------
  Drv.PWM.PwmArr = PWMARR;
  Ctl.SysError = NONE; 

  //ReadRomValue = Flash_GetAddress();    //4.88ms 
  //WriteRomValue = ReadRomValue;  

  u8KeyForbid = 0X7F;
  PwmInResetFlag = 0x7F;
  //----------------------------------
  //���Ʋ�����ʼ��  
  Ctl.numTicksPerCtrl = PWM_PRESCALER;  Ctl.numTicksPerCtrl  = 1;
  Ctl.numTicksPerCurrent = 2;                   //2
  Ctl.numTicksPerSpeed = SPEED_CTL_CNT;         //6
  
  //----------------------------------
  // ������з������� ���ӿ���
  #if(BEMFSETFR)  //
  Drv.Stk.BemfSetFR = (*(unsigned char code *)BemfSetFRRomAddress);

  if(Drv.Stk.BemfSetFR != 0)
  {
    Uc.flg.FR = Drv.Stk.BemfSetFR&0x0F; 
  }   
  else
  {
    Uc.flg.FR = DIRECTION ; 
  }
  #else
  Uc.flg.FR = DIRECTION ;  
  #endif

  Ctl.direction = Uc.flg.FR;    //�������
  Ctl.FnStopmodeC = STOPMODE;
  
  //----------------------------------
  //����������� 
  Ctl.Motor.BaseSpeed    =  BASE_SPEED;
  Ctl.Motor.PolePairs    =  POLE_PAIR;
  Ctl.Motor.BaseVoltage  =  BASE_VOLTAGE;
  //----------------------------------
  // ĸ�ߵ�ѹ����  ��������   BEMF����
  ADCInit();
  //----------------------------------
  //PWM��ʼ��
  PWMinit();
  //----------------------------------
  //�ٶȱջ� �Ӽ���ʱ��  
  #if(SPEED_CLOSE_EN)
  Ctl.spd.refCur = 0;  
  Ctl.spd.refTar = SPEED_REF_TAR;
  Ctl.spd.IncValue = SPEED_INCVALUE;
  Ctl.spd.DecValue = SPEED_DECVALUE;
  pid_spd.Kp = SPEED_PTERM; //Q15��ʽ
  pid_spd.Ki = SPEED_ITERM; //Q15��ʽ
  Pid_spdInit(); 
  #endif
  //----------------------------------  
  #if(CURRENT_CLOSE_EN)
  //��������ʼ��
  Ctl.Is.refCur = 0;  
  Ctl.Is.refTar =   SPEED_REF_TAR;
  pid_is.Kp = CURRENT_PTERM; //Q15��ʽ
  pid_is.Ki = CURRENT_ITERM; //Q15��ʽ
  Pid_isInit(); 
  #endif
  //----------------------------------  
  #if(MOTORCIRCLECALEEN)     
  Ctl.spd.ComNum  = 0;
  Ctl.spd.CircleNum = 0;
  #endif
  //----------------------------------
  //�ٶȼ���ģ���ʼ��
  Drv.speed.EventPeriod = 0;    
  Drv.speed.InputSelect = 1;
  Drv.speed.BaseRpm = Ctl.Motor.BaseSpeed; 
  Drv.speed.SpeedScaler = SPEEDSCALER ;
  
  //----------------------------------
  #if (POSITION_FB_MODE == SENSORLESS) 
  Bemfinit();
  #else  Hallinit();
  #endif
  //==================================
  #if(OCRESTART_EN)
  Ctl.OC.u16Runms = 0;
  Ctl.OC.u16nmsCount = 0;
  Ctl.OC.u8ReNum = 0;
  #endif
  //----------------------------------
  #if(OVERLOAD_EN)
  MCL_OverLoadInit(MECASEOVERLOAD0,MECASEOVERLOAD1,MECASEOVERLOAD2,MECASEOVERLOAD3,OL0NMS,OL1NMS,OL2NMS,OL3NMS);  
  #endif
}

/*******************************************************************************
* Function Name  : MCL_ModuleDefault
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void MCL_ModuleDefault(void)
{
  TIM2_ARR = PWMARR;       //�ز�Ƶ�� 
  //----------------------------------
  //������з������� ���ӿ���
  Ctl.direction = Uc.flg.FR; 

  //----------------------------------
  //Step ����
  Ctl.Step = 5;
  Ctl.StepPre = 0;

  #if (POSITION_FB_MODE == SENSORLESS) 
  BemfDefault();           //BEMF����
  #else
  Drv.Hall.u8ChangePhaseNum = 0;
  #endif
//----------------------------------
  #if(SPEED_CLOSE_EN)     //�ٶȱջ�
  Ctl.spd.refCur = 0;  
  Pid_spdInit();  
  #else       
  Drv.PWM.DutytargetOpen = MOTOR_TARGRT_DUTY;
  Drv.PWM.Dutytarget     = Drv.PWM.DutytargetOpen;
  Drv.PWM.DutyCurrent    = 0;  
  #endif

  #if(CURRENT_CLOSE_EN)
  Pid_isInit();          //�����ջ�
  #endif
//----------------------------------
  TimNmsDefault();       //��ʱ������
  Key_init();            //��������
  PwmInResetFlag = 0x7F;

//==================================
  #if(MOTORCIRCLECALEEN)  //
  Ctl.spd.ComNum  = 0;
  Ctl.spd.CircleNum = 0;
  #endif
  
  #if(FAILSTOREEN) //���ϼ�¼
  Ctl.E_message.State = MOTOR_NONE;
  Ctl.E_message.ErrorF = 0;
  #endif
  
  #if(OVERLOAD_EN) //����
  MCL_OverLoadInit(MECASEOVERLOAD0,MECASEOVERLOAD1,MECASEOVERLOAD2,MECASEOVERLOAD3,OL0NMS,OL1NMS,OL2NMS,OL3NMS);  
  #endif
  
  #if(CBCCP_EN)   //������
  Ctl.Cbcc.FoCounter = 0;
  Ctl.Cbcc.ReCounter = 0;
  #endif
  
  #if(BEEPSCAN_EN) //�������
  BeepInit();
  #endif
}

u8 Delay(u16 timer)
{
  while(timer--) _nop_();
  return(0);  
}

u8 Delayus(u16 timer)
{
  while(timer--) Delay(24);
  return(0);  
}


void Bemfinit(void)
{
  Ctl.Bemf.SPItest = BEMF_TEST;
  Ctl.Bemf.IRQ = BEMFNONE;
  
  Ctl.Ramp.cpmode = RAMP_MODE;
  //��λ���϶������趨
  Ctl.Alig.duty   = ALIGNMENT_DUTY; 
  Ctl.Alig.timNms = ALIGNMENTNMS;  

  //��������������
  Ctl.Ramp.cpNumA = 0;
  Ctl.Ramp.cpNumB = 0;
  Ctl.Ramp.cpNms = RAMP_TIM_STA;
  Ctl.Ramp.cpNmsCount = 0;
  Ctl.Ramp.cptimSta   = RAMP_TIM_STA;
  Ctl.Ramp.cptimEnd   = RAMP_TIM_END;
  Ctl.Ramp.cptimstep  = RAMP_TIM_STEP;       
  Ctl.Ramp.cpDutySta  = RAMP_DUTY_STA;
  Ctl.Ramp.cpDutyEnd  = RAMP_DUTY_END;
  Ctl.Ramp.cpDutystep = RAMP_DUTY_INC;
  Ctl.Ramp.cpFinalNumB = RAMP_STEP_COUNTER;
  Ctl.Ramp.cpCntErr = 0;
  Ctl.Ramp.cpCntFail = 0;
  Ctl.Ramp.cpCntNormal = 0;
  Ctl.Ramp.cpNumFail= RampNumFail;
  
  Ctl.Ramp.cpBEMFCnt = RampDetecBEMFCnt;
  Ctl.Ramp.cpBEMFCntFilt = RampDetecBEMFCntFilt;
  Ctl.Ramp.cpMaskTime = TempRampMaskTime;
  
  Ctl.Bemf.CTAngle = TEMPDELAYANGLE;
  Ctl.Bemf.MaskAngle = TEMPMASKANGLE;

  Drv.Stk.Calcnum = SRKBNUM;

  MDUControl.DelayAngleOutRef = 0;
}

void PWMinit(void)
{
  Drv.PWM.DutytargetOpen = 0;
  Drv.PWM.DutyCurrent    = 0;
  Drv.PWM.Dutytarget     = 0;  
  Drv.PWM.DutyIncValue  = SPEED_INCVALUE;
  Drv.PWM.DutyDecValue  = SPEED_DECVALUE;
  Drv.PWM.DutyMax = MOTOR_VS_MAX;
  Drv.PWM.DutyMin = MOTOR_VS_MIN;
  Drv.PWM.DutyLimitMaxRef = MECASECURRENTLIMITMAXREF;
  Drv.PWM.DutyLimitADD = 100;
}
void Hallinit(void)
{
  Drv.Hall.s16AdvanceEangle = TEMPHALLADVANCEEANGLE; //HALLλ�÷������೬ǰ�Ƕ�

  if(Drv.Hall.s16AdvanceEangle < -50.0/60.0*32767)
  {
    Drv.Hall.s16AdvanceEangle = -50.0/60.0*32767;
  }
  else if(Drv.Hall.s16AdvanceEangle < -10.0/60.0*32767)
  {
    ;
  } 
  else if(Drv.Hall.s16AdvanceEangle < 0)
  {
    Drv.Hall.s16AdvanceEangle = -10.0/60.0*32767;
  }    
  else if(Drv.Hall.s16AdvanceEangle == 0)
  {
    Drv.Hall.s16AdvanceEangle = 0;
  }
  else if(Drv.Hall.s16AdvanceEangle > 30/60.0*32767)
  {
    Drv.Hall.s16AdvanceEangle = 30.0/60.0*32767;
  }
}

void BemfDefault(void)
{
  Drv.Stk.BemfTabA = 0;
  Drv.Stk.BemfTabB = 0;
  Drv.Stk.RefNumX = 0;
  Drv.Stk.RefNumY = 0;
  Drv.Stk.RefNumZ = 0;
  Drv.Stk.BemfFR = 0xFF;
  //��λ���϶������趨
  //Ctl.Alig.duty   = ALIGNMENT_DUTY; //0.4
  //Ctl.Alig.timNms = ALIGNMENTNMS;   //380

  //��������������
  Ctl.Ramp.cpNumA = 0;
  Ctl.Ramp.cpNumB = 0;
  Ctl.Ramp.cpNms = Ctl.Ramp.cptimSta;
  Ctl.Ramp.cpNmsCount = 0;
  Ctl.Ramp.cpCntErr = 0;
  Ctl.Ramp.cpCntFail = 0;
  Ctl.Ramp.cpCntNormal = 0;  
  Ctl.Bemf.MaskTime = TempRampMaskTime;
  Ctl.Section.Cur = 0;
  Ctl.Section.Per = 0;
  Ctl.Section.ErrCounter = 0;

  MDUControl.DelayAngleOutRef = 0;
}
void TimNmsDefault(void)
{
  //----------------------------------
  //��ѹǷѹ�ж�ʱ�䣬��ת ��������
  Ctl.Tim.OVnms = 0;
  Ctl.Tim.UVnms = 0;
  Ctl.Tim.Nonms = 0;
  Ctl.Tim.OCnms = 0;
  Ctl.Tim.OH1nms = 0;
  Ctl.Tim.OH1REnms = 0;
  Ctl.Tim.OH2nms = 0;
  Ctl.Tim.OH2REnms = 0;

  Ctl.Tim.STAnms = 0;           //��ת
  Ctl.Tim.STB1nms = 0;          //ʧ��1
  Ctl.Tim.STB2nms = 0;          //ʧ��2
  Ctl.Tim.LED_OnOffms = 0;
  Ctl.Tim.LED_Cunter = 0;
}