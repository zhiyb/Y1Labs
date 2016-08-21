#include <avr/io.h>
#include <util/delay.h>

const unsigned char num[10] = {
//	0,	1,	2,	3,	4,
	0xFC,	0x60,	0xDA,	0xF2,	0x66,
//	5,	6,	7,	8,	9,
	0xB6,	0xBE,	0xE0,	0xFE,	0xF6,
};

int main(void)
{
	unsigned char i = 0;
	DDRA = 0xFF;
	PORTA = 0x00;
	DDRC &= ~(1 << 7);
	PORTC |= 1 << 7;
display:
	PORTA = num[i];
pressed:
	while (!(PINC & 0x80));	// While key pressed
	_delay_ms(5);		// De-bouncing
	if (!(PINC & 0x80))
		goto pressed;
notpressed:
	while (PINC & 0x80);	// While key not pressed
	_delay_ms(5);		// De-bouncing
	if (PINC & 0x80)
		goto notpressed;
	i = i < 9 ? i + 1 : 0;
	goto display;
	return 1;
}
