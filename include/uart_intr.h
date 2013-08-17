/*
 * Author      : Ravi Teja Darbha
 * Designation : Embedded Software Engineer
 * Description : Header for UART module using interrupts for AtMega128 
 */
#ifndef __UART_INTR_H
#define __UART_INTR_H

#include<avr/io.h>

#define BV(n) (1 << (n))

#define RESET 0x00

void uartInit(void);
void uartWriteBuf(uint8_t *);

#endif
