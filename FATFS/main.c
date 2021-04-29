#include "stm32f10x.h"
#include "usart.h"
#include "spi.h"
#include "sd.h"
#include "diskio.h"
#include "ff.h"

FATFS fs; //FatFs�ļ�ϵͳ����
FIL fnew; //�ļ�����
FRESULT res_sd;//�ļ��������
UINT fnum; //�ļ��ɹ���д����
BYTE ReadBuffer[1024] = {0};
BYTE WriteBuffer[] = "you have succeed��\r\n"; //д������
int main()
{
  USART_Config();
  if(SD_Init() == 0)
	{
		printf("SD����ʼ���ɹ�����������SD����\r\n");
	}else
  {
    printf("������룺%d\r\n",SD_Init());
  }
  res_sd = f_mount(&fs, "0:", 1);
  if(res_sd == FR_NO_FILESYSTEM)
	{
		printf("SD��û���ļ�ϵͳ���������и�ʽ��...\r\n");
		//��ʽ��
		//res_sd = f_mkfs("0:", 0, 0);
		
		if(res_sd == FR_OK)
		{
			printf("SD���ɹ���ʽ����\r\n");
			//��ʽ������ȡ������
			res_sd = f_mount(NULL, "0:", 1);
			//�����¹���
			res_sd = f_mount(&fs, "0:", 1);
		}
		else
		{
			printf("�ļ���ʽ��ʧ�ܣ�������룺%d\r\n",res_sd);
			while(1);
		}
	}
	else if(res_sd != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�ܣ���������Ϊ�ļ���ʼ��ʧ�ܣ�������룺%d\r\n", res_sd);
	}
	else
	{
		printf("�ļ�ϵͳ���سɹ��� �ɽ��ж�д���ԣ�\r\n");
	}
	
	//***********************д����****************************
	//���ļ�������ļ��������򴴽���
	printf("���������ļ�д�����....\r\n");
	//���ļ����������ھʹ���
	res_sd = f_open(&fnew, "0:FatFs.txt", FA_CREATE_ALWAYS | FA_WRITE);
	//�ļ��򿪳ɹ�
	if(res_sd == FR_OK)
	{
		printf("���ļ��ɹ�����ʼд�����ݣ�\r\n");
		res_sd= f_write(&fnew, WriteBuffer, sizeof(WriteBuffer), &fnum);
		
		if(res_sd == FR_OK)
		{
			printf("����д��ɹ���\r\n");
			printf("���ݣ�%s����д��%d���ַ�\r\n", WriteBuffer, fnum);
		}
		else
		{
			printf("����д��ʧ�ܣ�\r\n");
		}
		
		//�ر��ļ�
		f_close(&fnew);
	}
	
	//***********************������****************************
	//���ļ�������ļ��������򴴽���
	printf("���������ļ���ȡ����....\r\n");
	//���ļ����������ھʹ���
	res_sd = f_open(&fnew, "0:FatFs.txt", FA_OPEN_EXISTING | FA_READ);
	//�ļ��򿪳ɹ�
	if(res_sd == FR_OK)
	{
		printf("���ļ��ɹ�����ʼ��ȡ���ݣ�\r\n");
		res_sd= f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
		
		if(res_sd == FR_OK)
		{
			printf("���ݶ�ȡ�ɹ���\r\n");
			printf("���ݣ�%s\r\n", ReadBuffer);
		}
		else
		{
			printf("���ݶ�ȡʧ�ܣ�\r\n");
		}
		
		//�ر��ļ�
		f_close(&fnew);
	}
	
//	scan_files("FatFs��д�����ļ�.txt");
//	
//	//�������ܲ���
//	file_check();
//	
//	//����ܲ���
//	miscellaneous();
//	
	//ȡ�������ļ�ϵͳ
	f_mount(NULL, "0:", 1);
	
	while(1);
}