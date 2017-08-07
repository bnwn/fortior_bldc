/* Includes ------------------------------------------------------------------*/
#include <FU68xx.h>
#include <Myproject.h>


/** @addtogroup FT68xx
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LEDFAULTDIS_EN     (1)     //故障指示
#define LEDONOFFDIS_EN     (0)     //ONOFF指示#define LEDCWCCWDIS_EN     (0)     //正反转显示
#define LEDCELLDIS_EN      (0)     //电量显示
#define LEDSHIFTDIS_EN     (0)     //档位显示

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


void LED_show(void);
void Fault_Led(Error_TypeDef value); 
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Fault_Led   P15 P17 P20
* Description    : 
* Input          : Ctl.SysError故障代码
* Output         : None
* Return         : None
*******************************************************************************/
void Fault_Led(Error_TypeDef value)
{
  #if(LEDFAULTDIS_EN)
  u16 temp = 500;
  if(value != 0)
  {
    if(Ctl.Tim.LED_OnOffms > temp)
    {
      if(Ctl.Tim.LED_Cunter <= ((value<<1) - 1))  //一元操作符不加空格 3.6.6
      {
        if(Ctl.Tim.LED_OnOffms > (temp + 500))
        {
          Ctl.Tim.LED_OnOffms = temp;
          Ctl.Tim.LED_Cunter++;
          FAULT_ONOFF;
        }       
      }
      else
      {
        #if(0)
        //FAULT_ONOFF;                     //故障指示完成，输出固定信号
        Ctl.Tim.LED_OnOffms = 0;
        #else                              //故障指示完成，输出斩波信号
        if(Ctl.Tim.LED_OnOffms>temp+100)
        {
          Ctl.Tim.LED_OnOffms  = temp;
          FAULT_ONOFF;
        } 
        #endif                   
      }             
    }
  }
  else
  {
    Ctl.Tim.LED_OnOffms = 0;
  }
  #endif
}

/*******************************************************************************
* Function Name  : LED_show
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void LED_show(void)
{
  //照明指示
  #if(LAMP_EN) //扳手螺丝批，延时掉电程序
  if(Ctl.Tim.NoOperationDelaynms >= NOOPDELAYNMS)
  {
    Ctl.Tim.NoOperationDelaynms = NOOPDELAYNMS;
//    ReadRomValue = Flash_GetAddress();     //读
//    Flash_ErasePageRom();                  //擦
//    Flash_KeyWriteValue((WriteRomValue));  //写
    PDELAY_OFF;
  } 
  else
  {
    PDELAY_ON;
  }
  #endif   
                          
  #if(LEDONOFFDIS_EN)
  if(Ctl.Start == TRUE)
  {
    LED1_ON;
  }
  else
  {
    LED1_OFF;
  }
  #endif
//正反转显示
  #if(LEDCWCCWDIS_EN)
  if(Uc.flg.FR == CW)
  {
    LED2_OFF;
  }
  else if(Uc.flg.FR == CCW)
  {
    LED2_ON;
  }
  #endif
//电量显示
  #if(LEDCELLDIS_EN)
  if (Ctl.SysError == NONE)
  {
    if(Drv.AdcMeas.Vdc > 18)
    {
      LED1_ON;
      LED2_ON;
      LED3_ON;
    }
    else if(Drv.AdcMeas.Vdc > 16.5)
    {
      LED1_OFF;
      LED2_ON;
      LED3_ON;
    }
    else if(Drv.AdcMeas.Vdc > 15)
    {
      LED1_OFF;
      LED2_OFF;
      LED3_ON;
    }
    else
    {
      LED1_OFF;
      LED2_OFF;
      LED3_OFF;
    }
  }
  #endif 
//档位显示

  #if(LEDSHIFTDIS_EN)
  switch(Ctl.spd.SpeedShift)
  {
    case 1:
    {
      LED4_ON;
      LED5_OFF;
      LED6_OFF;
      LED7_OFF;
      LED8_OFF;
      LED9_OFF;
    }
      break;
    case 2:
    {
      LED4_ON;
      LED5_ON;
      LED6_OFF;
      LED7_OFF;
      LED8_OFF;
      LED9_OFF;
    }
      break;
    case 3:
    {
      LED4_ON;
      LED5_ON;
      LED6_ON;
      LED7_OFF;
      LED8_OFF;
      LED9_OFF;
    }      
      break;
    case 4:
    {
      LED4_ON;
      LED5_ON;
      LED6_ON;
      LED7_ON;
      LED8_OFF;
      LED9_OFF;
    }
      break;
    case 5:
    {
      LED4_ON;
      LED5_ON;
      LED6_ON;
      LED7_ON;
      LED8_ON;
      LED9_OFF;
    }
      break;  
    case 6:
    {
      LED4_ON;
      LED5_ON;
      LED6_ON;
      LED7_ON;
      LED8_ON;
      LED9_ON;
    }
    break;
    
    default:
      break;
  }
  #endif
}