#include "stm32f10x.h" // Device header
#include "Delay.h"
void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}
}

void Buzzer_1000Hz(void)
{
	Buzzer_Turn();
	Delay_ms(1);
}
void Buzzer_100Hz(void)
{
	Buzzer_Turn();
	Delay_ms(10);
}
void Buzzer_10000Hz(void)
{
	Buzzer_Turn();
	Delay_us(100);
}

void Buzzer_us(int n, int m)
{
	int M = 1000000 * m / n;
	M = M / 8;
	while (M--)
	{
		Buzzer_Turn();
		Delay_us(n);
	}
}

void play(void)
{
	//	Buzzer_us(1912,1); //1
	// Buzzer_us(1703,1); //2
	//	Buzzer_us(1517,1); //3
	//	Buzzer_us(1432,1); //4
	//	Buzzer_us(1275,1); //5
	//	Buzzer_us(1136,1); //6
	//	Buzzer_us(1012,1); //7
	//	Buzzer_us(956,1); //1+

	Buzzer_us(1517, 1); // 3
	Delay_us(100);
	Buzzer_us(1517, 1); // 3
	Delay_us(100);
	Buzzer_us(1517, 1); // 3
	Buzzer_us(1703, 1); // 2
	Buzzer_us(1703, 1); // 2
	Buzzer_us(1912, 1); // 1
}

void play_notice_UP(void)
{
	Buzzer_us(1912, 1);
	Buzzer_us(956, 1); // 1+
}
void play_notice_DOWN(void)
{

	Buzzer_us(956, 1); // 1+
	Buzzer_us(1912, 1);
}
