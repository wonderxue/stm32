#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"

#define LED_OFF      GPIOC->BSRR = GPIO_Pin_13
#define LED_ON       GPIOC->BRR  = GPIO_Pin_13

void LED_Init(void);
void LED_Turning(void);

#endif  //__LED_H__
