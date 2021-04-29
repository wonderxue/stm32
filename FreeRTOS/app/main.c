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
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )led_Task,         
                (const char*    )"led0_task",       
                (uint16_t       )50, 
                (void*          )NULL,              
                (UBaseType_t    )2,    
                (TaskHandle_t*  )&led);   
    //创建LED1任务
    xTaskCreate((TaskFunction_t )led_Task2,     
                (const char*    )"led1_task",   
                (uint16_t       )50, 
                (void*          )NULL,
                (UBaseType_t    )3,
                (TaskHandle_t*  )&led1);        
   
    vTaskDelete(start); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

int main()
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  LED_Init();
  
  xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )128,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )1,       //任务优先级
                (TaskHandle_t*  )&start);   //任务句柄              
    vTaskStartScheduler(); 
}
