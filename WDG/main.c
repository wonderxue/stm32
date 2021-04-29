#include "stm32f10x.h"
#include "LED.h"
#include "WWDG.h"
#include "SysTick.h"

int main()
{
  LED_Init();
  WWDG_Init(0x7f,WWDG_Prescaler_8,0x5f);
  LED_ON;
  SysTick_delay_ms(500);
  while(1)
  {
    LED_OFF;
    SysTick_delay_ms(400);
    WWDG_ReloadCounter();
  }
  
}