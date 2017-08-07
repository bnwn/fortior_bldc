#include <FTC68xx.h>
#include <Myproject.h>


/******************************************************************************
 tan(Angle)= 2^0, 2^(-1), 2^(-2), 2^(-3), 2^(-4), 2^(-5), 2^(-6), 2^(-7), 
						 2^(-8), 2^(-9), 2^(-10), 2^(-11), 2^(-12), 2^(-13)
 ��Ӧ�Ƕȵ�ֵ,Q15��ʽ, 
*******************************************************************************/
int16 xdata TanAngle[13] = {4096, 2418, 1277, 648, 326, 163, 81, 41, 20, 10, 5, 3, 1};

bit FlagStartPI = 0;

Ramp_TypeDef idata SpeedRamp;
PID_TypeDef idata SpeedPID;
PID_TypeDef idata CurrentPID;

void SpeedPIDInit(void)
{
	SpeedPID.Kp = TempSpeedKP;						//Q12��ʽ
	SpeedPID.Ki = TempSpeedKI;						//Q12��ʽ
	SpeedPID.Err = 0;
	SpeedPID.Err_Last1 = 0;
	SpeedPID.Err_Err = 0;
	#if (CurrentCloseLoopEnable)
	{
		SpeedPID.Out = 0;//TempMotorStartDuty;//
		SpeedPID.OutMax = TempCurrentMax;//MotorVSMax;//
		SpeedPID.OutMin = TempCurrentMin;//MotorVSMin;//
	}
	#else
	{
		SpeedPID.Out = TempMotorStartDuty;//0;//
		SpeedPID.OutMax = MotorVSMax;//TempCurrentMax;//
		SpeedPID.OutMin = TempMotorStartDuty;//TempCurrentMin;//	
	}
  #endif	
}

void SpeedRampInit(void)
{
	SpeedRamp.RampInc = SpeedRampInc;
	SpeedRamp.RampDec = SpeedRampDec;
	SpeedRamp.RampStep = MC.SpeedCtl.PISpeed;
}	


void CurrentPIDInit(void)
{
	CurrentPID.Kp = TempCurrentKP;						//Q12��ʽ
	CurrentPID.Ki = TempCurrentKI;						//Q12��ʽ
	CurrentPID.Err = 0;
	CurrentPID.Err_Last1 = 0;
	CurrentPID.Err_Err = 0;
	CurrentPID.Out = TempMotorStartDuty;
	CurrentPID.OutMax = MotorVSMax;
	CurrentPID.OutMin = TempMotorStartDuty;
}


int16 RampControl(Ramp_TypeDef *Ramp, int16 Ref)
{
	Ramp->RampTarget = Ref;
	if(Ramp->RampTarget > Ramp->RampStep)
	{
		Ramp->RampStep += Ramp->RampInc;
		if(Ramp->RampStep > Ramp->RampTarget)
		{
			Ramp->RampStep = Ramp->RampTarget;
		}
	}
	else if(Ramp->RampTarget < Ramp->RampStep)
	{
		Ramp->RampStep -= Ramp->RampDec;
		if(Ramp->RampStep < Ramp->RampTarget)
		{
			Ramp->RampStep = Ramp->RampTarget;
		}
	}
	
	return 	Ramp->RampStep;
}

int16 PIDControl(PID_TypeDef *PID, int16 Ref, int16 Cur)
{
	int32 Kp_Out, Ki_Out, PID_Out;

	/*PI����ʱ��67us*/
	if(!PID->Err)
	{
		PID->Err_Last1 = Ref - Cur;																//��ʼ��PID�ϴ�ƫ��
		PID->Err = Ref - Cur;																			//��ʼ��PID��ǰƫ��
		PID->Err_Err=PID->Err - PID->Err_Last1;										//��ʼ��PID�ϴ�ƫ������ϴ�ƫ��֮��
	}
	else
	{
		PID->Err_Last1 = PID->Err;																//����PID�ϴ�ƫ��
		PID->Err = Ref - Cur;																			//����PID��ǰƫ��
		PID->Err_Err=PID->Err - PID->Err_Last1;										//����PID�ϴ�ƫ������ϴ�ƫ��֮��		
	}

	Kp_Out = ((int32)PID->Kp * (int32)PID->Err_Err) >> 12;
	Ki_Out = ((int32)PID->Ki * (int32)PID->Err) >> 12;

	PID_Out = PID->Out;
	PID_Out += Kp_Out + Ki_Out;

	if(PID_Out > PID->OutMax)
	{
		PID_Out = PID->OutMax;												//PID������
	}
	if(PID_Out < PID->OutMin)
	{
		PID_Out = PID->OutMin;												//PID������
	}
	PID->Out = PID_Out;
 	
	return PID->Out;	
}

