#include "stm32f10x.h"

/*LED灯相关定义*/
#define RCC_GPIO_LED RCC_APB2Periph_GPIOF /*LED使用的GPIO时钟*/
#define LEDn 4                            /*LED数量*/
#define GPIO_LED GPIOF                    /*LED灯使用的GPIO组*/

#define DS1_PIN GPIO_Pin_10 /*DS1使用的GPIO管脚*/
#define DS2_PIN GPIO_Pin_9  /*DS2使用的GPIO管脚*/
#define DS3_PIN GPIO_Pin_8  /*DS3使用的GPIO管脚*/
#define DS4_PIN GPIO_Pin_7  /*DS4使用的GPIO管脚*/

/*KEY按键相关定义*/
#define RCC_GPIO_KEY RCC_APB2Periph_GPIOA /*KEY使用的GPIO时钟*/
#define KEYn 2                            /*KEY数量*/
#define GPIO_KEY GPIOA                    /*KEY灯使用的GPIO组*/

#define KEY1_PIN GPIO_Pin_0 /*KEY1使用的GPIO管脚*/
#define KEY2_PIN GPIO_Pin_1 /*KEY2使用的GPI0管脚*/

void Delay_us(uint32_t us); // 延时函数单位us
void Delay_ms(uint32_t ms); // 延时函数单位ms
void Delay_s(uint32_t s);   // 延时函数单位s
void Key_Init(void);        // KEY初始化函数声明 定义在下方
void LED_Init(void);        // LED灯初始化函数声明  定义在下方
void Turn_On_LED(uint8_t LED_NUM);
uint8_t Key_GetNum(void); // 获取按键值的函数声明

int main(void)
{

    LED_Init();        // LED初始化
    Key_Init();        // 按键KEY初始化
    uint8_t KeyNum;    // 接收按键信号
    uint8_t count = 0; // 计数 流水灯
    uint8_t flag = 0;  // 流水灯信号信号 取值0和1
    uint8_t sw = 0;    // 开关信号  取值0和1
    while (1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3); // 灯全关
        KeyNum = Key_GetNum();
        if (KeyNum == 1) // 按键1按下时，开关信号sw反转
        {

            if (sw)
                sw = 0;
            else
                sw = 1;
        }
        if (sw) // 开关信号为1时候，流水灯才亮
        {
            if (KeyNum == 2) // 按键1按下时，流水灯顺逆信号flag反转
            {

                if (flag)
                    flag = 0;
                else
                    flag = 1;
            }
            if (flag)
            {
                count -= 1; // flag==1时候，逆转
            }
            else
            {
                count += 1; // flag==0时候，顺流
            }
            Turn_On_LED(count % 4);
            Delay_ms(200); // 延时200ms
        }
    }
}

void Turn_On_LED(uint8_t LED_NUM)
{
    switch (LED_NUM)
    {
    case 0:
        GPIO_ResetBits(GPIO_LED, DS1_PIN); /*点亮DS1灯*/
        break;
    case 1:
        GPIO_ResetBits(GPIO_LED, DS2_PIN); /*点亮DS2灯*/
        break;
    case 2:
        GPIO_ResetBits(GPIO_LED, DS3_PIN); /*点亮DS3灯*/
        break;
    case 3:
        GPIO_ResetBits(GPIO_LED, DS4_PIN); /*点亮DS4灯*/
        break;
    default:
        GPIO_ResetBits(GPIO_LED, DS1_PIN | DS2_PIN | DS3_PIN | DS4_PIN); /*点亮所有的灯*/
        break;
    }
}

uint8_t Key_GetNum(void)
{
    uint8_t KeyNum = 0;
    if (GPIO_ReadInputDataBit(GPIO_KEY, KEY1_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(GPIO_KEY, KEY1_PIN) == 0)
            ;
        Delay_ms(20);
        KeyNum = 1;
    }
    if (GPIO_ReadInputDataBit(GPIO_KEY, KEY2_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(GPIO_KEY, KEY2_PIN) == 0)
            ;
        Delay_ms(20);
        KeyNum = 2;
    }
    return KeyNum;
}

/**
 * @brief  微秒级延时
 * @param  xus 延时时长，范围：0~233015
 * @retval 无
 */
void Delay_us(uint32_t xus)
{
    SysTick->LOAD = 72 * xus;   // 设置定时器重装值
    SysTick->VAL = 0x00;        // 清空当前计数值
    SysTick->CTRL = 0x00000005; // 设置时钟源为HCLK，启动定时器
    while (!(SysTick->CTRL & 0x00010000))
        ;                       // 等待计数到0
    SysTick->CTRL = 0x00000004; // 关闭定时器
}

/**
 * @brief  毫秒级延时
 * @param  xms 延时时长，范围：0~4294967295
 * @retval 无
 */
void Delay_ms(uint32_t xms)
{
    while (xms--)
    {
        Delay_us(1000);
    }
}

/**
 * @brief  秒级延时
 * @param  xs 延时时长，范围：0~4294967295
 * @retval 无
 */
void Delay_s(uint32_t xs)
{
    while (xs--)
    {
        Delay_ms(1000);
    }
}

void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_GPIO_KEY, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    GPIO_InitStructure.GPIO_Pin = KEY1_PIN | KEY2_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_KEY, &GPIO_InitStructure);
}
void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_GPIO_LED, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Pin = DS1_PIN | DS2_PIN | DS3_PIN | DS4_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //
    GPIO_Init(GPIO_LED, &GPIO_InitStructure);

    GPIO_SetBits(GPIO_LED, DS1_PIN | DS2_PIN | DS3_PIN | DS4_PIN);
}