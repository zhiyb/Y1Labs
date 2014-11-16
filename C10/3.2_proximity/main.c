#include <avr/interrupt.h>
//#include <stdio.h>
//#include "debug.h"

//#define VOLT 3.3
//#define VAL 0x200

ISR(ADC_vect)
{
	PORTB ^= _BV(7);	// Toggle LED
	//ADCSRA |= _BV(ADIF);	// Clean interrupt flag
}

void init(void)
{
	//init_debug_uart0();
	ADMUX = 0;		// Channel 0
	// Enable ADC, enable auto trigger, enable interrupt, division by 2
	ADCSRA = _BV(ADEN) | _BV(ADATE) | _BV(ADIE);// | 6;
	ADCSRB = 0;		// Auto trigger: free running mode
	DIDR0 = _BV(0);		// Disable digital input buffer on PIN0
	DDRB |= _BV(7);		// LED pin output
	PORTB |= _BV(7);	// Initialise: LED on
	ADCSRA |= _BV(ADSC);	// Start conversion
	sei();			// Global interrupt enable
}

int __attribute__((noreturn)) main(void)
{
	init();

	while (1);
	/*puts("*** ADC for C9 ***");
		uint16_t res = ADC_read();
		if (res < VAL)
			PORTB |= _BV(7);
		else
			PORTB &= ~_BV(7);
		printf("Result: 0x%X, volt: %fV\n", res, VOLT * res / 1024);
		_delay_ms(200);*/
}
