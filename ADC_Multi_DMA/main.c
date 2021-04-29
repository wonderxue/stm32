#include <stm32f10x.h>
#include "usart.h"
#include "ADC_M_D.h"
#include "LED.h"
#include "user_it.h"

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];        

void delay()
{
  int a;
  for(a=0;a<2000000;a++);
}

int main()
{
  USART_Config();
  printf("\nFunction  >>USART_Config()  >>done\n");
  ADCx_Init();
  printf("\nFunction  >>ADCx_Init()  >>done\n");
  LED_Init();
  printf("\nFunction  >>LED_Init()  >>done\n");
  while(1)
  {
    ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
    printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
		printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
    delay();
  }
}
