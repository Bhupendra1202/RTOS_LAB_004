#include <stdio.h>
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h"
#include "freertos/queue.h"

#define MQ_len 4
#define MQ_size 64

TaskHandle_t task1_handler,task2_handler,task3_handler,task4_handler,task5_handler;
QueueHandle_t MES_qu;
void rt_task1(void *data)
{

    printf("Inside Task1 & periodicity time 1000ms\n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    //pdMS_TO_TICKS(1000);
    printf("Realease Task 1\n");
    vTaskDelete(task1_handler);
}

void rt_task2(void *data)
{

  printf("Inside Task2 & periodicity time 2000ms\n");
    vTaskDelay(2000/portTICK_PERIOD_MS);
    //pdMS_TO_TICKS(2000);
    printf("Realease Task 2\n");
    vTaskDelete(task2_handler);
}

void rt_task3(void *data)
{

  printf("Inside Task3 & periodicity time 5000ms\n");
    vTaskDelay(5000/portTICK_PERIOD_MS);
    //pdMS_TO_TICKS(5000);
    printf("Realease Task 3\n");
    vTaskDelete(task3_handler);
}

void rt_task4(void *data)
{
int count=10;
while(1)
{
    count++;
    printf("Queue is ready to send data\n");
    xQueueSend(MES_qu,&count,pdMS_TO_TICKS(1000));
    vTaskDelay(2000/portTICK_PERIOD_MS);



}
    vTaskDelete(task4_handler);

}

void rt_task5(void *data)
{
    unsigned int pvBuffer;
    while(1)
    {
        
    printf("Queue is ready to recieve data\n");
     xQueueReceive(MES_qu,&pvBuffer,pdMS_TO_TICKS(1000));
         printf("Interger Data is recieve from Task 4 : %d\n",pvBuffer);

    vTaskDelay(2000/portTICK_PERIOD_MS);
                        
    }
        vTaskDelete(task5_handler);

}


void app_main(void)
{
BaseType_t res;
printf("PROJECT FOR QUE 1 IS START\n");
res = xTaskCreate(  rt_task1,"RT TASK1",2048,NULL,5,&task1_handler);
res = xTaskCreate(  rt_task2,"RT TASK2",2048,NULL,6,&task2_handler);
res = xTaskCreate(  rt_task3,"RT TASK3",2048,NULL,7,&task3_handler);
  
  MES_qu = xQueueCreate( MQ_size,MQ_len );
res = xTaskCreate(  rt_task4,"RT TASK4",2048,NULL,8,&task4_handler);
res = xTaskCreate(  rt_task5,"RT TASK5",2048,NULL,9,&task5_handler);

}

