#include "oled.h"
#include "oledfont.h"
struct oled_dis_mode oled_dis_mode={0,1,2};
struct oled_frame oled_frame={0,1,2,3,4,5,6,7};
struct oled_dir oled_dir={0,1,2,3};
void oled_write_cmd(unsigned char cmd)
{
  IIC_Start();
  IIC_SendByte(oled_Adress);
	IIC_SendByte(0x00);//cmd
	IIC_SendByte(cmd);
  IIC_Stop();
}

void oled_write_data(unsigned char data)
{
  IIC_Start();
  IIC_SendByte(oled_Adress);
	IIC_SendByte(0x40);//data
	IIC_SendByte(data);
  IIC_Stop();
}

void oled_cls()
{
	unsigned char i,j;
	for(i=0;i<8;i++)
	{
		oled_write_cmd(0xb0+i);
		for(j=0;j<128;j++)
		oled_write_data(0x00);
	}
}

void oled_on()
{
  oled_write_cmd(0x8D);
  oled_write_cmd(0x14);
  oled_write_cmd(0xAF);
}

void oled_off()
{
  oled_write_cmd(0x8D);
  oled_write_cmd(0x10);
  oled_write_cmd(0xAE);
}

void oled_init()
{
	oled_write_cmd(0xAE);//off-AE on-AF
	
	oled_write_cmd(0x20);//mode
	oled_write_cmd(0x02);//page
	
	oled_write_cmd(0x00);//low column
	oled_write_cmd(0x10);//high column
	oled_write_cmd(0x40);//line
	oled_write_cmd(0xb0);//page
	
	oled_write_cmd(0x81);//contrast control
	oled_write_cmd(0xFE);
	
	oled_write_cmd(0xA1);//set segment remap
	oled_write_cmd(0xA4);//with ram-A4  without ram-A5
	oled_write_cmd(0xA6);//normal-A6 reverse-A7
	oled_write_cmd(0xA8);//ratio 1-64
	oled_write_cmd(0x3F);
	oled_write_cmd(0xC8);//COM Scan Direction-C0 or C8
	
	oled_write_cmd(0xD3);//display offset
	oled_write_cmd(0x00);
	
	oled_write_cmd(0xD5);//Set Display Clock Divide Ration/Oscillator Frequency
	oled_write_cmd(0x80);//0-3 for Clock Divide Ration 4-7 for Oscillator Frequency
	
	oled_write_cmd(0xD8);//area color mode
	oled_write_cmd(0x05);
	
	oled_write_cmd(0xD9);//pre charge
	oled_write_cmd(0xF1);
	
	oled_write_cmd(0xDA);//pin configuartion
	oled_write_cmd(0x12);
	
	oled_write_cmd(0xDB);//VCOMH
	oled_write_cmd(0x30);
}

void oled_start_page(unsigned char pag,unsigned int seg)
{
	oled_write_cmd(0xb0+pag);
	oled_write_cmd(0x00+seg%16);
	oled_write_cmd(0x10+seg/16);
}

void oled_start_line(unsigned char line)
{
	oled_write_cmd(0x40+line);
}

void oled_set_pos(unsigned char x,unsigned char y)
{
  oled_write_cmd(0xb0+y);
  oled_write_cmd(((x&0xf0)>>4)|0x10);
  oled_write_cmd(x&0x0f);
}

void oled_area_horiz(unsigned int colu1,unsigned int colu2)
{
	oled_write_cmd(0x21);
	oled_write_cmd(colu1);
	oled_write_cmd(colu2);
}

void oled_area_verti(unsigned int page1,unsigned int page2)
{
	oled_write_cmd(0x22);
	oled_write_cmd(page1);
	oled_write_cmd(page2);
}

void oled_display_mode(unsigned char mode)
{
	oled_write_cmd(0x20);
	oled_write_cmd(mode);
}

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';			
		if(x>127){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			oled_set_pos(x,y);	
			for(i=0;i<8;i++)
			oled_write_data(F8X16[c*16+i]);
			oled_set_pos(x,y+1);
			for(i=0;i<8;i++)
			oled_write_data(F8X16[c*16+i+8]);
			}
			else {	
				oled_set_pos(x,y);
				for(i=0;i<6;i++)
				oled_write_data(F6x8[c][i]);
				
			}
}

u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		oled_set_pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	oled_write_data(BMP[j++]);	    	
	    }
	}
} 
void OLED_SCROLL(unsigned char dir,unsigned char frame,unsigned char vs_page,unsigned char vd_page,unsigned char row)
{
  oled_write_cmd(0x2E);
  //hor
  if (dir<2)
  {
    oled_write_cmd(0x26+dir);
    oled_write_cmd(0);
    oled_write_cmd(vs_page);
    oled_write_cmd(frame);
    oled_write_cmd(vd_page);
  }
  else
  {
    oled_write_cmd(0x29+dir-2);
    oled_write_cmd(0);
    oled_write_cmd(vs_page);
    oled_write_cmd(frame);
    oled_write_cmd(vd_page);
    oled_write_cmd(row);
  }
  oled_write_cmd(0x2F);  
}