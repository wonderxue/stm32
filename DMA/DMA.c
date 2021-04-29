#include "DMA.h"

char SendData[BUFFER_SIZE];
void DMA_Config(void)
{
	  DMA_InitTypeDef DMA_InitStructure;
	
		// 开启DMA时钟
		RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);
		// 源数据地址
    DMA_InitStructure.DMA_PeripheralBaseAddr =USART_DR_ADDRESS;
		// 目标地址
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendData;
		// 方向：外设到存储器
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		// 传输大小	
		DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
		// 外设地址递增	    
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		// 内存地址递增
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		// 外设数据单位	
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		// 内存数据单位
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
		// DMA模式，一次或者循环模式
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
		// 优先级：高	
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		// 失能内存到内存的传输
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		// 配置DMA通道		   
		DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
    //清除DMA数据流传输完成标志位
    DMA_ClearFlag(DMA_FLAG_TC);
		// 使能DMA
		DMA_Cmd(DMA_CHANNEL,ENABLE);
}

