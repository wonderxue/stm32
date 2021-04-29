#include "stm32f10x.h"
#include "spi.h"
#include "usart.h"

int main()
{
  User_SPI_Init();
  USART_Config();
}
