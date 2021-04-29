#ifndef __IIC_H__
#define __IIC_H__

#include <stm32f10x.h>

//IIC_GPIO config
#define SDA            GPIO_Pin_7
#define SCL            GPIO_Pin_5
#define IIC_GPIO       GPIOA
#define IIC_RCC_GPIO   RCC_APB2Periph_GPIOA

#define IIC_SCL_1()  GPIO_SetBits(IIC_GPIO,SCL)//IIC_GPIO->BSRR = SCL
#define IIC_SCL_0()  GPIO_ResetBits(IIC_GPIO,SCL)//IIC_GPIO->BRR  = SCL				
	
#define IIC_SDA_1()  GPIO_SetBits(IIC_GPIO,SDA)//IIC_GPIO->BSRR = SDA
#define IIC_SDA_0()  GPIO_ResetBits(IIC_GPIO,SDA)//IIC_GPIO->BRR  = SDA
	
#define IIC_SDA_READ()  GPIO_ReadInputDataBit(IIC_GPIO,SDA)

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
unsigned char IIC_SendByte(unsigned char data);
unsigned char IIC_ReadByte(void);

#endif  //__IIC_H__
