/* Standard includes. */
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Library includes. */
#include "stm32f10x_it.h"

/* Demo app includes. */
#include "serial.h"
#include "led.h"
#include "semphr.h"
#include "event_groups.h"
static void prvSetupHardware(void);

/*
 * Configure the LCD as required by the demo.
 */

/*
 * Retargets the C library printf function to the USART.
 */
int fputc(int ch, FILE *f);

/*
 * Checks the status of all the demo tasks then prints a message to the
 * display.  The message will be either PASS - and include in brackets the
 * maximum measured jitter time (as described at the to of the file), or a
 * message that describes which of the standard demo tasks an error has been
 * discovered in.
 *
 * Messages are not written directly to the terminal, but passed to vLCDTask
 * via a queue.
 */

/*
 * Configures the timers and interrupts for the fast interrupt test as
 * described at the top of this file.
 */
extern void vSetupTimerTest(void);

/*-----------------------------------------------------------*/

/* The queue used to send messages to the LCD task. */

StackType_t xTask3Stack[100];
StaticTask_t xTask3TCB;
StackType_t xIdleTaskStack[100];
StaticTask_t xIdleTasTCB;

TaskHandle_t xHandleTask1;
TaskHandle_t xHandleTask2;
TaskHandle_t xHandleTask3;

static QueueHandle_t xQueueCalcHandle;
static EventGroupHandle_t xEventGroupCalc;

static int sum = 0;
static int dec = 0;
/*-----------------------------------------------------------*/

void Task1Function(void *param)
{
	volatile int i;
	while (1)
	{
	//	printf("1");
		for (i = 0; i < 100000; i++)
		{
			sum++;
		}
		xQueueSend(xQueueCalcHandle, &sum, 0);
		/*设置事件0*/
		xEventGroupSetBits(xEventGroupCalc, (1 << 0));
		//	vTaskDelete(NULL);
	}
}
void Task2Function(void *param)
{
	volatile int i;
	while (1)
	{
	//	printf("2");
		for (i = 0; i < 100000; i++)
		{
			dec--;
		}
		xQueueSend(xQueueCalcHandle, &dec, 0);
		/*设置事件0*/
		xEventGroupSetBits(xEventGroupCalc, (1 << 1));
		// vTaskDelete(NULL);
	}
}

void Task3Function(void *param)
{
	int val1, val2, i = 0;
	while (1)
	{
	//	printf("3");
		/*等待事件*/
		xEventGroupWaitBits(xEventGroupCalc, (1 << 0) | (1 << 1), pdTRUE, pdTRUE, portMAX_DELAY);
		xQueueReceive(xQueueCalcHandle, &val1, 0);
		xQueueReceive(xQueueCalcHandle, &val2, 0);
		printf("val1 = %d, val2 = %d\r", val1, val2);
		if (i++ > 10)
		{
			vTaskDelete(xHandleTask1);
			vTaskDelete(xHandleTask2);
			vTaskDelete(xHandleTask3);
		}
	}
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
								   StackType_t **ppxIdleTaskStackBuffer,
								   uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer = &xIdleTasTCB;
	*ppxIdleTaskStackBuffer = xIdleTaskStack;
	*pulIdleTaskStackSize = 100;
}
void vApplicationIdleHook(void) // 钩子函数
{
}

int main(void)
{

#ifdef DEBUG
	debug();
#endif
	prvSetupHardware();
	printf("Begin!\r");

	/*创建事件组*/
	xQueueCalcHandle = xQueueCreate(2, sizeof(int));
	xEventGroupCalc = xEventGroupCreate();
	printf("Begin!\r");
	xTaskCreate(Task1Function, "Task1", 100, NULL, 1, &xHandleTask1); // 动态任务
	xTaskCreate(Task2Function, "Task2", 100, NULL, 1, &xHandleTask2);
	xTaskCreate(Task3Function, "Task3", 100, NULL, 1, &xHandleTask3);
	// Start the scheduler
	vTaskStartScheduler();
	/* Will only get here if there was not enough heap space to create the
	idle task. */
	return 0;
}

/*-----------------------------------------------------------*/

static void prvSetupHardware(void)
{
	/* Start with the clocks in their expected state. */
	RCC_DeInit();

	/* Enable HSE (high speed external clock). */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait till HSE is ready. */
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
	{
	}

	/* 2 wait states required on the flash. */
	*((unsigned long *)0x40022000) = 0x02;

	/* HCLK = SYSCLK */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);

	/* PCLK2 = HCLK */
	RCC_PCLK2Config(RCC_HCLK_Div1);

	/* PCLK1 = HCLK/2 */
	RCC_PCLK1Config(RCC_HCLK_Div2);

	/* PLLCLK = 8MHz * 9 = 72 MHz. */
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

	/* Enable PLL. */
	RCC_PLLCmd(ENABLE);

	/* Wait till PLL is ready. */
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	{
	}

	/* Select PLL as system clock source. */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	/* Wait till PLL is used as system clock source. */
	while (RCC_GetSYSCLKSource() != 0x08)
	{
	}

	/* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);

	/* SPI2 Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	/* Set the Vector Table base address at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	/* Configure HCLK clock as SysTick clock source. */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

	SerialPortInit();
	led_init();
}
