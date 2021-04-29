#include "WWDG.h"
#include "LED.h"

u8 gcr;

void WWDG_IRQHandler(void)
{
  WWDG_ClearFlag();
  WWDG_SetCounter(gcr);
  LED_ON;
}

static void WWDG_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

 void WWDG_Init(u8 cr,u16 pre,u8 wr)
 {
   gcr=cr;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
   WWDG_DeInit(); 
   
   WWDG_SetPrescaler(pre);
   WWDG_SetCounter(cr);
   WWDG_SetWindowValue(wr);
   
   WWDG_Enable(cr);
   #if WWDG_IT
   WWDG_ClearFlag();	
   WWDG_NVIC_Config();
   WWDG_EnableIT();
   #endif
 }
 
void WWDG_ReloadCounter()
{
  WWDG_SetCounter(gcr);
}