RTOS

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

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



任务暂停：

~~~c
  void vTaskSuspend( TaskHandle_t xTaskToSuspend );
~~~

