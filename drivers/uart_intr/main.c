#include"uart_intr.h"

int main(void)
{
	uartInit();
	uartWriteBuf("RAVI TEJA D%d");
		//delay_us(1000);
	while(1);
	return 0;
}

void delay_us(uint32_t time)
{
	uint32_t i,j;
	for(i = 0;i < time;i++)
	{
		for(j = 0;j < 16;j++)
			asm("nop");
	}
}
