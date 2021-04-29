#include "LED.h"
#include "exti.h"
#include "usart.h"
int main()
{
  int a;
  USART_Config();
  LED_Init();
  printf("test start\n");
  EXTI_Key_Config();
  while(1);
}
