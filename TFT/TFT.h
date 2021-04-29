#ifndef __TFT_H__
#define __TFT_H__

//RGB 5-6-5

#include <stm32f10x.h>
#include "SysTick.h"

#define TFT_CTRLA   	  GPIOA
#define TFT_CTRLB   	  GPIOB


//GPIO B
#define TFT_SCL        	GPIO_Pin_11
#define TFT_SDA        	GPIO_Pin_10
#define TFT_RST     	  GPIO_Pin_1
#define TFT_RS         	GPIO_Pin_0

//GPIO A
#define TFT_CS        	GPIO_Pin_7
#define TFT_LED        	GPIO_Pin_6



#define	TFT_SCL_SET  	TFT_CTRLB->BSRR=TFT_SCL    
#define	TFT_SDA_SET  	TFT_CTRLB ->BSRR=TFT_SDA   
#define	TFT_CS_SET  	TFT_CTRLA->BSRR=TFT_CS  

    
#define	TFT_LED_SET  	TFT_CTRLA->BSRR=TFT_LED   
#define	TFT_RS_SET  	TFT_CTRLB->BSRR=TFT_RS 
#define	TFT_RST_SET  	TFT_CTRLB->BSRR=TFT_RST 

#define	TFT_SCL_CLR  	TFT_CTRLB->BRR=TFT_SCL  
#define	TFT_SDA_CLR  	TFT_CTRLB->BRR=TFT_SDA 
#define	TFT_CS_CLR  	TFT_CTRLA->BRR=TFT_CS 
    
#define	TFT_LED_CLR  	TFT_CTRLA->BRR=TFT_LED 
#define	TFT_RST_CLR  	TFT_CTRLB->BRR=TFT_RST
#define	TFT_RS_CLR  	TFT_CTRLB->BRR=TFT_RS 

void TFT_WriteCmd(unsigned char Cmd);
void TFT_WriteData_U8(unsigned char Data);
void TFT_WriteData_U16(unsigned short Data);
void TFT_WriteReg(unsigned char Index,unsigned char Data);
void TFT_Reset(void);
void TFT_Init(void);

void TFT_SetRegion(unsigned short x_start,unsigned short y_start,unsigned short x_end,unsigned short y_end);
void TFT_SetXY(unsigned short x,unsigned short y);
void Gui_DrawPoint(unsigned short x,unsigned short y,unsigned short Data);
void TFT_Clear(unsigned short Color);

#endif  //__TFT_H__
