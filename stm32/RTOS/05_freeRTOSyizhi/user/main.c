#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "TFT.h"
#include <string.h>
#include "LED.h"
#include "FreeRTOS.h"
#include "string.h"
#include "task.h"
#include "queue.h"

StackType_t xTask3Stack[100];
StaticTask_t xTask3TCB;

StackType_t xIdleTaskStack[100];
StaticTask_t xIdleTasTCB;

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
								   StackType_t **ppxIdleTaskStackBuffer,
								   uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer = &xIdleTasTCB;
	*ppxIdleTaskStackBuffer = xIdleTaskStack;
	*pulIdleTaskStackSize = 100;
}

int main(void)
{
	OLED_Init();
	Lcd_Init();
	LCD_Clear(0xFFFF);
	OLED_ShowString(1, 1, "hello");
	BACK_COLOR = WHITE;
	POINT_COLOR = BLACK;
	showhanzi(0 * 32 + 1, 0, 0);
	showhanzi(1 * 32 + 1, 0, 1);
	showhanzi(2 * 32 + 1, 0, 2);

	printf("begin!\n");
	xTaskCreate(Task1Function, "Task1", 100, NULL, 1, &xHandleTask1); // 动态任务
	xTaskCreate(Task2Function, "Task2", 100, NULL, 1, &xHandleTask2);
	xHandleTask3 = xTaskCreateStatic(Task3Function, "Task3", 100, NULL, 1, xTask3Stack, &xTask3TCB);
	xTaskCreate(TaskGenericFunction, "Task4", 100, (void *)4, 1, NULL); // 动态任务
	xTaskCreate(TaskGenericFunction, "Task5", 100, (void *)5, 1, NULL);
	// Start the scheduler
	vTaskStartScheduler();
}
