#include <stm32f10x.h>
#include "usart.h"
#include "LED.h"
#include "user_it.h"
void delay()
{
  int a;
  for(a=0;a<2000000;a++);
}
int main()
{
  int value;
  USART_Config();
  printf("\nFunction  >>USART_Config()  >>done\n");
  LED_Init();
  printf("Function  >>LED_Init()  >>done\n");
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  GPIO_InitTypeDef ss;
  ss.GPIO_Mode=GPIO_Mode_IPU;
  ss.GPIO_Pin=GPIO_Pin_13;
  ss.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC,&ss);
  while(1)
  {
    delay();
    value=(GPIOC->IDR & GPIO_Pin_13);
    printf("%d",value);
  }
}
