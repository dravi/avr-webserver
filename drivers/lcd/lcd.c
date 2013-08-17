/*
 * Author      : Ravi Teja Darbha
 * Designation : Embedded Software Engineer
 * Description : Hitachi LCD driver to be used
 *               with AtMega128
 */

#include<stdarg.h>
#include"lcd.h"

/*
 *Used to initialize the LCD
 */
void lcdInit()
{
	LCD_DATA_DIR |= BV(RS)|BV(EN)|BV(DB4)|BV(DB5)|BV(DB6)|BV(DB7);
	lcdWriteByte(FUNCTION_SET,CMD);                                    /* Must executed first */
	lcdWriteByte(DISPLAY_CLEAR,CMD);
	lcdWriteByte(DISPLAY_CTRL,CMD);
	lcdWriteByte(ENTRY_MODE,CMD);	
}

/*This function is used to write a charchter
 *to the LCD command or data register 
 *flag == 0 for selecting command register
 *flag == 1 for selecting data register
 */
void lcdWriteByte(uint8_t ch , uint8_t flag)
{
	switch(flag)
	{
		case CMD:
			LCD_PORT &= ~BV(RS);
			break;
		case DATA:
			LCD_PORT |= BV(RS);
			break;
	}
	LCD_PORT &= ~(BV(DB4)|BV(DB5)|BV(DB6)|BV(DB7));
	LCD_PORT |= MSB(ch);
	lcd_NegEdge(EN);
	delay_us(200);
	LCD_PORT &= ~(BV(DB4)|BV(DB5)|BV(DB6)|BV(DB7));
	LCD_PORT |= LSB(ch);
	lcd_NegEdge(EN);
	delay_us(200);
}

/*
 *This function is used to write a character to the LCD
 */
void lcdWriteChar(uint8_t ch,uint8_t line)
{
	switch(line)
	{
		case LINE1:
			lcdWriteByte(LINE1_ADDR,CMD);
			break;
		case LINE2:
			lcdWriteByte(LINE2_ADDR,CMD);
	}
	lcdWriteByte(ch,DATA);
}

/*
 *This function is used to write a string to the LCD
 */
void lcdWriteString(uint8_t *str,uint8_t line)
{
	switch(line)
	{
		case LINE1:
			lcdWriteByte(LINE1_ADDR,CMD);
			break;
		case LINE2:
			lcdWriteByte(LINE2_ADDR,CMD);
	}
	while(*str != '\0')
	{
		lcdWriteByte(*str,DATA);
		str++;
	}
}

_my_printf(char *fmt,...)
{
	char *p;
	uint8_t count = 0;
	lcdWriteByte(LINE1_ADDR,CMD);
	va_list ap;
	va_start(ap,fmt);
	for(p = fmt;*p;p++)
	{
		if(*p != '%')
		{
			lcdWriteByte(*p,DATA);
			count++;
			continue;
		}
		switch(*++p)
		{
			case 'd': lcdWriteByte(va_arg(ap,int32_t),DATA);
					  count++;
					  break;
			case 'u': lcdWriteByte(va_arg(ap,uint32_t),DATA);
			          count++;
			          break;
			case 'c': lcdWriteByte(va_arg(ap,uint8_t),DATA);
			          count++;
			          break;
		}
	}
	va_end(ap);
	return count;
}




