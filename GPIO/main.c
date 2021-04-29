#include <stm32f10x.h>
#include "LED.h"
int main()
{
  int i=0;
  LED_Init();
  while(1)
  {
    LED_Turning();
    for(i=0;i<2000000;i++);
  }
}
