/*
 * Author      : Ravi Teja Darbha
 * Designation : Embedded Software Engineer
 * Description : UART driver using polling for
 *               AtMega128
 */

#include"uart.h"

void uartInit(uint32_t baud)
{
	UCSR1B = RESET;
	UCSR1C = RESET;
	//UBRR1H = (uint8_t)(UBRR_VAL(baud) >> 8);
	UBRR1L = 8;//(uint8_t)ceil(UBRR_VAL(baud));
	UCSR1C |= BV(UCSZ1)|BV(UCSZ0);
	UCSR1B |= BV(RXEN)|BV(TXEN);
}

void uartWriteByte(uint8_t data)
{
	//UCSR1A |= BV(TXC);
	while((UCSR1A & BV(UDRE)) == 0);
	UDR1 = data;
}

uint8_t uartReadByte()
{
	uint8_t data;
	while((UCSR1A & BV(RXC)) == 0);
	data = UDR1;
	return data;
}

