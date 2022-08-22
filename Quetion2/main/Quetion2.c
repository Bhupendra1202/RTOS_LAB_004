#include <stdio.h>
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h"
#include "freertos/timers.h"

TaskHandle_t task1_handler,task2_handler,task3_handler,task4_handler,task5_handler;
TimerHandle_t serial_timer_handle;
void rt_task1(void *data)
{

    printf("Inside Task1 & periodicity time 1000ms\n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    printf("Realease Task 1\n");
    vTaskDelete(task1_handler);
}

void rt_task2(void *data)
{

  printf("Inside Task2 & periodicity time 2000ms\n");
    vTaskDelay(2000/portTICK_PERIOD_MS);
    printf("Realease Task 2\n");
    vTaskDelete(task2_handler);
}

void CallbackFunction(void *data)
{
    printf("Callback by timer of task 3\n");
}

void rt_task3(void *data)
{

  printf("Inside Task3 & periodicity time 5000ms\n");
    vTaskDelay(5000/portTICK_PERIOD_MS);

     printf("Creating The Timer\n");
    serial_timer_handle = xTimerCreate("one_shot_timer",1000/portTICK_PERIOD_MS,pdFALSE,0,CallbackFunction);
    printf("Starting The Timer\n");
    xTimerStart(serial_timer_handle,0);

    vTaskDelete(task3_handler);
}

void app_main(void)
{
BaseType_t res;
printf("PROJECT FOR QUE 2 IS START\n");
res = xTaskCreate(  rt_task1,"RT TASK1",2048,NULL,5,&task1_handler);
res = xTaskCreate(  rt_task2,"RT TASK2",2048,NULL,6,&task2_handler);
res = xTaskCreate(  rt_task3,"RT TASK3",2048,NULL,7,&task3_handler);
  


}
