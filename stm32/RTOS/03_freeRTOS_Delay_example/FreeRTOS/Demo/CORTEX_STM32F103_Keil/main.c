

/* Standard includes. */
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Library includes. */
#include "stm32f10x_it.h"

/* Demo app includes. */

#include "LCD_Message.h"
#include "BlockQ.h"
#include "death.h"
#include "integer.h"
#include "blocktim.h"
#include "partest.h"
#include "semtest.h"
#include "PollQ.h"
#include "flash.h"
#include "comtest2.h"
#include "serial.h"
#include "led.h"
/* Task priorities. */
#define mainQUEUE_POLL_PRIORITY (tskIDLE_PRIORITY + 2)
#define mainCHECK_TASK_PRIORITY (tskIDLE_PRIORITY + 3)
#define mainSEM_TEST_PRIORITY (tskIDLE_PRIORITY + 1)
#define mainBLOCK_Q_PRIORITY (tskIDLE_PRIORITY + 2)
#define mainCREATOR_TASK_PRIORITY (tskIDLE_PRIORITY + 3)
#define mainFLASH_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define mainCOM_TEST_PRIORITY (tskIDLE_PRIORITY + 1)
#define mainINTEGER_TASK_PRIORITY (tskIDLE_PRIORITY)

/* Constants related to the LCD. */
#define mainMAX_LINE (240)
#define mainROW_INCREMENT (24)
#define mainMAX_COLUMN (20)
#define mainCOLUMN_START (319)
#define mainCOLUMN_INCREMENT (16)

/* The maximum number of message that can be waiting for display at any one
time. */
#define mainLCD_QUEUE_SIZE (3)

/* The check task uses the sprintf function so requires a little more stack. */
#define mainCHECK_TASK_STACK_SIZE (configMINIMAL_STACK_SIZE + 50)

/* Dimensions the buffer into which the jitter time is written. */
#define mainMAX_MSG_LEN 25

/* The time between cycles of the 'check' task. */
#define mainCHECK_DELAY ((TickType_t)5000 / portTICK_PERIOD_MS)

/* The number of nano seconds between each processor clock. */
#define mainNS_PER_CLOCK ((unsigned long)((1.0 / (double)configCPU_CLOCK_HZ) * 1000000000.0))

/* Baud rate used by the comtest tasks. */
#define mainCOM_TEST_BAUD_RATE (115200)

/* The LED used by the comtest tasks. See the comtest.c file for more
information. */
#define mainCOM_TEST_LED (3)

/*-----------------------------------------------------------*/

/*
 * Configure the clocks, GPIO and other peripherals as required by the demo.
 */
static void prvSetupHardware(void);

/*
 * Configure the LCD as required by the demo.
 */
static void prvConfigureLCD(void);

/*
 * The LCD is written two by more than one task so is controlled by a
 * 'gatekeeper' task.  This is the only task that is actually permitted to
 * access the LCD directly.  Other tasks wanting to display a message send
 * the message to the gatekeeper.
 */
static void vLCDTask(void *pvParameters);

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
static void vCheckTask(void *pvParameters);

/*
 * Configures the timers and interrupts for the fast interrupt test as
 * described at the top of this file.
 */
extern void vSetupTimerTest(void);

/*-----------------------------------------------------------*/

/* The queue used to send messages to the LCD task. */

TaskHandle_t xHandleTask1;
TaskHandle_t xHandleTask2;
TaskHandle_t xHandleTask3;

static int rands[] = {1, 2, 3, 4, 5};
/*-----------------------------------------------------------*/
void Task1Function(void *param)
{
	TickType_t tStart = xTaskGetTickCount();
	TickType_t ttStart = tStart;
	TickType_t t = 0;
	int i = 0, j = 0;
	printf("%d\n", tStart);
	while (1)
	{
		t = xTaskGetTickCount();
		if (t >= ttStart + 1000)
		{
			vTaskDelete(xHandleTask3);
			vTaskDelete(xHandleTask2);
			vTaskDelete(xHandleTask1);
		}

		for (i = 0; i < rands[j]; i++)
		{
			printf("1");
		}
		printf("\n");
		j++;
		if (j == 5)
			j = 0;
#if 1
		vTaskDelay(6);
#else
		vTaskDelayUntil(&tStart, 6);
#endif
	}
}

