#ifndef __ADC_S_I_H__
#define __ADC_S_I_H__

#include <stm32f10x.h>

// ADC ���ѡ��
// ������ ADC1/2�����ʹ��ADC3���ж���ص�Ҫ�ĳ�ADC3��
#define    ADCx                          ADC2
#define    ADC_CLK                       RCC_APB2Periph_ADC2

// ADC GPIO�궨��
// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA
#define    ADC_PIN                       GPIO_Pin_1

// ADC ͨ���궨��
#define    ADC_CHANNEL                   ADC_Channel_1

// ADC �ж���غ궨��
#define    ADC_IRQ                       ADC1_2_IRQn
#define    ADC_IRQHandler                ADC1_2_IRQHandler

void ADCx_Init(void);

#endif  //__ADC_S_I_H__