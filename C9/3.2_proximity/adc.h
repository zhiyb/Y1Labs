#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

inline void ADC_init(void)
{
	ADMUX = 0;
	ADCSRA = _BV(ADEN) | 6;
	//ADCSRB = ;
}

inline void ADC_channel(uint8_t c)
{
	while (ADCSRA & _BV(ADSC));
	ADMUX = c;
	DIDR0 = 1 << c;
}

inline uint16_t ADC_read(void)
{
	ADCSRA |= _BV(ADSC);
	while (ADCSRA & _BV(ADSC));
	return ADC;
}

#endif
