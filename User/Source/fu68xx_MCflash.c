
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
#include "fu68xx_MCadc.h"
#include "fu68xx_MCflash.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define STARTPAGEROMADDRESS 0x3C00 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8 xdata *PageRomAddress = 0;     //ҳ��ַ
uint8 xdata OffsetRomAddressCur = 0; //ƫ�Ƶ�ǰ��ַ 
uint8 xdata OffsetRomAddressTar = 0; //ƫ��Ŀ��д���ַ

u8 xdata WriteRomValue;           //ROM д��ֵ
u8 xdata ReadRomValue;            //ROM ����ֵ
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
u8 Flash_GetAddress(void);
void Flash_ErasePageRom(void);
void Flash_KeyWriteValue( u8 value);

/*-------------------------------------------------------------------------------------------------
	Function Name :	void Flash_GetAddress(void)
	Description   :	��ȡFlash��ǰ��ַ�е�ֵ
	Input         :	null
  Output				: null
-------------------------------------------------------------------------------------------------*/
u8 Flash_GetAddress(void)//
{
  uint8 i;
  u8 tevalue;        //��ʱ����
  u8 revalue;        //����ֵ

  PageRomAddress = STARTPAGEROMADDRESS;
  
  tevalue = *(uint8 code *)PageRomAddress;
  
  while(tevalue != 0x7F)
  {
    PageRomAddress = PageRomAddress + 0x80; 
    tevalue = *(uint8 code *)PageRomAddress;
    
    if(PageRomAddress > 0x3F00)
    {
      PageRomAddress = STARTPAGEROMADDRESS;        
      revalue = 1;
      OffsetRomAddressCur = 0;
      OffsetRomAddressTar = OffsetRomAddressCur + 1;
      Flash_Sector_Write(PageRomAddress,0X7F); 
      tevalue = 0x7F;
    }      
  }

  for(i = 0; i < 128;i++)
  {
    tevalue = *(uint8 code *)(PageRomAddress + i);
    if(tevalue > 0)
    {
      OffsetRomAddressCur = i;
      OffsetRomAddressTar = OffsetRomAddressCur + 1;
      revalue = tevalue;
    }
  }

  return revalue;
}


void Flash_ErasePageRom(void)
{
  if(OffsetRomAddressCur >= 127)
  { 
    OffsetRomAddressCur = 0;
    OffsetRomAddressTar = OffsetRomAddressCur + 1;

    Flash_Sector_Erase(PageRomAddress);                   //������ҳ

    if(PageRomAddress < 0x3F00)    
    {
      PageRomAddress = PageRomAddress + 0x80;
    }
    else 
    {
      PageRomAddress = STARTPAGEROMADDRESS;
    }
    
    Flash_Sector_Write(PageRomAddress + OffsetRomAddressCur, 0x7F);    //�׵�ַд��
  }
}

void Flash_KeyWriteValue( u8 value)
{
  u8 key;
  u8 i;
  u8 TempReadRomValue;

  key = value; 

  TempReadRomValue = ReadRomValue;                       
  
  for(i = 0;((WriteRomValue != TempReadRomValue)&&(i < 5));i++)
  {
    Flash_Sector_Write(PageRomAddress + OffsetRomAddressTar, key);
    TempReadRomValue = *(uint8 code *)(PageRomAddress + OffsetRomAddressTar);
  }
  
  if(WriteRomValue == TempReadRomValue)
  {
    ReadRomValue = TempReadRomValue;
  }                                                                    //������Ч����
}