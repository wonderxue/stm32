#ifndef __TIME_INT_H__
#define __TIME_INT_H__
#include <stm32f10x.h>
#include "LED.h"

#define TIM                    TIM3
#define RCC_APB1Periph_TIM     RCC_APB1Periph_TIM3
#define TIM_IRQn                TIM3_IRQn

void Time_Int_Init(uint16_t arr,uint16_t psc);

#endif  //__TIME_INT_H__
