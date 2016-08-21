/* This is the C code for Il Matto(ATMEGA644P),
 * boost converter project.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#include <avr/io.h>
#include <stdio.h>

int uputchar(char c, FILE *stream)
{
	if (c == '\n')
		uputchar('\r', stream);
	while (!(UCSR0A & _BV(UDRE0)));
	UDR0 = c;
	return c;
}

int ugetchar(FILE *stream)
{
	while(!(UCSR0A & _BV(RXC0)));
	return UDR0;
}

void uart_init(void)
{
#undef BAUD
#define BAUD 9600
#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
#if USE_2X
	UCSR0A |= (1 << U2X0);
#else
	UCSR0A &= ~(1 << U2X0);
#endif
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
	fdevopen(uputchar, ugetchar);
}
