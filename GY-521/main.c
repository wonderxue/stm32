#include "stm32f10x.h"
#include "IIC.h"
#include "oled.h"
#include "GY_521.h"
#include "usart.h"


int main()
{
  int i;
  int a;
//  USART_Config();
  IIC_Init();
  oled_init();
  GY_Init();
//  printf("system init done\n");
//  printf("test %6.2f\n",-12.3);
  oled_on();
  oled_cls();
  oled_display_mode(oled_dis_mode.horiz);
  while(1)
  {
    OLED_ShowNum(0,0,GY_Read_Data(Data_Read.ACCEL_XOUT_H)/16.384,8,16);
    OLED_ShowNum(0,2,GY_Read_Data(Data_Read.ACCEL_YOUT_H)/16.384,8,16);
    OLED_ShowNum(0,4,GY_Read_Data(Data_Read.ACCEL_ZOUT_H)/16.384,8,16);
//    
//    OLED_ShowNum(60,0,GY_Read_Data(Data_Read.GYRO_XOUT_H)/16.384,8,16);
//    OLED_ShowNum(60,2,GY_Read_Data(Data_Read.GYRO_YOUT_H)/16.384,8,16);
//    OLED_ShowNum(60,4,GY_Read_Data(Data_Read.GYRO_ZOUT_H)/16.384,8,16);
//    printf("ax=%1.6f",GY_Read_Data(Data_Read.ACCEL_XOUT_H)/16384.0);
//    printf("ay=%1.6f",GY_Read_Data(Data_Read.ACCEL_YOUT_H)/16384.0);
//    printf("az=%1.6f",GY_Read_Data(Data_Read.ACCEL_ZOUT_H)/16384.0);
//    
//    printf("gx=%6.2f",GY_Read_Data(Data_Read.GYRO_XOUT_H)/16.384);
//    printf("gy=%6.2f",GY_Read_Data(Data_Read.GYRO_YOUT_H)/16.384);
//    printf("gz=%6.2f",GY_Read_Data(Data_Read.GYRO_ZOUT_H)/16.384);
//    printf("\n");
    for(i=0;i<2000;i++)
    for(a=0;a<2000;a++);
  }
}