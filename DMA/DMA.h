#ifndef __DMA_H__
#define __DMA_H__

#include <stm32f10x.h>

#define DMA_CHANNEL     DMA1_Channel4
#define DMA_CLOCK       RCC_AHBPeriph_DMA1
#define USART_DR_ADDRESS        (USART1_BASE+0x04)

#define DMA_FLAG_TC     DMA1_FLAG_TC4
#define BUFFER_SIZE     50

void DMA_Config(void);

#endif  //__DMA_H__
