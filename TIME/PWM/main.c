#include <stm32f10x.h>
#include "time_pwm.h"
#include "LED.h"

int main()
{
  LED_Init();
  Time_PWM_Init(899,0);
  TIM_SetCompare2(TIM3,100);
}
