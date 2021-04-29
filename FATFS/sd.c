#include "sd.h"
unsigned char SD_Type=0;
//取消片选 释放SPI总线
void SD_DisSelect(void)
{
  SPI_CS_Disable;
  SPI_ReadWrite_Byte(0xff);
}

//等待卡准备好
//准备好了返回值0；其他错误代码
unsigned char SD_WaitReady(void)
{
  unsigned int t=0;
  do
  {
	if(SPI_ReadWrite_Byte(0xff)==0XFF)return 0;//OK
	t++;		  	
  }while(t<0XFFFFFF);
  return 1;
}

//选择SD卡并等待卡准备好
//返回值 0成功，1失败
unsigned char SD_Select(void)
{
  SPI_CS_Enable;
  if(SD_WaitReady()==0)return 0;
  SD_DisSelect();
  return 1;
}

//获得响应
//Response 要得到的回应?
//其他响应错误
unsigned char SD_GetResponse(unsigned char Response)
{
  unsigned long Count=0xFFFF;   		//等待次数
  SD_Select (); 
  while ((SPI_ReadWrite_Byte(0xff)!=Response)&&Count)Count--;	  
  if (Count==0)return MSD_RESPONSE_FAILURE;  
  else return MSD_RESPONSE_NO_ERROR;
}

//从SD卡读取一个数据包的内容
//buf数据缓存区
//len读取的数据长度
unsigned char SD_RecvData(unsigned char*buf,unsigned long len)
{	
  SD_Select ();   
  if(SD_GetResponse(0xFE))return 1;
  while(len--)
  {
    *buf=SPI_ReadWrite_Byte(0xff);
     buf++;
  }
  SPI_ReadWrite_Byte(0xff);
  SPI_ReadWrite_Byte(0xff);									  					    
  return 0;
}

//向SD卡写入一个数据包的内容512字节
//buf数据缓存
//命令
//返回值0成功 其他失败
unsigned char SD_SendBlock(unsigned char*buf,unsigned char cmd)
{	
  unsigned long t;	
  SD_Select ();   
  if(SD_WaitReady())return 1;
  SPI_ReadWrite_Byte(cmd);
  if(cmd!=0XFD)
  {
	for(t=0;t<512;t++)SPI_ReadWrite_Byte(buf[t]);
	SPI_ReadWrite_Byte(0xFF);
	SPI_ReadWrite_Byte(0xFF);
	t=SPI_ReadWrite_Byte(0xFF);
	if((t&0x1F)!=0x05)return 2;								  					    
   }						 									  					    
  return 0;
}

//向SD卡发送一个命令
//unsigned char cmd  命令
//unsigned int arg 命令参数
unsigned char SD_SendCmd(unsigned char cmd, unsigned int arg, unsigned char crc)
{
  unsigned char r1;	
  unsigned char Retry=0; 
  SD_DisSelect();
  if(SD_Select())return 0XFF;
    SPI_ReadWrite_Byte(cmd | 0x40);
    SPI_ReadWrite_Byte(arg >> 24);
    SPI_ReadWrite_Byte(arg >> 16);
    SPI_ReadWrite_Byte(arg >> 8);
    SPI_ReadWrite_Byte(arg);	  
    SPI_ReadWrite_Byte(crc); 
  if(cmd==CMD12) SPI_ReadWrite_Byte(0xff);//Skip a stuff byte when stop reading
	Retry=0X1F;
  do
   {
	 r1=SPI_ReadWrite_Byte(0xFF);
   }while((r1&0X80) && Retry--);	 
  return r1;
}

//获取SD卡的CID信息包括 包括制造商信息
//unsigned char *cid_data	存放CID的内存至少16个字节
//返回 0:NO_ERR
//		 1:错误														   
unsigned char SD_GetCID(unsigned char *cid_data)
{
  unsigned char r1;	   
  r1=SD_SendCmd(CMD10,0,0x01);
  if(r1==0x00)
  {
	r1=SD_RecvData(cid_data,16);	//接收16个字节的数据 
  }
  SD_DisSelect();
  if(r1)return 1;
  else return 0;
}		

//获取SD卡的CSD信息包括 包括容量和速度信息
//unsigned char *cid_data	存放CsD的内存至少16个字节
//返回 0:NO_ERR
//		 1:错误														   
unsigned char SD_GetCSD(unsigned char *csd_data)
{
  unsigned char r1;	 
  r1=SD_SendCmd(CMD9,0,0x01);
  if(r1==0)
  {
     r1=SD_RecvData(csd_data, 16); 
   }
  SD_DisSelect();
  if(r1)return 1;
  else return 0;
}  

//获取SD卡总扇区数
//返回值:0: 取出容量出错
//其他:SD容量(扇区数/512字节)														  
unsigned int SD_GetSectorCount(void)
{
  unsigned char csd[16];
  unsigned int Capacity;  
  unsigned char n;
  unsigned long csize;  					    
  //取CSD信息
  if(SD_GetCSD(csd)!=0) return 0;	    
    
  if((csd[0]&0xC0)==0x40)	 //V2.00卡
  {	
	 csize = csd[9] + ((unsigned long)csd[8] << 8) + 1;
	 Capacity = (unsigned int)csize << 10;//得到扇区数		   
  }else//V1.XX卡
   {	
	  n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
	  csize = (csd[8] >> 6) + ((unsigned long)csd[7] << 2) + ((unsigned long)(csd[6] & 3) << 10) + 1;
	  Capacity= (unsigned int)csize << (n - 9);//得到扇区数 
   }
   return Capacity;
}

