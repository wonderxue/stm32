#include "RCC_Config.h"
void RCC_HSE_Config(u32 PllMul)
{
  //��λRCC�Ĵ���
  RCC_DeInit();
  //ʹ��HSE
  RCC_HSEConfig(RCC_HSE_ON);
  
  if(RCC_WaitForHSEStartUp()==SUCCESS)
  {
    //ʹ��Ԥȡָ
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);
    //���÷�Ƶ,����RCC_SYSCLK=72MHz
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//72MHz
    RCC_PCLK1Config(RCC_SYSCLK_Div2);//36MHz
    RCC_PCLK2Config(RCC_SYSCLK_Div1);//72MHz
    //���໷����
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1,PllMul);
    //ʹ��pll
    RCC_PLLCmd(ENABLE);
    //�ȴ�pll�ȶ�
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
    //ѡ��ϵͳʱ��
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    //�ж��Ƿ�ɹ�
    while(RCC_GetSYSCLKSource()!=0x08);
  }
  else
  {
    //HSE����ʧ�ܣ��������
  }
}
