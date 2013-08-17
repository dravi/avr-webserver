/*
 * Author      : Ravi Teja Darbha
 * Designation : Embedded Software Engineer
 * Description : UART driver using interrupts for
 *               AtMega128
 */

#include"uart_intr.h"
#include<stdarg.h>
#include<stdio.h>
#include<avr/interrupt.h>

uint8_t buf[50];
uint8_t *rbuf;
uint8_t *wbuf;

volatile uint8_t transmit_complete = 1;

void uartInit()
{
	UCSR1B = RESET;
	UCSR1C = RESET;
	//UBRR1H = (uint8_t)(UBRR_VAL(baud) >> 8);
	UBRR1L = 8;//(uint8_t)ceil(UBRR_VAL(baud));
	UCSR1C |= BV(UCSZ1)|BV(UCSZ0);
	UCSR1B |= BV(TXEN);
	sei();
}

void uartWriteBuf(uint8_t *buf)
{
	while(!transmit_complete);
	transmit_complete = 0;
	wbuf = buf;
	if(wbuf[0] != '\0')
	{
		UDR1 = wbuf[0];
		UCSR1B |= BV(UDRIE);
	}
	else
		transmit_complete = 1;
}

//uint8_t uartReadBuf()

ISR(USART1_UDRE_vect)
{
	if(*++wbuf != '\0')
		UDR1 = *wbuf;
	else
	{
		transmit_complete = 1;
		UCSR1B &= ~BV(UDRIE);
	}
}
/*
uint8_t my_vsprintf(uint8_t *fmt,va_list ap)
{
	uint8_t *pbuf = buf;
	while(*fmt)
	{
		if(*fmt != '%')
		{
			*pbuf++ = *fmt++;
		}
		switch(*++fmt)
		{
			case 'd':sprintf(++pbuf,"%d",va_arg(ap,int));
			         break;
		}
	}
	return 0;
}
*/
uint8_t _my_printf(uint8_t *fmt,...)
{
	uint8_t size;
	va_list ap;
	va_start(ap,fmt);
	size = vsprintf(buf,fmt,ap);
	uartWriteBuf(buf);
	va_end(ap);
	return size;
}
