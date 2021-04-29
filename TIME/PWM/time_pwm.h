#ifndef __TIME_PWM_H__
#define __TIME_PWM_H__
#include <stm32f10x.h>
#include "LED.h"

#define TIM                       TIM3
#define RCC_APB1Periph_TIM        RCC_APB1Periph_TIM3

#define RCC_APB2Periph_GPIO       RCC_APB2Periph_GPIOB
#define GPIO_Pin_X                GPIO_Pin_5
#define GPIO                      GPIOB

#define GPIO_PartialRemap_TIM     GPIO_PartialRemap_TIM3

void Time_PWM_Init(uint16_t arr,uint16_t psc);

#endif  //__TIME_PWM_H__
