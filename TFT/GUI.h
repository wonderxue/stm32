#ifndef __GUI_H__
#define __GUI_H__

#include "TFT.h"

unsigned short TFT_BGR2RGB(unsigned short c);
void Gui_Circle(unsigned short X,unsigned short Y,unsigned short R,unsigned short fc); 
void Gui_DrawLine(unsigned short x0, unsigned short y0,unsigned short x1, unsigned short y1,unsigned short Color);  
void Gui_box(unsigned short x, unsigned short y, unsigned short w, unsigned short h,unsigned short bc);
void Gui_box2(unsigned short x,unsigned short y,unsigned short w,unsigned short h, unsigned char mode);
void showimage(unsigned short x,unsigned short y,unsigned char width,unsigned char height,const unsigned char *p);

#endif  //__GUI_H__
