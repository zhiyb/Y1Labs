#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t val = 0;

ISR(INT0_vect)
{
	if (val != 0)
		val--;
}

ISR(INT1_vect)
{
	if (val != 0xFF)
		val++;
}

static inline void init(void)
{
	// IO port
	MCUCR |= 0x80;			// Disable JTAG
	MCUCR |= 0x80;			// Thanks to someone point that out
	DDRC = 0xFF;				// PORTC as output of `val'
	PORTC = 0;
	DDRD &= ~(_BV(2) | _BV(3));		// INT0 and INT1 as input
	PORTD |= _BV(2) | _BV(3);		// have pull-up resistors

	// External interrupts
	EICRA = _BV(ISC11) | _BV(ISC01);	// Falling edge
	EIMSK = _BV(INT1) | _BV(INT0);		// Interrupts enable
	EIFR = _BV(INTF1) | _BV(INTF0);		// Clean interrupt flags
	sei();					// Global interrupt enable
}

int __attribute__((noreturn)) main(void)
{
	init();

	while (1)
		PORTC = val;
}
