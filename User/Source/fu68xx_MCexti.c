#include <FTC68xx.h>
#include <MC_type.h>

//void EXTI_Init(void)
//{
//  /*HA Config*/
//	SetBit(P1_OE, P14, 0);  // config P14 as input
//	SetBit(P1_PU, P14, 1);  // enable P14 pull up	
//	SetBit(P1_AN, P14, 0);  // diasable P14 analog function
//	CLR(P1IF, P14);         // clear P14 interrupt flag
//	SetBit(P1IE, P14, 1);   // config P14 as the source of EXTI1
//	
//	/*HB Config*/
//	SetBit(P1_OE, P16, 0);  // config P16 as input
//	SetBit(P1_PU, P16, 1);  // enable P16 pull up	
//	SetBit(P1_AN, P16, 0);  // diasable P16 analog function
//	CLR(P1IF, P16);         // clear P16 interrupt flag
//	SetBit(P1IE, P16, 1);   // config P16 as the source of EXTI1
//	
//	/*HC Config*/
//	SetBit(P2_OE, P21, 0);   // config P21 as input
//	SetBit(P2_PU, P21, 1);  // enable P21 pull up	
//	SetBit(P2_AN, P21, 0);  // diasable P21analog function
//	CLR(P2IF, P21);					// clear P21 interrupt flag
//	SetBit(P2IE, P21, 1);		// config P21 as the source of EXTI1
//	
//	IT11 = 1;
//	IT10 = 1;								// rising and falling	
//	
//	PX11 = 1;
//	PX10 = 0;								// 中断优先级别2

//	EX1 = 1;								// 使能外部中断1
//	EA = 1;									// 使能全局中断
//	
//	
//}