/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <inttypes.h>
#include <avr/io.h>

void init_uart0(void)
{
	/* Configure 9600 baud, 8-bit, no parity and one stop bit */
	const int baud_rate = 9600;
	UBRR0H = (F_CPU/(baud_rate*16L)-1) >> 8;
	UBRR0L = (F_CPU/(baud_rate*16L)-1);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

char get_ch(void)
{
	while(!(UCSR0A & _BV(RXC0)));
	return UDR0;
}

void put_ch(char ch)
{
	while (!(UCSR0A & _BV(UDRE0)));
	UDR0 = ch;
}

void put_str(char *str)
{
	int i;
	for(i=0; str[i]; i++) put_ch(str[i]);
}

int main(void)
{
	char ch;
	init_uart0();
	put_str("Hello from Il Matto\n\r");
	/* forever loop */
	for (;;) 
	{
		/* get character from UART */
		ch = get_ch();
		/* send message back to the host terminal */
		put_str("You sent the character '");
		put_ch(ch);
		put_str("'\n\r");
	}
}



