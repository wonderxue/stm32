#ifndef __SPI_H__
#define __SPI_H__
#include "stm32f10x.h"

#define User_SPIx          2
#define User_SPI_Modex     3
#define User_SPI_Speed     SPI_BaudRatePrescaler_256

#define User_SPI_CS_Pin    GPIO_Pin_12
#define User_SPI_CS_GPIO   GPIOB
#define User_SPI_CS_RCC    RCC_APB2Periph_GPIOB

#define SPI_CS_Enable      GPIO_ResetBits(User_SPI_CS_GPIO,User_SPI_CS_Pin)
#define SPI_CS_Disable     GPIO_SetBits(User_SPI_CS_GPIO,User_SPI_CS_Pin)

#if User_SPIx==1
#define User_RCC_APB2Periph_GPIO  RCC_APB2Periph_GPIOA
#define User_RCC_APB1Periph_SPI   RCC_APB1Periph_SPI1
#define User_SPI_GPIO             GPIOA
#define User_SPI                  SPI1
#define User_SPI_SCK      GPIO_Pin_5
#define User_SPI_MISO     GPIO_Pin_6
#define User_SPI_MOSI     GPIO_Pin_7
#endif

#if User_SPIx==2
#define User_RCC_APB2Periph_GPIO  RCC_APB2Periph_GPIOB
#define User_RCC_APB1Periph_SPI   RCC_APB1Periph_SPI2
#define User_SPI_GPIO             GPIOB
#define User_SPI                  SPI2
#define User_SPI_SCK      GPIO_Pin_13
#define User_SPI_MISO     GPIO_Pin_14
#define User_SPI_MOSI     GPIO_Pin_15
#endif

#if User_SPI_Modex==0
#define User_SPI_CPOL  SPI_CPOL_Low
#define User_SPI_CPHA  SPI_CPHA_1Edge
#endif

#if User_SPI_Modex==1
#define User_SPI_CPOL  SPI_CPOL_Low
#define User_SPI_CPHA  SPI_CPHA_2Edge
#endif

#if User_SPI_Modex==2
#define User_SPI_CPOL  SPI_CPOL_High
#define User_SPI_CPHA  SPI_CPHA_1Edge
#endif

#if User_SPI_Modex==3
#define User_SPI_CPOL  SPI_CPOL_High
#define User_SPI_CPHA  SPI_CPHA_2Edge
#endif

void User_SPI_Init(void);
void User_SPI_SetSpeed(unsigned char SPI_Speed);
unsigned char SPI_ReadWriteByte(unsigned char TxData);
#endif  //__SPI_H__
