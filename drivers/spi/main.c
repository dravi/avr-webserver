#include"spi.h"
#include"lcd.h"

int main(void)
{
	lcdInit();
	spiInit();
	lcdWriteChar(spiFullDuplexRdWr('D'),LINE2);
	while(1);
	return 0;
}
