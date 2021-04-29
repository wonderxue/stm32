#include "time_pwm.h"

//tim=(arr+1)*(psc+1)/Sysclock  ms
void Time_PWM_Init(uint16_t arr,uint16_t psc)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIMS;
  TIM_OCInitTypeDef TIM_OCInitStruct;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO|RCC_APB2Periph_AFIO,ENABLE);
  
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_X;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIO,&GPIO_InitStructure);
  
  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM,ENABLE);
  
  TIMS.TIM_Period=arr;
  TIMS.TIM_Prescaler=psc;
  TIMS.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM,&TIMS);
  
  TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;
  TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
  TIM_OC2Init(TIM,&TIM_OCInitStruct);
  
  TIM_OC2PreloadConfig(TIM,TIM_OCPreload_Enable);
  
  TIM_Cmd(TIM,ENABLE);
}
