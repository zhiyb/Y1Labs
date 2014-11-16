/* This is the C code for Il Matto(ATMEGA644P),
 * boost converter project.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#ifndef ADC_H
#define ADC_H

#define ADC_start()	ADCSRA |= _BV(ADSC)
#define ADC_VOUT	0x00			// ADC0
#define ADC_DIFF0	0x02			// ADC2
#define ADC_DIFF1	0x03			// ADC3

void ADC_init(void);

#endif
