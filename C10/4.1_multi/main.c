#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t val = 0;

ISR(INT0_vect, ISR_NOBLOCK)
{
	if (val != 0)
		val--;
}

ISR(INT1_vect, ISR_NOBLOCK)
{
	if (val != 0xFF)
		val++;
}

ISR(ADC_vect, ISR_NOBLOCK)
{
	TIFR0 = 0xFF;
	PORTB ^= _BV(7);	// Toggle LED
}

static inline void init(void)
{
	// IO port
	DDRD &= ~(_BV(2) | _BV(3));		// INT0 and INT1 as input
	PORTD |= _BV(2) | _BV(3);		// have pull-up resistors
	DDRB |= _BV(7);		// LED pin output
	PORTB |= _BV(7);	// Initialise: LED on

	// External interrupts
	EICRA = _BV(ISC11) | _BV(ISC01);	// Falling edge
	EIFR = _BV(INTF1) | _BV(INTF0);		// Clean interrupt flags
	EIMSK = _BV(INT1) | _BV(INT0);		// Interrupts enable

	// ADC interrupt
	ADMUX = 0;		// Channel 0
	// Enable ADC, enable auto trigger, enable interrupt, division by 2
	ADCSRA = _BV(ADEN) | _BV(ADATE) | _BV(ADIE);// | 6;
	// Auto trigger source: timer0 compare match
	ADCSRB = _BV(ADTS1) | _BV(ADTS0);
	DIDR0 = _BV(0);		// Disable digital input buffer on PIN0
	ADCSRA |= _BV(ADSC);	// Start conversion

	// Timer 0
	TCCR0A = _BV(WGM01);	// No output, CTC mode (0 -> OCR0A)
	TCCR0B = _BV(CS02);	// no force ouput, CTC,  clk/256 prescaler
	OCR0A = 0x00;		// Compare register A
	TIMSK0 = 0;		// No timer0 interrupts enabled

	// Global interrupt enable
	sei();
}

int __attribute__((noreturn)) main(void)
{
	init();

	while (1)
		OCR0A = val;
}
