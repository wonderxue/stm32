#include "stm32f10x.h"
#include "usart.h"
#include "spi.h"
#include "sd.h"
#include "diskio.h"
#include "ff.h"

FATFS fs; //FatFs文件系统对象
FIL fnew; //文件对象
FRESULT res_sd;//文件操作结果
UINT fnum; //文件成功读写数量
BYTE ReadBuffer[1024] = {0};
BYTE WriteBuffer[] = "you have succeed！\r\n"; //写缓存区
int main()
{
  USART_Config();
  if(SD_Init() == 0)
	{
		printf("SD卡初始化成功，即将挂载SD卡。\r\n");
	}else
  {
    printf("错误代码：%d\r\n",SD_Init());
  }
  res_sd = f_mount(&fs, "0:", 1);
  if(res_sd == FR_NO_FILESYSTEM)
	{
		printf("SD卡没有文件系统，即将进行格式化...\r\n");
		//格式化
		//res_sd = f_mkfs("0:", 0, 0);
		
		if(res_sd == FR_OK)
		{
			printf("SD卡成功格式化！\r\n");
			//格式化后先取消挂载
			res_sd = f_mount(NULL, "0:", 1);
			//再重新挂载
			res_sd = f_mount(&fs, "0:", 1);
		}
		else
		{
			printf("文件格式化失败！错误代码：%d\r\n",res_sd);
			while(1);
		}
	}
	else if(res_sd != FR_OK)
	{
		printf("挂载文件系统失败！可能是因为文件初始化失败！错误代码：%d\r\n", res_sd);
	}
	else
	{
		printf("文件系统挂载成功， 可进行读写测试！\r\n");
	}
	
	//***********************写测试****************************
	//打开文件，如果文件不存在则创建它
	printf("即将进行文件写入测试....\r\n");
	//打开文件，若不存在就创建
	res_sd = f_open(&fnew, "0:FatFs.txt", FA_CREATE_ALWAYS | FA_WRITE);
	//文件打开成功
	if(res_sd == FR_OK)
	{
		printf("打开文件成功！开始写入数据！\r\n");
		res_sd= f_write(&fnew, WriteBuffer, sizeof(WriteBuffer), &fnum);
		
		if(res_sd == FR_OK)
		{
			printf("数据写入成功！\r\n");
			printf("数据：%s。共写入%d个字符\r\n", WriteBuffer, fnum);
		}
		else
		{
			printf("数据写入失败！\r\n");
		}
		
		//关闭文件
		f_close(&fnew);
	}
	
	//***********************读测试****************************
	//打开文件，如果文件不存在则创建它
	printf("即将进行文件读取测试....\r\n");
	//打开文件，若不存在就创建
	res_sd = f_open(&fnew, "0:FatFs.txt", FA_OPEN_EXISTING | FA_READ);
	//文件打开成功
	if(res_sd == FR_OK)
	{
		printf("打开文件成功！开始读取数据！\r\n");
		res_sd= f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
		
		if(res_sd == FR_OK)
		{
			printf("数据读取成功！\r\n");
			printf("数据：%s\r\n", ReadBuffer);
		}
		else
		{
			printf("数据读取失败！\r\n");
		}
		
		//关闭文件
		f_close(&fnew);
	}
	
//	scan_files("FatFs读写测试文件.txt");
//	
//	//其他功能测试
//	file_check();
//	
//	//多项功能测试
//	miscellaneous();
//	
	//取消挂载文件系统
	f_mount(NULL, "0:", 1);
	
	while(1);
}