#include "stm32f10x.h"
#include "RCC_Config.h"
void Init()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  GPIO_InitTypeDef GPIOC_13;
  GPIOC_13.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIOC_13.GPIO_Pin=GPIO_Pin_13;
  GPIOC_13.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC,&GPIOC_13);
}
int main()
{  
  int i;
  RCC_HSE_Config(RCC_PLLMul_2);
  Init(); 
  while(1)
  {  
    GPIO_SetBits(GPIOC,GPIO_Pin_13);
    for(i=0;i<300000;i++);
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
    for(i=0;i<300000;i++);
  }
}
