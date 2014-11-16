/* This is the C code for Il Matto(ATMEGA644P),
 * boost converter project.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#include <avr/io.h>

void PWM_init(void)
{
	// Fast PWM, 10 bit, 11kHz
	TCCR1A = _BV(COM1A1) | _BV(WGM11) | _BV(WGM10);	// Clear on compare
	TCCR1B = _BV(WGM12);				// Fast PWM, 10b
	TCCR1C = 0;					// No force output
	OCR1A = 0;					// Compare A
	TIMSK1 = 0;					// No interrupt
	TCCR1B |= _BV(CS10);				// Start timer
	DDRD |= _BV(5);
}
