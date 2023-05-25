# stm32 项目

## 什么都无法舍弃的人 什么也改变不了

## 学习路线

- 51 有点基础看了一些，就没学了(继续学完)
- stm32 直接入门的 32
- RTOS 正在学，试试
- linux 和 ARM

- 微处理器 移动端芯片
- 微控制器 控制芯片：stm32


~~~ c
uint8_t KeyNum;					// 按键接收
uint8_t Speed = 0;				// 风扇转速百分比
float temper;					// 接收传感器获取的温度
uint8_t temper_i, temper_f;		// 温度的整数部分和小数部分
uint8_t flag = 1, set_flag = 0; // 开关信号和阈值选择信号
uint8_t MIN = 18, MAX = 30;		// 最低阈值和最高阈值
uint8_t T[4] = {0};				// 温度区间
void System_Init()				// 系统初始化
{

	OLED_Init();	            // OLED初始化
	DS18B20_Init();             // 温度传感器初始化
	Fan_Init();		            // 风扇初始化
	Key_Init();		            // 按键初始化
	Serial_Init();	            // 串口初始化
}
~~~