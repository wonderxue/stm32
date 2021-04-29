#include "GY_521.h"

struct GY_Config GY_Config={0x19,0x1a,0x1b,0x1c,0x6b};
struct Data_Read Data_Read={0x3b,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};

void GY_Write_Cmd(unsigned char reg_address,unsigned char cmd)
{
  IIC_Start();
  IIC_SendByte(GY_Adress);
  IIC_SendByte(reg_address);
  IIC_SendByte(cmd);
  IIC_Stop();
}

unsigned char GY_Read_Byte(unsigned char reg_address)
{
  unsigned char data;
  IIC_Start();
  IIC_SendByte(GY_Adress);
  IIC_SendByte(reg_address);
  IIC_Stop();
  IIC_Start();
  IIC_SendByte(GY_Adress+1);
  data=IIC_ReadByte();
  IIC_Stop();
  return data;
}

void GY_Init()
{
  GY_Write_Cmd(GY_Config.Pow_Manage,0x80);
  SysTick_delay_ms(100);
  GY_Write_Cmd(GY_Config.Pow_Manage,0x00);
  GY_Write_Cmd(GY_Config.Sample_Rate,0x07);
  GY_Write_Cmd(GY_Config.AC_Self_Check,0x01);//+/-2g
  GY_Write_Cmd(GY_Config.GY_Self_Check,0x18);//+/-2000/s
  GY_Write_Cmd(GY_Config.Low_Filter_Freq,0x06);
}

int GY_Read_Data(unsigned char reg_address)
{
  unsigned char H,L;
  int temp;
  H=GY_Read_Byte(reg_address);
  L=GY_Read_Byte(reg_address+1);
  temp=(H<<8)+L;
//  if(reg_address!=0x41)//ac
//  {
//    temp=temp-32768;
//  }
  return temp;
}
