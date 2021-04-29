#include "LED.h"

void LED_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  GPIO_InitTypeDef ss;
  ss.GPIO_Mode=GPIO_Mode_Out_PP;
  ss.GPIO_Pin=GPIO_Pin_13;
  ss.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC,&ss);
}
