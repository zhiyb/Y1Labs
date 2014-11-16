#include <avr/io.h>
#include <util/delay.h>

//								0,		1,		2,		3,		4,		5,		6,		7,		8,		9
code unsigned char table[10] = {0x3F,	0x06,	0x5B,	0x4F,	0x66,	0x6D,	0x7D,	0x07,	0x7F,	0x6F};

void main(void)
{
	unsigned char i;
	DDRA = 0xFF;
	PORTA = 0x00;
	while (1)
		for (i = 0; i < 10; i++) {
			PORTA = table[i];
			_delay_ms(1000);
		}
}
