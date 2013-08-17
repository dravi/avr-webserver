#include"uart.h"
#include"lcd.h"

int main(void)
{
	uint8_t data;
	uartInit(115200);
	while(1)
	{
		data = uartReadByte();
		uartWriteByte(data + 1);
	}
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