void Task2Function(void *param)
{
	while (1)
	{

		printf("2");
		//		GPIO_WriteBit(GPIOC, GPIO_Pin_13, 0);
	}
}
void Task3Function(void *param)
{
	while (1)
	{
		printf("3");
		//		GPIO_WriteBit(GPIOC, GPIO_Pin_13, 1);
	}
}
// void TaskGenericFunction(void *param)
//{
//	int val = (int)param;

//	while (1)
//	{
//		printf("%d", val);
//	}
//}
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

#ifdef DEBUG
	debug();
#endif

	prvSetupHardware();
	printf("begin!\n");
	xTaskCreate(Task1Function, "Task1", 100, NULL, 2, &xHandleTask1); // 动态任务
	xTaskCreate(Task2Function, "Task2", 100, NULL, 1, &xHandleTask2);
	xHandleTask3 = xTaskCreateStatic(Task3Function, "Task3", 100, NULL, 1, xTask3Stack, &xTask3TCB);
	//	xTaskCreate(TaskGenericFunction, "Task4", 100, (void *)4, 1, NULL); // 动态任务
	//	xTaskCreate(TaskGenericFunction, "Task5", 100, (void *)5, 1, NULL);
	// Start the scheduler
	vTaskStartScheduler();
	/* Will only get here if there was not enough heap space to create the
	idle task. */
	return 0;
}

static void vCheckTask(void *pvParameters)
{
	TickType_t xLastExecutionTime;
	xLCDMessage xMessage;
	static signed char cPassMessage[mainMAX_MSG_LEN];
	extern unsigned short usMaxJitter;

	xLastExecutionTime = xTaskGetTickCount();
	xMessage.pcMessage = cPassMessage;

	for (;;)
	{
		/* Perform this check every mainCHECK_DELAY milliseconds. */
		vTaskDelayUntil(&xLastExecutionTime, mainCHECK_DELAY);

		/* Has an error been found in any task? */

		if (xAreBlockingQueuesStillRunning() != pdTRUE)
		{
			xMessage.pcMessage = "ERROR IN BLOCK Q\n";
		}
		else if (xAreBlockTimeTestTasksStillRunning() != pdTRUE)
		{
			xMessage.pcMessage = "ERROR IN BLOCK TIME\n";
		}
		else if (xAreSemaphoreTasksStillRunning() != pdTRUE)
		{
			xMessage.pcMessage = "ERROR IN SEMAPHORE\n";
		}
		else if (xArePollingQueuesStillRunning() != pdTRUE)
		{
			xMessage.pcMessage = "ERROR IN POLL Q\n";
		}
		else if (xIsCreateTaskStillRunning() != pdTRUE)
		{
			xMessage.pcMessage = "ERROR IN CREATE\n";
		}
		else if (xAreIntegerMathsTaskStillRunning() != pdTRUE)
		{
			xMessage.pcMessage = "ERROR IN MATH\n";
		}
		else if (xAreComTestTasksStillRunning() != pdTRUE)
		{
			xMessage.pcMessage = "ERROR IN COM TEST\n";
		}
		else
		{
			sprintf((char *)cPassMessage, "PASS [%uns]\n", ((unsigned long)usMaxJitter) * mainNS_PER_CLOCK);
		}

		/* Send the message to the LCD gatekeeper for display. */
		// xQueueSend(xLCDQueue, &xMessage, portMAX_DELAY);
	}
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

	vParTestInitialise();
	SerialPortInit();
	led_init();
}