int16 PID_Control(PID_TypeDef *PID, int16 Ref, int16 Cur)
{
	int16 Kp_Out;
	int16 Ki_Out;
	int32 PID_Out;

	/*PI����ʱ��42us*/
	if(!PID->Err)
	{
		PID->Err_Last1 = Ref - Cur;																//��ʼ��PID�ϴ�ƫ��
		PID->Err = Ref - Cur;																			//��ʼ��PID��ǰƫ��
		PID->Err_Err=PID->Err - PID->Err_Last1;										//��ʼ��PID�ϴ�ƫ������ϴ�ƫ��֮��
	}
	else
	{
		PID->Err_Last1 = PID->Err;																//����PID�ϴ�ƫ��
		PID->Err = Ref - Cur;																			//����PID��ǰƫ��
		PID->Err_Err=PID->Err - PID->Err_Last1;										//����PID�ϴ�ƫ������ϴ�ƫ��֮��		
	}
	
	Kp_Out = MDU_MULA_S16(PID->Kp, PID->Err_Err, 12);
	Ki_Out = MDU_MULA_S16(PID->Ki, PID->Err, 12);
	PID_Out = PID->Out;
	PID_Out += Kp_Out + Ki_Out;
		
	if(PID_Out > PID->OutMax)
	{
		PID_Out = PID->OutMax;												//PID������
	}
	if(PID_Out < PID->OutMin)
	{
		PID_Out = PID->OutMin;												//PID������
	}
	PID->Out = PID_Out;
	
	return PID->Out;	
}

void PI_Init(void)
{	
/*-----------------------------------------------------------------------------------
	PI���ݸ�ʽ
	Q = PIRANGE + 8(Q8~Q23���ݸ�ʽ)
  ���Ĵ�����ֵʱҪͳһ���ݸ�ʽ
-----------------------------------------------------------------------------------*/		
	SetBit(SV_CR, PIRANGE3, 0);
	SetBit(SV_CR, PIRANGE2, 1);
	SetBit(SV_CR, PIRANGE1, 0);
	SetBit(SV_CR, PIRANGE0, 0);				//PI��λQ=PIRANGE+8����PI���ݸ�ʽ							

  PI_KP = 0;												//�Ĵ����������ͣ�int16 Q12��ʽ��PI_KP=Kp*2^12��
	PI_KI = 0;												//�Ĵ����������ͣ�int16 Q12��ʽ��PI_KI=Kp*2^12
	PI_EK = 0;												
  PI_UK = 0;												//�Ĵ����������ͣ�int16
	PI_UKMAX = 0;											//�Ĵ����������ͣ�int16
	PI_UKMIN = 0;											//�Ĵ����������ͣ�int16
}
int16 PI_Control(PID_TypeDef *PID, int16 Ref, int16 Cur)
{
	static uint8 *PIDType = 0;
	
	/*PI����ʱ��10us*/	
	FlagStartPI = 1;
	while(FlagStartPI)   // MDU��ʱ���ñ�־
	{
		FlagStartPI = 0;	

		/*ָ�����������ж�ִ��ʱ��2.5us*/
		if(PIDType != PID)                // ͨ��PID���ݵ�ַ��ȡPID���ͣ�
		{
			PIDType = PID;
			
			PI_KP = PID->Kp;									//�Ĵ����������ͣ�int16 Q12��ʽ��PI_KP=Kp*2^12��
			PI_KI = PID->Ki;									//�Ĵ����������ͣ�int16 Q12��ʽ��PI_KI=Kp*2^12
			PI_EK = PID->Err;												
			PI_UK = PID->Out;									//�Ĵ����������ͣ�int16
			PI_UKMAX = PID->OutMax;						//�Ĵ����������ͣ�int16
			PI_UKMIN = PID->OutMin;						//�Ĵ����������ͣ�int16		
			
			SetBit(SV_CR,PISTA,1);						//����PI
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();													//�ȴ�PI�������,PI_LastErr��ʼ����?

		}
		/*��ֵ����ʱ��3.2us*/	
		PID->Err = Ref - Cur;								//����PID��ǰƫ��  

		/*PIӲ������ʱ��1.8us*/
		PI_EK = PID->Err;										//PI����
		PI_UK = PID->Out;									//�Ĵ����������ͣ�int16
		SetBit(SV_CR,PISTA,1);
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		PID->Out = PI_UK;										//PI���
	}
  FlagStartPI = 1;
	
  return PID->Out;
}



