/*
 * Author      : Ravi Teja Darbha
 * Designation : Embedded Software Engineer
 * Description : Header for Hitachi LCD module to be
 *               used with AtMega128 
 */
#ifndef __LCD_H
#define __LCD_H 1

#include<avr/io.h>

#define BV(x) (1 << (x))

#define RS  0
#define EN  2
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7

#define CMD            0
#define DATA           1

#define LINE1          0
#define LINE2          1

#define LINE1_ADDR     0x80
#define LINE2_ADDR     0xC0

#define LCD_DATA_DIR   DDRA
#define LCD_PORT       PORTA

#define DISPLAY_CLEAR  0x01       
#define FUNCTION_SET   0x28
#define DISPLAY_CTRL   0x0C
#define ENTRY_MODE     0x06

#define lcd_NegEdge(x) LCD_PORT |= BV(x);      \
    delay_us(100);                               \
	LCD_PORT &= ~BV(x);        

#define MSB(x) ((x) & 0xF0)
#define LSB(x) ((x) & 0x0F) << 4

#define delay_ms(x) delay_us(x##000)
#define delay_s(x) delay_ms(x##000)

void lcdInit(void);
void lcdWriteByte(uint8_t,uint8_t);
void lcdWriteChar(uint8_t,uint8_t);
void lcdWriteString(uint8_t *,uint8_t);

void delay_us(uint32_t);

#endif
