#include <FTC68xx.h>
#include <MC_type.h>

//void SVPWM_init(void)
//{
//	SV_US = 0;								// SV_US:uint16,Q15(0~32767)
//	SV_PWMPRD = PWMARR;
//	SV_ANGLE = 0;									// SV_ANGLE:uint16,Q16(0~65536)
//	SetBit(SV_CR, SVSEGMT, 0);			// 0£º7 segment£¬1£º5 segment
//}


//void SVPWM_APP(void)
//{	
//	if(MC.FR == CW)
//	{	
//		MC.Angle += MC.Theta;	
//		if(MC.Angle > 65535)
//		{
//			MC.Angle -= 65536;
//		}	
//	}
//	else if(MC.FR == CCW)
//	{
//		if(MC.Angle < MC.Theta)
//		{
//			MC.Angle += 65535;
//		}	
//		MC.Angle -= MC.Theta;	
//	}
//	
//	SV_ANGLE = (uint16)MC.Angle;
//	SV_US = MC.PWMDutyCtl.VS;

//	SetBit(SV_CR, SVSTA, 1);
//	
//}
