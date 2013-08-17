#include"lcd.h"

int main(void)
{
	int a = 23,b = 45;
	uint8_t *name = "Wassup!!!";
	lcdInit();
	lcdWriteString("Hey Ravi",LINE1);
	lcdWriteChar('A',LINE2);
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
