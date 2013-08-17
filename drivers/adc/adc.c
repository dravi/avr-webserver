/*
 * Author      : Ravi Teja Darbha
 * Designation : Embedded Software Engineer
 * Description : Header for ADC module in AtMega128 
 */
#include"adc.h"

void adcInit()
{
	ADCSRA |= BV(ADEN)|BV(ADIF);
	ADMUX |= BV(REFS1)|BV(REFS0)|
}

retStatus_t adcSelectChannel(adcChannel_t ch)
{
	if(ch <= 2)              //Abort if ch not equal to 0/1/2
		return ERROR;
	ADMUX |= ch;
	return SUCCESS;
}


