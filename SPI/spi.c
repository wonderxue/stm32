#include "spi.h"

void User_SPI_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitTypeDef CS_GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  RCC_APB2PeriphClockCmd(	User_RCC_APB2Periph_GPIO, ENABLE );//PORTB时钟使能
  RCC_APB2PeriphClockCmd(	User_SPI_CS_RCC, ENABLE );
  RCC_APB1PeriphClockCmd(	User_RCC_APB1Periph_SPI,  ENABLE );//SPI2时钟使能

  GPIO_InitStructure.GPIO_Pin = User_SPI_SCK | User_SPI_MISO | User_SPI_MOSI;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(User_SPI_GPIO, &GPIO_InitStructure);//初始化GPIOB

  GPIO_InitStructure.GPIO_Pin =User_SPI_CS_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(User_SPI_CS_GPIO, &CS_GPIO_InitStructure);
  
  GPIO_SetBits(User_SPI_GPIO,User_SPI_SCK | User_SPI_MISO | User_SPI_MOSI);  //PB13/14/15上拉
  SPI_CS_Disable;
  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
  SPI_InitStructure.SPI_CPOL = User_SPI_CPOL;		//串行同步时钟的空闲状态为高电平
  SPI_InitStructure.SPI_CPHA = User_SPI_CPHA;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
  SPI_InitStructure.SPI_BaudRatePrescaler = User_SPI_Speed;		//定义波特率预分频的值:波特率预分频值为256
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
  SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
  SPI_Init(User_SPI, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

  SPI_Cmd(User_SPI, ENABLE); //使能SPI外设
}

unsigned char SPI_ReadWriteByte(unsigned char TxData)
{
  unsigned char retry=0;
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
  {
    retry++;
    if(retry>200)return 0;
  }
  SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
  retry=0;

  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
  {
    retry++;
    if(retry>200)return 0;
  }
  return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据
}

void User_SPI_SetSpeed(unsigned char SPI_Speed)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_Speed));//判断有效性
  User_SPI->CR1&=0XFFC7;//位3-5清零，用来设置波特率
  User_SPI->CR1|=SPI_Speed;	//设置SPI2速度 
  SPI_Cmd(User_SPI,ENABLE); //使能SPI1
}

