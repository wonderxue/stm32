#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <stm32f10x.h>
#include <core_cm3.h>
#include "LED.h"

//0-Disable  1-Enable
#define SysTick_IQR_Status    1

void SysTick_INTR_us(unsigned int us);
void SysTick_INTR_ms(unsigned int ms);

void SysTick_delay_us(unsigned int us);
void SysTick_delay_ms(unsigned int ms);
  
#endif  //__SYSTICK_H__
