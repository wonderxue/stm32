#ifndef __ADC_S_D_H__
#define __ADC_S_D_H__

#include <stm32f10x.h>

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADCx                          ADC1
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA

// PC1-ͨ��11 ����IO
#define    ADC_PIN                       GPIO_Pin_1
#define    ADC_CHANNEL                   ADC_Channel_1
#define    ADC_DMA_CHANNEL               DMA1_Channel1

void ADCx_Init(void);

#endif  //__ADC_S_D_H__