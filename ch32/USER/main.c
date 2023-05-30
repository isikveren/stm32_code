#include "ch32f10x.h"

#include "LED.h"
#include "OLED.h"

static u16 p_ms=0;	
void Delay_Ms(u16 n)
{	 		  	  
	u32 i;	
	
	SysTick->LOAD=(u32)n*p_ms;				
	SysTick->VAL =0x00;							
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	
	do
	{
		i=SysTick->CTRL;
	}while((i&0x01)&&!(i&(1<<16)));	
	
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	
	SysTick->VAL =0X00;        	    
} 

int main()
{
	LED_Init();
	OLED_Init();
	OLED_ShowString(1, 1, "123");
	while (1)
		
	{
	Delay_Ms(200);
	OLED_ShowString(1, 1, "321");
	Delay_Ms(200);
	}
}
