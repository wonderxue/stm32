#include "SysTick.h"
unsigned int INT=0;
unsigned int Temp=0;

static char SysTick_Config_Redef(uint32_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                   
  }
  #if SysTick_IQR_Status
  
  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                        
  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); 
  SysTick->VAL   = 0UL;                                             
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         
  #else 
  
  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                        
  SysTick->VAL   = 0UL;                                           
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk;                         
  #endif  //IRQ
  return (0UL);  
}
void SysTick_INTR_us(unsigned int us)
{
  INT=us;
  Temp=us;
  SysTick_Config_Redef(72);
}
void SysTick_INTR_ms(unsigned int ms)
{
  INT=ms;
  Temp=ms;
  SysTick_Config_Redef(72000);
}

void SysTick_delay_us(unsigned int us)
{
  unsigned int i=0;
  SysTick_Config_Redef(72);
  for(i=0;i<us;i++)
  {
    while(!((SysTick->CTRL)&(1<<16)));
  }
  SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_delay_ms(unsigned int ms)
{
  unsigned int i=0;
  SysTick_Config_Redef(72000);
  for(i=0;i<ms;i++)
  {
    while(!(SysTick->CTRL&(1<<16)));
  }
  SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
}
