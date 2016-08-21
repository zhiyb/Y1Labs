#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

static inline void timer0_init(void)
{
	TCCR0A = _BV(WGM01);			// No output, CTC mode
	TCCR0B = _BV(CS02);			// CTC, clk/256
	OCR0A = 250;				// Compare register A
	TIMSK0 = 0;				// No interrupt
	TIFR0 |= _BV(OCF0A);			// Clear interrupt flag
}

static inline uint8_t timer0(void)
{
	if (TIFR0 & _BV(OCF0A)) {		// Interrupt flag
		TIFR0 |= _BV(OCF0A);		// Clear interrupt flag
		return 1;
	}
	return 0;
}

#endif
