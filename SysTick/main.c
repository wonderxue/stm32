#include <stm32f10x.h>
#include "SysTick.h"
#include "LED.h"
int main()
{
  LED_Init();
  LED_OFF;
  SysTick_INTR_ms(1000);
  while(1)
  {
  }
}
