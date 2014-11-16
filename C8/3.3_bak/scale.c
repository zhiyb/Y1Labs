/*  Author: Klaus-Peter Zauner
 *  Modified: zhiyb(Yubo Zhi)
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
//#include "et_scale.h"
#include "tft.h"

// Output pin: OC1A, PORTD.5

void init_tone(void);
void tone(uint16_t frequency);

/*int main(void)
{
	uint8_t i = 0;

	TFT_init();
	stdout = tftout();
	init_tone();
	puts("Initialsation finished");

start:
	while (i < ET_SCALE_TOP) {
		tone(et_scale[i]);
		printf("%.4dHz, ", et_scale[i++]);
		_delay_ms(200);
	}
	puts("Reached top!\n");
	_delay_ms(200);
	while (i != 0) {
		tone(et_scale[--i]);
		printf("%.4dHz, ", et_scale[i]);
		_delay_ms(200);
	}
	puts("Reached bottom!\n");
	_delay_ms(200);
	goto start;

	return 1;
}*/

/* init_tone ---
   Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
	TCCR1A = _BV(COM1A0) | _BV(WGM10);	// Toggle OC1A on Compare Match
	TCCR1C = 0;				// No force output
	TCCR1B = _BV(WGM13);			// PWM, PFC, TOP: OCR1A
	TCCR1B |= _BV(CS11) /*| _BV(CS10)*/;	// clk/8 prescaler
	TIMSK1 = 0;				// No interrupts
	TCNT1H = 0x00;
	TCNT1L = 0x00;				// Counter 1
	OCR1AH = 0x00;
	OCR1AL = 0x00;				// Compare register
	DDRD |= _BV(5);				// Output
}

/* tone ---
   Set oscillator output to desired frequency
*/
void tone(uint16_t frequency)
{
	printf("%.4dHz, ", frequency);
	if (frequency == 0) {
		OCR1AH = 0;
		OCR1AL = 0;
		return;
	}
	frequency = (F_CPU / 8 / 2 / 2) / frequency;
	OCR1AH = frequency / 0x0100;
	OCR1AL = frequency % 0x0100;		// Compare register
}
