#include <stm32f10x.h>
#include "usart.h"
#include "ADC_D_S.h"
#include "LED.h"
#include "user_it.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint32_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
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
    // ȡ��ADC1���ݼĴ����ĸ�16λ�������ADC2��ת������
		temp0 = (ADC_ConvertedValue[0]&0XFFFF0000) >> 16;
		// ȡ��ADC1���ݼĴ����ĵ�16λ�������ADC1��ת������
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
