#include "RCC_Config.h"
void RCC_HSE_Config(u32 PllMul)
{
  //复位RCC寄存器
  RCC_DeInit();
  //使能HSE
  RCC_HSEConfig(RCC_HSE_ON);
  
  if(RCC_WaitForHSEStartUp()==SUCCESS)
  {
    //使能预取指
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);
    //配置分频,假设RCC_SYSCLK=72MHz
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//72MHz
    RCC_PCLK1Config(RCC_SYSCLK_Div2);//36MHz
    RCC_PCLK2Config(RCC_SYSCLK_Div1);//72MHz
    //锁相环配置
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1,PllMul);
    //使能pll
    RCC_PLLCmd(ENABLE);
    //等待pll稳定
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
    //选择系统时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    //判断是否成功
    while(RCC_GetSYSCLKSource()!=0x08);
  }
  else
  {
    //HSE启动失败，处理代码
  }
}
