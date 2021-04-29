#ifndef __ADC_M_D_H__
#define __ADC_M_D_H__

#include <stm32f10x.h>

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC1输入通道（引脚）配置**************************/
#define    ADCx                          ADC1
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA

#define    ADC_PIN_1                      GPIO_Pin_1
#define    ADC_CHANNEL_1                  ADC_Channel_1

#define    ADC_PIN_2                      GPIO_Pin_2
#define    ADC_CHANNEL_2                  ADC_Channel_2

#define    NOFCHANEL										  2
#define    ADC_DMA_CHANNEL                DMA1_Channel1
#define    ADC_DMA_CLK                    RCC_AHBPeriph_DMA1
void ADCx_Init(void);

#endif  //__ADC_M_D_H__
