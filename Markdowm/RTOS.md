#	FreeRTOS

## 	任务创建和删除

创建任务（动态）：

~~~c
    BaseType_t xTaskCreate( TaskFunction_t pxTaskCode,
                            const char * const pcName, 
                            const configSTACK_DEPTH_TYPE usStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask );
~~~

创建任务（静态）：

~~~c
  TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                    const char * const pcName,
                                    const uint32_t ulStackDepth,
                                    void * const pvParameters,
                                    UBaseType_t uxPriority,
                                    StackType_t * const puxStackBuffer,
                                    StaticTask_t * const pxTaskBuffer );
~~~

任务删除：

~~~c
 void vTaskDelete( TaskHandle_t xTaskToDelete );
~~~

## 	任务暂停和重启

任务暂停：

~~~c
  void vTaskSuspend( TaskHandle_t xTaskToSuspend );
~~~

任务重新开始：

~~~c
 void vTaskResume( TaskHandle_t xTaskToResume );
~~~

## 	延时函数

延时函数，延时多少个Tick

~~~c
void vTaskDelay( const TickType_t xTicksToDelay ); //任务执行完开始延时计时
void vTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );//任务开始时，开始计时

BaseType_t xTaskDelayUntil( TickType_t * const pxPreviousWakeTime,
                            const TickType_t xTimeIncrement );

vTaskDelayUntil(t2,t);//延迟到t2+t
~~~

<img src="C:\Users\lauxu\AppData\Roaming\Typora\typora-user-images\image-20230717025040853.png" alt="image-20230717025040853" style="zoom:50%;" />

## 	空闲任务及其钩子函数

空闲任务：

~~~c
static portTASK_FUNCTION(prvIdleTask, pvParameters);
~~~

帮助自杀任务清理内存



钩子函数：

文件 

~~~c
#define configUSE_IDLE_HOOK 1  //FreeRTOSConfig.h
~~~



~~~C
#if (configUSE_IDLE_HOOK == 1)
        {
            extern void vApplicationIdleHook(void);
            /* Call the user defined function from within the idle task.  This
             * allows the application designer to add background functionality
             * without the overhead of a separate task.
             * NOTE: vApplicationIdleHook() MUST NOT, UNDER ANY CIRCUMSTANCES,
             * CALL A FUNCTION THAT MIGHT BLOCK. */
            /*从空闲任务中调用用户定义的函数。这允许应用程序设计人员添加后台功能
			*没有单独任务的开销。
			*注意:vApplicationIdleHook()在任何情况下都不能，
			*调用可能阻塞的函数。* /
			
            vApplicationIdleHook();
        }
#endif /* configUSE_IDLE_HOOK */
~~~

