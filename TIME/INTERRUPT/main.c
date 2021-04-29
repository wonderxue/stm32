#include <stm32f10x.h>
#include "time_int.h"
#include "LED.h"

int main()
{
  LED_Init();
  Time_Int_Init(4999,7199);
  while(1);
}
