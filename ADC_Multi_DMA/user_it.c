#include "user_it.h"

//for ADC_IRQHandler()
//__IO uint16_t ADC_ConvertedValue;

void WWDG_IRQHandler(void)
{
  printf("\nIRQHandler  >>WWDG_IRQHandler()  >>done\n");
}

void PVD_IRQHandler(void)
{
  printf("\nIRQHandler  >>PVD_IRQHandler()  >>done\n");
}

void TAMPER_IRQHandler(void)
{
  printf("\nIRQHandler  >>TAMPER_IRQHandler()  >>done\n");
}

void RTC_IRQHandler(void)
{
  printf("\nIRQHandler  >>RTC_IRQHandle()  >>done\n");
}

void FLASH_IRQHandler(void)
{
  printf("\nIRQHandler  >>FLASH_IRQHandler()  >>done\n");
}

void RCC_IRQHandler(void)
{
  printf("\nIRQHandler  >>RCC_IRQHandler()  >>done\n");
}

void EXTI0_IRQHandler(void)
{
  printf("\nIRQHandler  >>EXTI0_IRQHandler()  >>done\n");
} 

void EXTI1_IRQHandler(void)
{
  printf("\nIRQHandler  >>EXTI1_IRQHandler()  >>done\n");
}

void EXTI2_IRQHandler(void)
{
  printf("\nIRQHandler  >>EXTI2_IRQHandler()  >>done\n");
}

void EXTI3_IRQHandler(void)
{
  printf("\nIRQHandler  >>EXTI3_IRQHandler()  >>done\n");
}

void EXTI4_IRQHandler(void)
{
  printf("\nIRQHandler  >>EXTI4_IRQHandler()  >>done\n");
}

void DMA1_Channel1_IRQHandler(void)
{
  printf("\nIRQHandler  >>DMA1_Channel1_IRQHandler()  >>done\n");
}

void DMA1_Channel2_IRQHandler(void)
{
  printf("\nIRQHandler  >>DMA1_Channel2_IRQHandler()  >>done\n");
}

void DMA1_Channel3_IRQHandler(void)
{
  printf("\nIRQHandler  >>DMA1_Channel3_IRQHandler()  >>done\n");
}

void DMA1_Channel4_IRQHandler(void)
{
  printf("\nIRQHandler  >>DMA1_Channel4_IRQHandler()  >>done\n");
}

void DMA1_Channel5_IRQHandler(void)
{
  printf("\nIRQHandler  >>DMA1_Channel5_IRQHandler()  >>done\n");
}

void DMA1_Channel6_IRQHandler(void)
{
  printf("\nIRQHandler  >>WWDG_IRQHandler()  >>done\n");
}

void DMA1_Channel7_IRQHandler(void)
{
  printf("\nIRQHandler  >>DMA1_Channel7_IRQHandler()  >>done\n");
}

void ADC1_2_IRQHandler(void)
{
  printf("\nIRQHandler  >>ADC1_2_IRQHandler()  >>done\n");
//  if (ADC_GetITStatus(ADCx,ADC_IT_EOC)==SET) 
//	{
//		// 读取ADC的转换值
//		ADC_ConvertedValue = ADC_GetConversionValue(ADCx);
//	}
//	ADC_ClearITPendingBit(ADCx,ADC_IT_EOC);
}

void USB_HP_CAN1_TX_IRQHandler(void)
{
  printf("\nIRQHandler  >>USB_HP_CAN1_TX_IRQHandler()  >>done\n");
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
  printf("\nIRQHandler  >>USB_LP_CAN1_RX0_IRQHandler()  >>done\n");
}

void CAN1_RX1_IRQHandler(void)
{
  printf("\nIRQHandler  >>CAN1_RX1_IRQHandler()  >>done\n");
}

void CAN1_SCE_IRQHandler(void)
{
  printf("\nIRQHandler  >>CAN1_SCE_IRQHandler()  >>done\n");
}

void EXTI9_5_IRQHandler(void)
{
  printf("\nIRQHandler  >>EXTI9_5_IRQHandler()  >>done\n");
}

void TIM1_BRK_IRQHandler(void)
{
  printf("\nIRQHandler  >>TIM1_BRK_IRQHandler()  >>done\n");
}

void TIM1_UP_IRQHandler(void)
{
  printf("\nIRQHandler  >>TIM1_UP_IRQHandler()  >>done\n");
}

void TIM1_TRG_COM_IRQHandler(void)
{
  printf("\nIRQHandler  >>TIM1_TRG_COM_IRQHandler()  >>done\n");
}

void TIM1_CC_IRQHandler(void)
{
  printf("\nIRQHandler  >>TIM1_CC_IRQHandler()  >>done\n");
}

void TIM2_IRQHandler(void)
{
  printf("\nIRQHandler  >>TIM2_IRQHandler()  >>done\n");
}

void TIM3_IRQHandler(void)
{
  printf("\nIRQHandler  >>TIM3_IRQHandler()  >>done\n");
}

void TIM4_IRQHandler(void)
{
  printf("\nIRQHandler  >>TIM4_IRQHandler()  >>done\n");
}

void I2C1_EV_IRQHandler(void)
{
  printf("\nIRQHandler  >>I2C1_EV_IRQHandler()  >>done\n");
}

void I2C1_ER_IRQHandler(void)
{
  printf("\nIRQHandler  >>I2C1_ER_IRQHandler()  >>done\n");
}

void I2C2_EV_IRQHandler(void)
{
  printf("\nIRQHandler  >>I2C2_EV_IRQHandler()  >>done\n");
}

void I2C2_ER_IRQHandler(void)
{
  printf("\nIRQHandler  >>I2C2_ER_IRQHandler()  >>done\n");
}

void SPI1_IRQHandler(void)
{
  printf("\nIRQHandler  >>SPI1_IRQHandler()  >>done\n");
}

void SPI2_IRQHandler(void)
{
  printf("\nIRQHandler  >>SPI2_IRQHandler()  >>done\n");
}

void USART1_IRQHandler(void)
{
  //printf("\nIRQHandler  >>USART1_IRQHandler()  >>done\n");
  char cmd[8];
  if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET)
  {
    scanf("%s",cmd);
    printf("Cmd:%s\n",cmd);
   if(strcmp(cmd,"ON")==0)
    {
      LED_ON;
      printf("Process  >>LED_ON  >>done\n");
    }
    else if(strcmp(cmd,"OFF")==0)
    {
      LED_OFF;
      printf("Process  >>LED_OFF >>done\n");
    }
    else if(strcmp(cmd,"RST")==0)
    { 
      printf("Warning  >>System_Rebooting  >>done\n");
      //__set_FAULTMASK(1); 
      NVIC_SystemReset();
    }
  }
  USART_ClearITPendingBit(DEBUG_USARTx, USART_IT_RXNE);
}

void USART2_IRQHandler(void)
{
  printf("\nIRQHandler  >>USART2_IRQHandler()  >>done\n");
}

void USART3_IRQHandler(void)
{
  printf("\nIRQHandler  >>USART3_IRQHandler()  >>done\n");
}

void EXTI15_10_IRQHandler(void)
{
  printf("\nIRQHandler  >>EXTI15_10_IRQHandler()  >>done\n");
}

void RTCAlarm_IRQHandler(void)
{
  printf("\nIRQHandler  >>RTCAlarm_IRQHandler()  >>done\n");
}

void USBWakeUp_IRQHandler(void)
{
  printf("\nIRQHandler  >>USBWakeUp_IRQHandler()  >>done\n");
}
