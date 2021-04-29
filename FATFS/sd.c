#include "sd.h"
unsigned char SD_Type=0;
//ȡ��Ƭѡ �ͷ�SPI����
void SD_DisSelect(void)
{
  SPI_CS_Disable;
  SPI_ReadWrite_Byte(0xff);
}

//�ȴ���׼����
//׼�����˷���ֵ0�������������
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

//ѡ��SD�����ȴ���׼����
//����ֵ 0�ɹ���1ʧ��
unsigned char SD_Select(void)
{
  SPI_CS_Enable;
  if(SD_WaitReady()==0)return 0;
  SD_DisSelect();
  return 1;
}

//�����Ӧ
//Response Ҫ�õ��Ļ�Ӧ?
//������Ӧ����
unsigned char SD_GetResponse(unsigned char Response)
{
  unsigned long Count=0xFFFF;   		//�ȴ�����
  SD_Select (); 
  while ((SPI_ReadWrite_Byte(0xff)!=Response)&&Count)Count--;	  
  if (Count==0)return MSD_RESPONSE_FAILURE;  
  else return MSD_RESPONSE_NO_ERROR;
}

//��SD����ȡһ�����ݰ�������
//buf���ݻ�����
//len��ȡ�����ݳ���
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

//��SD��д��һ�����ݰ�������512�ֽ�
//buf���ݻ���
//����
//����ֵ0�ɹ� ����ʧ��
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

//��SD������һ������
//unsigned char cmd  ����
//unsigned int arg �������
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

//��ȡSD����CID��Ϣ���� ������������Ϣ
//unsigned char *cid_data	���CID���ڴ�����16���ֽ�
//���� 0:NO_ERR
//		 1:����														   
unsigned char SD_GetCID(unsigned char *cid_data)
{
  unsigned char r1;	   
  r1=SD_SendCmd(CMD10,0,0x01);
  if(r1==0x00)
  {
	r1=SD_RecvData(cid_data,16);	//����16���ֽڵ����� 
  }
  SD_DisSelect();
  if(r1)return 1;
  else return 0;
}		

//��ȡSD����CSD��Ϣ���� �����������ٶ���Ϣ
//unsigned char *cid_data	���CsD���ڴ�����16���ֽ�
//���� 0:NO_ERR
//		 1:����														   
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

//��ȡSD����������
//����ֵ:0: ȡ����������
//����:SD����(������/512�ֽ�)														  
unsigned int SD_GetSectorCount(void)
{
  unsigned char csd[16];
  unsigned int Capacity;  
  unsigned char n;
  unsigned long csize;  					    
  //ȡCSD��Ϣ
  if(SD_GetCSD(csd)!=0) return 0;	    
    
  if((csd[0]&0xC0)==0x40)	 //V2.00��
  {	
	 csize = csd[9] + ((unsigned long)csd[8] << 8) + 1;
	 Capacity = (unsigned int)csize << 10;//�õ�������		   
  }else//V1.XX��
   {	
	  n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
	  csize = (csd[8] >> 6) + ((unsigned long)csd[7] << 2) + ((unsigned long)(csd[6] & 3) << 10) + 1;
	  Capacity= (unsigned int)csize << (n - 9);//�õ������� 
   }
   return Capacity;
}

//��ʼ��SD
unsigned char SD_Init(void)
{
  unsigned char r1;      // 
  unsigned long retry;  // 
  unsigned char buf[4];  
  unsigned long i;
  
  User_SPI_Init();
  SD_Select();
  
  for(i=0;i<10;i++)SPI_ReadWrite_Byte(0XFF);//��������74������
  retry=20;
  do
  {
	 r1=SD_SendCmd(CMD0,0,0x95);//����IDLE״̬
   }while((r1!=0X01) && retry--);
  SD_Type=0;//Ĭ���޿�
  
  if(r1==0X01)
   {
	  if(SD_SendCmd(CMD8,0x1AA,0x87)==1)//SD V2.0
	  {
		for(i=0;i<4;i++)buf[i]=SPI_ReadWrite_Byte(0XFF);	//Get trailing return value of R7 resp
		if(buf[2]==0X01&&buf[3]==0XAA)//���Ƿ�֧��2.7~3.6V
		{
		  retry=0XFFFE;
		  do
		  {
			 SD_SendCmd(CMD55,0,0X01);	//����CMD55
			 r1=SD_SendCmd(CMD41,0x40000000,0X01);//����CMD41
		    }while(r1&&retry--);
		  if(retry&&SD_SendCmd(CMD58,0,0X01)==0)//����SD2.0��ʼ
		  {
			 for(i=0;i<4;i++)buf[i]=SPI_ReadWrite_Byte(0XFF);//�õ�OCRֵ
			 if(buf[0]&0x40)SD_Type=SD_TYPE_V2HC;    //���CCS
			  else SD_Type=SD_TYPE_V2;   
		    }
		 }
		}else//SD V1.x/ MMC	V3
		{
		  SD_SendCmd(CMD55,0,0X01);		//����CMD55
		  r1=SD_SendCmd(CMD41,0,0X01);	//����CMD41
		  if(r1<=1)
		  {		
			SD_Type=SD_TYPE_V1;
			retry=0XFFFE;
			do 
			{
			  SD_SendCmd(CMD55,0,0X01);	//����CMD55
			  r1=SD_SendCmd(CMD41,0,0X01);//����CMD41
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

//unsigned char*buf���ݻ���
//sector��ʼ����
//������
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