//初始化SD
unsigned char SD_Init(void)
{
  unsigned char r1;      // 
  unsigned long retry;  // 
  unsigned char buf[4];  
  unsigned long i;
  
  User_SPI_Init();
  SD_Select();
  
  for(i=0;i<10;i++)SPI_ReadWrite_Byte(0XFF);//发送至少74个脉冲
  retry=20;
  do
  {
	 r1=SD_SendCmd(CMD0,0,0x95);//进入IDLE状态
   }while((r1!=0X01) && retry--);
  SD_Type=0;//默认无卡
  
  if(r1==0X01)
   {
	  if(SD_SendCmd(CMD8,0x1AA,0x87)==1)//SD V2.0
	  {
		for(i=0;i<4;i++)buf[i]=SPI_ReadWrite_Byte(0XFF);	//Get trailing return value of R7 resp
		if(buf[2]==0X01&&buf[3]==0XAA)//卡是否支持2.7~3.6V
		{
		  retry=0XFFFE;
		  do
		  {
			 SD_SendCmd(CMD55,0,0X01);	//发送CMD55
			 r1=SD_SendCmd(CMD41,0x40000000,0X01);//发送CMD41
		    }while(r1&&retry--);
		  if(retry&&SD_SendCmd(CMD58,0,0X01)==0)//鉴别SD2.0开始
		  {
			 for(i=0;i<4;i++)buf[i]=SPI_ReadWrite_Byte(0XFF);//得到OCR值
			 if(buf[0]&0x40)SD_Type=SD_TYPE_V2HC;    //检测CCS
			  else SD_Type=SD_TYPE_V2;   
		    }
		 }
		}else//SD V1.x/ MMC	V3
		{
		  SD_SendCmd(CMD55,0,0X01);		//发送CMD55
		  r1=SD_SendCmd(CMD41,0,0X01);	//发送CMD41
		  if(r1<=1)
		  {		
			SD_Type=SD_TYPE_V1;
			retry=0XFFFE;
			do 
			{
			  SD_SendCmd(CMD55,0,0X01);	//发送CMD55
			  r1=SD_SendCmd(CMD41,0,0X01);//发送CMD41
			}while(r1&&retry--);
		  }else
		     {
			   SD_Type=SD_TYPE_MMC;//MMC V3
			   retry=0XFFFE;
			   do 
			    {											    
				  r1=SD_SendCmd(CMD1,0,0X01);
			     }while(r1&&retry--);  
		   }
		  if(retry==0||SD_SendCmd(CMD16,512,0X01)!=0)SD_Type=SD_TYPE_ERR;
		}
   }
  SD_DisSelect();
  User_SPI_SetSpeed(SPI_BaudRatePrescaler_2);
  if(SD_Type)return 0;
  else if(r1)return r1; 	   
  return 0xaa;
}

unsigned char SD_ReadDisk2(unsigned char*buf,unsigned int sector,unsigned char cnt)
{
  unsigned char r1;
  if(SD_Type!=SD_TYPE_V2HC)sector <<= 9;
  if(cnt==1)
  {
	r1=SD_SendCmd(CMD17,sector,0X01);
	if(r1==0)
	{
	  r1=SD_RecvData(buf,512);	   
	}
  }else
    {
	   r1=SD_SendCmd(CMD18,sector,0X01);
	   do
	   {
		  r1=SD_RecvData(buf,512);	 
		  buf+=512;  
		}while(--cnt && r1==0); 	
	   SD_SendCmd(CMD12,0,0X01);	
	 }   
  SD_DisSelect();
  return r1;
}

//unsigned char*buf数据缓存
//sector起始扇区
//扇区数
unsigned char SD_WriteDisk2(unsigned char*buf,unsigned int sector,unsigned char cnt)
{
  unsigned char r1;
  if(SD_Type!=SD_TYPE_V2HC)sector *= 512;
  if(cnt==1)
  {
	 r1=SD_SendCmd(CMD24,sector,0X01);
	 if(r1==0)
	 {
		r1=SD_SendBlock(buf,0xFE);  
	  }
   }else
    {
	  if(SD_Type!=SD_TYPE_MMC)
	   {
		  SD_SendCmd(CMD55,0,0X01);	
		  SD_SendCmd(CMD23,cnt,0X01);
		}
 	  r1=SD_SendCmd(CMD25,sector,0X01);
	  if(r1==0)
	  {
		do
		{
		  r1=SD_SendBlock(buf,0xFC);	 
		  buf+=512;  
		 }while(--cnt && r1==0);
		 r1=SD_SendBlock(0,0xFD);
		}
	}   
  SD_DisSelect();
  return r1;
}	
