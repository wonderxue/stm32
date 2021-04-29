#include <stm32f10x.h>
#include "usart.h"
#include "ADC_D_S.h"
#include "LED.h"
#include "user_it.h"

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint32_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL*2];        

void delay()
{
  int a;
  for(a=0;a<8000000;a++);
}

int main()
{
  uint16_t temp0=0 ,temp1=0;
  USART_Config();
  printf("\nFunction  >>USART_Config()  >>done\n");
  ADCx_Init();
  printf("\nFunction  >>ADCx_Init()  >>done\n");
  LED_Init();
  printf("\nFunction  >>LED_Init()  >>done\n");
  while(1)
  {
    // 取出ADC1数据寄存器的高16位，这个是ADC2的转换数据
		temp0 = (ADC_ConvertedValue[0]&0XFFFF0000) >> 16;
		// 取出ADC1数据寄存器的低16位，这个是ADC1的转换数据
		temp1 = (ADC_ConvertedValue[0]&0XFFFF);	
		
		ADC_ConvertedValueLocal[0] =(float) temp0/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) temp1/4096*3.3;
		
		printf("\r\n ADCx_1 value = %f V \r\n",
		        ADC_ConvertedValueLocal[1]);
		printf("\r\n ADCx_2 value = %f V \r\n",
		        ADC_ConvertedValueLocal[0]);
		
		printf("\r\n\r\n");
		delay(); 
  }
}
