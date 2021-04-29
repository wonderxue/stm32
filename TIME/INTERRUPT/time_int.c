#include "time_int.h"

void TIM3_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM,TIM_IT_Update)!=RESET)
  {
    LED_Turning();
    TIM_ClearITPendingBit(TIM,TIM_IT_Update);
  }
}
//tim=(arr+1)*(psc+1)/Sysclock  ms
void Time_Int_Init(uint16_t arr,uint16_t psc)
{
  TIM_TimeBaseInitTypeDef TIMS;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  TIMS.TIM_Period=arr;
  TIMS.TIM_Prescaler=psc;
  TIMS.TIM_CounterMode=TIM_CounterMode_Up;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM,ENABLE);
  TIM_TimeBaseInit(TIM,&TIMS);
  
  TIM_ITConfig(TIM,TIM_IT_Update,ENABLE);
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel =TIM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  TIM_Cmd(TIM,ENABLE);
}
