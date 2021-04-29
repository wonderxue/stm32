#include "spi.h"

void User_SPI_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitTypeDef CS_GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  RCC_APB2PeriphClockCmd(	User_RCC_APB2Periph_GPIO, ENABLE );//PORTBʱ��ʹ��
  RCC_APB2PeriphClockCmd(	User_SPI_CS_RCC, ENABLE );
  RCC_APB1PeriphClockCmd(	User_RCC_APB1Periph_SPI,  ENABLE );//SPI2ʱ��ʹ��

  GPIO_InitStructure.GPIO_Pin = User_SPI_SCK | User_SPI_MISO | User_SPI_MOSI;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(User_SPI_GPIO, &GPIO_InitStructure);//��ʼ��GPIOB

  GPIO_InitStructure.GPIO_Pin =User_SPI_CS_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(User_SPI_CS_GPIO, &CS_GPIO_InitStructure);
  
  GPIO_SetBits(User_SPI_GPIO,User_SPI_SCK | User_SPI_MISO | User_SPI_MOSI);  //PB13/14/15����
  SPI_CS_Disable;
  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
  SPI_InitStructure.SPI_CPOL = User_SPI_CPOL;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
  SPI_InitStructure.SPI_CPHA = User_SPI_CPHA;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
  SPI_InitStructure.SPI_BaudRatePrescaler = User_SPI_Speed;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
  SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
  SPI_Init(User_SPI, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���

  SPI_Cmd(User_SPI, ENABLE); //ʹ��SPI����
}

unsigned char SPI_ReadWriteByte(unsigned char TxData)
{
  unsigned char retry=0;
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
  {
    retry++;
    if(retry>200)return 0;
  }
  SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
  retry=0;

  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
  {
    retry++;
    if(retry>200)return 0;
  }
  return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����
}

void User_SPI_SetSpeed(unsigned char SPI_Speed)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_Speed));//�ж���Ч��
  User_SPI->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
  User_SPI->CR1|=SPI_Speed;	//����SPI2�ٶ� 
  SPI_Cmd(User_SPI,ENABLE); //ʹ��SPI1
}

