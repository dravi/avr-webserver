/*
 * Author      : Ravi Teja Darbha
 * Designation : Embedded Software Engineer
 * Description : Header for UART module using polling for AtMega128 
 */
#ifndef __UART_H
#define __UART_H

#include<avr/io.h>

#define BV(x) (1 << (x))

#define F_OSC 16000000
#define UBRR_VAL(baud) (F_OSC / (16 * baud) - 1)
#define RESET 0x00

void uartInit(uint32_t);
void uartWriteByte(uint8_t);
uint8_t uartReadByte(void);

#endif
