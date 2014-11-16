#include <avr/io.h>
#include <util/delay.h>

const unsigned char num[10] = {
//	0,	1,	2,	3,	4,
	0xFC,	0x60,	0xDA,	0xF2,	0x66,
//	5,	6,	7,	8,	9,
	0xB6,	0xBE,	0xE0,	0xFE,	0xF6,
};

void main(void)
{
	unsigned char i;
	DDRA = 0xFF;
	PORTA = 0x00;
	while (1)
		for (i = 0; i < 10; i++) {
			PORTA = num[i];
			_delay_ms(1000);
		}
}
