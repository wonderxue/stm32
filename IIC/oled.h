#ifndef __OLED_H__
#define __OLED_H__

#include "IIC.h"


//Device Information
#define oled_Adress         0x78

struct oled_dis_mode
{
  unsigned char horiz;
  unsigned char verti;
  unsigned char page;
};
struct oled_frame
{
  unsigned char frame5;
  unsigned char frame64;
  unsigned char frame128;
  unsigned char frame256;
  unsigned char frame3;
  unsigned char frame4;
  unsigned char frame25;
  unsigned char frame2;
};

struct oled_dir
{
  unsigned char right;
  unsigned char left;
  unsigned char up_right;
  unsigned char uo_left;
};
extern struct oled_dis_mode oled_dis_mode;
extern struct oled_frame oled_frame; 
extern struct oled_dir oled_dir;
void oled_write_cmd(unsigned char cmd);
void oled_write_data(unsigned char data);
void oled_init(void);
void oled_cls(void);
void oled_off(void);
void oled_on(void);
void oled_start_page(unsigned char pag,unsigned int seg);
void oled_area_horiz(unsigned int colu1,unsigned int colu2);
void oled_area_verti(unsigned int page1,unsigned int page2);
void oled_start_line(unsigned char line);
void oled_set_pos(unsigned char x,unsigned char y);
void oled_display_mode(unsigned char mode);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_SCROLL(unsigned char dir,unsigned char frame,unsigned char vs_page,unsigned char vd_page,unsigned char row);
#endif  //__OLED_H__
