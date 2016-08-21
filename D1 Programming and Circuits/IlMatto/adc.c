/* This is the C code for Il Matto(ATMEGA644P),
 * boost converter project.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#include <avr/io.h>
#include "adc.h"

void ADC_init(void)
{
	ADMUX = ADC_VOUT;				// ADC channel 0
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);	// Prescaler 64
	ADCSRA |= _BV(ADATE) | _BV(ADIE);		// Auto, Interrupt
	ADCSRB = _BV(ADTS2) | _BV(ADTS1);		// Timer 1 ovf
	//ADCSRB = 0x00;				// Free running
	DIDR0 = 0xFF;					// Disable PA0 i/p
}