/*******************************************************************************
Name 		: Sin()
Input		: Angle,Angle Value=0��~360��(Q15 Value=0~32767)
Output	: Sin(Angle)
Function:	caclulate Sin(Angle)
*******************************************************************************/
int16 Sin(int16 Angle)
{
	uint8 i;
	uint8 Quadrant;
	int16 z;
	int32 x[2], y[2];
	x[0] = 19898;															//��ʼ��תʸ��ģ��Q15��ʽ,0.607252941*2^15=19898
	y[0] = 0;
	z = 0;
	if((0<=Angle) && (Angle<8192))							//Angle=0��~90��,1th quadrant
	{
		Quadrant = 1;
	}
	else if((8192<=Angle) && (Angle<16384))		//Angle=90��~180��,2th quadrant
	{
		Quadrant = 2;
		Angle = 16384 - Angle;
	}
	else if((16384<=Angle) && (Angle<24576))		//Angle=180��~270��,3th quadrant
	{
		Quadrant = 3;
		Angle = Angle - 16384;
	}
	else if((24576<=Angle) && (Angle<32768))		//Angle=270��~360��,4th quadrant
	{
		Quadrant = 4;
		Angle = 32767 - Angle;
	}

	for(i=0;i<13;i++)
	{
		if(z < Angle)
		{
			x[1] = x[0] - (y[0] >> i);
			y[1] = y[0] + (x[0] >> i);
			z += TanAngle[i];
		}
		else
		{
			x[1] = x[0] + (y[0] >> i);
			y[1] = y[0] - (x[0] >> i);
			z -= TanAngle[i];
		}
		x[0] = x[1];
		y[0] = y[1];
	}
	
	if((Quadrant==3) || (Quadrant==4))
	{
		y[0]= -y[0];
	}
	
	if(y[0] > 32767)
	{
		y[0] = 32767;
	}
	if(y[0] < -32768)
	{
		y[0] = -32768;
	}
	return (int16)y[0];	
	
}


/*******************************************************************************
Name 		: Cos()
Input		: Angle,Angle Value=0��~360��(Q15 Value=0~32767)
Output	: Cos(Angle)
Function:	caclulate Cos(Angle)
*******************************************************************************/
int16 Cos(int16 Angle)
{
	uint8 i;
	uint8 Quadrant;
	int16 z;
	int32 x[2], y[2];
	x[0] = 19898;															//��ʼ��תʸ��ģ��Q15��ʽ,0.607252941*2^15=19898	
	y[0] = 0;
	z = 0;
	if((0<=Angle) && (Angle<8192))							//Angle=0��~90��,1th quadrant
	{
		Quadrant = 1;
	}
	else if((8192<=Angle) && (Angle<16384))		//Angle=90��~180��,2th quadrant
	{
		Quadrant = 2;
		Angle = 16384 - Angle;
	}
	else if((16384<=Angle) && (Angle<24576))		//Angle=180��~270��,3th quadrant
	{
		Quadrant = 3;
		Angle = Angle - 16384;
	}
	else if((24576<=Angle) && (Angle<32768))		//Angle=270��~360��,4th quadrant
	{
		Quadrant = 4;
		Angle = 32767 - Angle;
	}
	
	for(i=0;i<13;i++)
	{	
		if(z < Angle)
		{
			x[1] = x[0] - (y[0] >> i);
			y[1] = y[0] + (x[0] >> i);
			z += TanAngle[i];
		}
		else
		{
			x[1] = x[0] + (y[0] >> i);
			y[1] = y[0] - (x[0] >> i);
			z -= TanAngle[i];
		}
		x[0] = x[1];
		y[0] = y[1];
	}
	
	if((Quadrant==2) || (Quadrant==3))
	{
		x[0] =  -x[0];
	}	
	
	if(x[0] > 32767)
	{
		x[0] = 32767;
	}
	if(x[0] < -32768)
	{
		x[0] = -32768;
	}
	return (int16)x[0];
}

