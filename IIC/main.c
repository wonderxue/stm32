#include "IIC.h"
#include "RCC_Config.h"
#include "usart.h"
#include "oled.h"//64*128
#include "pic.h"

int main()
{
  //int i,j=0;
  IIC_Init();
	oled_init();
  oled_on();
	oled_cls();
	oled_display_mode(oled_dis_mode.horiz);

  oled_area_verti(0,7);

	oled_area_horiz(0,127);
  OLED_ShowNum(0,0,23,8,16);
  //OLED_DrawBMP(0,0,128,128,a);
  //OLED_SCROLL(oled_dir.up_right,oled_frame.frame5,0,7,1);
  while(1)
  {
    //oled_write_data(0xff);
  }
}
