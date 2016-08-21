#include <avr/io.h>
#include <stdio.h>

void init_volume(void)
{
	TCCR2A = _BV(COM2A0) | _BV(COM2A1);	// Set OC1A on Compare Match
	TCCR2A |= _BV(WGM21) | _BV(WGM20);	// PWM, Fast, 0xFF, BOTTOM
	TCCR2B = _BV(CS20);			// clk/1 prescaler
	ASSR = 0;				// I/O clock
	TIMSK2 = 0;				// No interrupts
	TCNT2 = 0x00;				// Counter 1
	OCR2A = 0xFF;				// Compare register
	DDRD |= _BV(7);				// Output
}

void volume(uint8_t v)
{
	//v = (uint16_t)0xFF * (uint16_t)(100 - v) / (uint16_t)100;
	//printf("\n<VOL %d>\n", v);
	OCR2A = (100 - v) * 0xFF / 100;		// Duty cycle
}
