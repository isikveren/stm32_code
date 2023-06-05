#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "key.h"
#include "ultrasonic.h"
#include "Buzzer.h"

uint16_t angle, i = 10;
int t = 0, sw = 1;
float dis;
int speed = 0;
uint8_t key;
void set_steer(int speed)
{
	speed = speed * 10 + 1500;
	PWM_SetCompare3(speed);
	OLED_ShowNum(2, 1, speed, 4);
}
void speed_set2(int speed)
{
	speed = speed * 200;
	PWM_SetCompare2(speed);
	OLED_ShowNum(2, 1, speed, 4);
}
void speed_set1(int speed)
{
	speed = speed * 200;
	PWM_SetCompare1(speed);
	OLED_ShowNum(2, 1, speed, 4);
}
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Buzzer_Init();
	PWM_Init();
	Key_Init();
	OLED_Init(); // OLED初始化
	hcsr_init();
	OLED_ShowChineseString(1, 1, 3, 5);
	angle = 1500;
	// play_notice_UP();
	//	play_notice_DOWN();
	t = 100;
	PWM_SetCompare2(10000);
	while (1)
	{
		speed_set1(50);
		speed_set2(50);
		dis = Distance();
		OLED_ShowNum(3, 1, dis, 4);
		key = Key_GetNum();
		if (key == 2)
		{
			sw = (sw == 1) ? 0 : 1;
		}
		OLED_ShowNum(2, 6, sw, 2);

		if (sw)
		{
			if (dis < 10)
			{
				speed = -10 * (10 - dis);
				

				// speed_set1(speed);
				// speed_set2(speed);
				set_steer(speed);
			}
			if (dis > 10)
			{
				speed = (dis - 10) * 10;
				
				speed_set1(speed);
				speed_set2(speed);
				set_steer(speed);
			}
			if (dis >= 20)
			{
				speed = 100;
				
				speed_set1(speed);
				speed_set2(speed);
				set_steer(speed);
			}
		}
		else
		{
			set_steer(0);
			speed_set1(0);
			speed_set2(0);
		}
	}
}
//
