#ifndef __OLED_H__
#define __OLED_H__
#include "i2c.h"

//Device Information
#define oled_Adress 0x3c

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
void oled_fill(void);
void oled_off(void);
void oled_on(void);
void oled_start_page(unsigned char pag, unsigned int seg);
void oled_area_horiz(unsigned int colu1, unsigned int colu2);
void oled_area_verti(unsigned int page1, unsigned int page2);
void oled_start_line(unsigned char line);
void oled_set_pos(unsigned char x, unsigned char y);
void oled_display_mode(unsigned char mode);
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char chr, unsigned char Char_Size);
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len, unsigned char size2);
void OLED_ShowString(unsigned char x, unsigned char y, unsigned char *chr, unsigned char Char_Size);
void OLED_SCROLL(unsigned char dir, unsigned char frame, unsigned char vs_page, unsigned char vd_page, unsigned char row);
#endif //__OLED_H__