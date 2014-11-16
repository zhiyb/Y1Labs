/* This is the C code for Il Matto(ATMEGA644P),
 * boost converter project.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "uart.h"
#include "adc.h"
#include "pwm.h"
#include "comm.h"

//	| Port | Pin | Use                         |
//	|------+-----+-----------------------------|
//	| A    | PA0 | Voltage at load             |
//	| D    | PD0 | Host connection TX (orange) |
//	| D    | PD1 | Host connection RX (yellow) |
//	| D    | PD5 | PWM out to drive MOSFET     |

#define ADCZONE	5	// Reduce noise
#define ADC_P	0.2	// Reduce noise

volatile uint16_t adc = 0, set = 0, diff0, diff1;

ISR(ADC_vect)
{
	if (ADMUX == ADC_VOUT) {
		ADMUX = ADC_DIFF0;
		adc = ADC;
		if (adc < set)
			PWM_inc(1);//ADC_P * (float)(set - adc));
		else if (adc > set)
			PWM_dec(1);//ADC_P * (float)(adc - set));
	} else if (ADMUX == ADC_DIFF0) {
		ADMUX = ADC_DIFF1;
		diff0 = ADC;
	} else if (ADMUX == ADC_DIFF1) {
		ADMUX = ADC_VOUT;
		diff1 = ADC;
	}
	TIFR1 |= _BV(TOV1);
}

void init(void)
{
	uart_init();
	PWM_init();
	ADC_init();
	DDRA = 0x00;
	PORTA = 0x00;
	sei();
}

int __attribute__((noreturn)) main(void)
{
	init();
	ADC_start();

	while (1)
		switch (getchar()) {
		case COMM_SET:
			scanf("%u", &set);
			printf("%u", set);
			break;
		case COMM_GET:
			printf("%u %u %u %u", adc, set, OCR1A, \
					diff0 > diff1 ? \
					diff0 - diff1 : \
					diff1 - diff0);
		}
}
