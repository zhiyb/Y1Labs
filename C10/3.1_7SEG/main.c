#include <avr/io.h>
#include <avr/interrupt.h>

const unsigned char num[10] = {
//	0,	1,	2,	3,	4,
	0xFC,	0x60,	0xDA,	0xF2,	0x66,
//	5,	6,	7,	8,	9,
	0xB6,	0xBE,	0xE0,	0xFE,	0xF6,
};

volatile uint8_t count = 0;

ISR(TIMER1_COMPA_vect)
{
	PORTA = num[count++];
	if (count == 10)
		count = 0;
}

int __attribute__((noreturn)) main(void)
{
	// Port initialise
	DDRA = 0xFF;
	PORTA = num[count++];

	// Timer1 initialise (Using timer1 to be more precise)
	TCCR1A = 0;		// No pin output, CTC mode (0 -> OCR1A)
	TCCR1B = _BV(WGM12) | _BV(CS12);	// CTC, clk/256 prescaler
	TCCR1C = 0;		// No force output
	OCR1A = 46874;		// 12M / 256 - 1 = 46874
	TIMSK1 = _BV(OCIE1A);	// Interrupt compare A match enable

	// Global interrupt enable
	sei();

	while (1);
}
