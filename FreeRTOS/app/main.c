#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "stm32f10x.h"
#include "LED.h"
#include "task.h" 
#include "queue.h" 
#include "list.h"  
#include "portable.h"

unsigned char ucHeap [configTOTAL_HEAP_SIZE];
TaskHandle_t led;
TaskHandle_t led1;
TaskHandle_t start;
void led_Task(void *pvParameters)
{
  while(1)
  {
    LED_ON;
    vTaskDelay(2000);
    LED_OFF;
    vTaskDelay(2000);
  }
}

void led_Task2(void *pvParameters)
{
  while(1)
  {
    LED_ON;
    vTaskDelay(500);
    LED_OFF;
    vTaskDelay(500);
  }
}

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )led_Task,         
                (const char*    )"led0_task",       
                (uint16_t       )50, 
                (void*          )NULL,              
                (UBaseType_t    )2,    
                (TaskHandle_t*  )&led);   
    //����LED1����
    xTaskCreate((TaskFunction_t )led_Task2,     
                (const char*    )"led1_task",   
                (uint16_t       )50, 
                (void*          )NULL,
                (UBaseType_t    )3,
                (TaskHandle_t*  )&led1);        
   
    vTaskDelete(start); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

int main()
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  LED_Init();
  
  xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )128,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )1,       //�������ȼ�
                (TaskHandle_t*  )&start);   //������              
    vTaskStartScheduler(); 
}
