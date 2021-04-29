#include <stm32f10x.h>
#include "usart.h"
#include "ADC_S_D.h"
#include "LED.h"
#include "user_it.h"

extern __IO uint16_t ADC_ConvertedValue;
float ADC_ConvertedValueLocal; 

void delay()
{
  int a;
  for(a=0;a<2000000;a++);
}

int main()
{
	// ���ô���
	USART_Config();
	printf("\nFunction  >>USART_Config()  >>done\n");
  LED_Init();
  printf("\nFunction  >>LED_Init()  >>done\n");
	// ADC ��ʼ��
	ADCx_Init();
	printf("\nFunction  >>ADCx_Init()  >>done\n");
	
	while (1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
	
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

		delay();  
	}
}
