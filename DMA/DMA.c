#include "DMA.h"

char SendData[BUFFER_SIZE];
void DMA_Config(void)
{
	  DMA_InitTypeDef DMA_InitStructure;
	
		// ����DMAʱ��
		RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);
		// Դ���ݵ�ַ
    DMA_InitStructure.DMA_PeripheralBaseAddr =USART_DR_ADDRESS;
		// Ŀ���ַ
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendData;
		// �������赽�洢��
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		// �����С	
		DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
		// �����ַ����	    
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		// �ڴ��ַ����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		// �������ݵ�λ	
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		// �ڴ����ݵ�λ
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
		// DMAģʽ��һ�λ���ѭ��ģʽ
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
		// ���ȼ�����	
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		// ʧ���ڴ浽�ڴ�Ĵ���
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		// ����DMAͨ��		   
		DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
    //���DMA������������ɱ�־λ
    DMA_ClearFlag(DMA_FLAG_TC);
		// ʹ��DMA
		DMA_Cmd(DMA_CHANNEL,ENABLE);
}

