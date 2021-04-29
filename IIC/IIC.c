#include "IIC.h"

void IIC_Init(void)
{
  RCC_APB2PeriphClockCmd(IIC_RCC_GPIO,ENABLE);
  GPIO_InitTypeDef ss;
  ss.GPIO_Mode=GPIO_Mode_Out_OD;
  ss.GPIO_Pin=SDA|SCL;
  ss.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(IIC_GPIO,&ss);
  
  IIC_SDA_1();
  IIC_SCL_1();
}

void IIC_Start(void)
{
  IIC_SCL_1();
  IIC_SDA_1();
  IIC_SDA_0();
	IIC_SCL_0();
}

void IIC_Stop(void)
{
  IIC_SCL_1();
  IIC_SDA_0();
	IIC_SDA_1();
}

unsigned char IIC_Wait_Ack()
{
  unsigned char ack=1,i=0;
  IIC_SDA_1();
  IIC_SCL_1();
  while((ack==1)&&(i++<255))
  ack=IIC_SDA_READ();
  IIC_SCL_0();
  return ack;
}

void IIC_Send_Ack(char ack)
{
  if(ack==0)
    IIC_SDA_0();
  else
    IIC_SDA_1();
  IIC_SCL_1();
  IIC_SCL_0();
}

unsigned char IIC_SendByte(unsigned char data)
{
  unsigned int a=0;
  IIC_SCL_0();
  for(a=0;a<8;a++)
  {
    if(data>>7)
      IIC_SDA_1();
    else
      IIC_SDA_0();
    IIC_SCL_1();
    IIC_SCL_0();
    data<<=1;
  }
  return IIC_Wait_Ack();
}

unsigned char IIC_ReadByte(void)
{
  unsigned char a=0,data=0;
  IIC_SCL_0();
  IIC_SDA_1();
  for(a=0;a<8;a++)
  {
    IIC_SCL_1();
    data<<=1;
    data|=IIC_SDA_READ();
    IIC_SCL_0();
  }
  IIC_Send_Ack(0);
  return data;
}

