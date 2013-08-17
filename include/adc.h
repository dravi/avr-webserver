/*
 * Author      : Ravi Teja Darbha
 * Designation : Embedded Software Engineer
 * Description : Header for ADC module in AtMega128 
 */
#ifndef _ADC_H
#define _ADC_H

#include<avr/io.h>

#define SUCCESS 1
#define ERROR   0

#define BV(x) (1 << (x))
#define adcStartConv() ADCSRA |= BV(ADSC)

typedef uint8_t retStatus_t;
typedef uint8_t adcChannel_t

void adcInit(void);
retStatus_t adcSelectChannel(adcChannel_t);

#endif
