#include <stm32f10x.h>
#include "DMA.h"
#include "usart.h"
extern char SendData[BUFFER_SIZE];
int main()
{
  int a=0;
  for(a=0;a<BUFFER_SIZE;a++)
  {
    SendData[a]='a';
  }
  USART_Config();
  DMA_Config();
  USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);
  while(1);
}
