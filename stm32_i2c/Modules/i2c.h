#ifndef __I2C_H__
#define __I2C_H__

#include "gpio.h"
#include "main.h"
//硬件配置
#define SDA     13
#define SCL     12
#define SCL_L   HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,RESET)
#define SCL_H   HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,SET)
#define SDA_L   HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,RESET)
#define SDA_H   HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,SET)
#define SDA_In  SDAIn()
#define SDA_Out SDAOut()
#define SDA_Read HAL_GPIO_ReadPin(SDA_GPIO_Port,SDA_Pin)
#define i2cDelay(x) delay_us(x)
extern void delay_us(int us);
//功能定义
unsigned char begin(unsigned short dev_addr);
_Bool writeByte(unsigned char fid,unsigned char data);
_Bool writeRegByte(unsigned char fid,unsigned char reg_addr,unsigned char data);
unsigned char readbyte(unsigned char fid);
unsigned char readRegByte(unsigned char fid,unsigned char reg_addr);

#endif //__I2C_H__