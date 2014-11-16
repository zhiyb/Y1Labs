// Reference: http://playground.arduino.cc/Main/RotaryEncoders

#include <avr/io.h>
#include <util/delay.h>

const unsigned char num[16] = {
//	0,	1,	2,	3,	4,
	0xFC,	0x60,	0xDA,	0xF2,	0x66,
//	5,	6,	7,	8,	9,
	0xB6,	0xBE,	0xE0,	0xFE,	0xF6,
//	A,	B,	C,	D,	E,	F,
	0xEE,	0x3E,	0x9C,	0x7A,	0x9E,	0x8E,
};

void init(void)
{
	DDRC &= 0x7C;
	PORTC |= 0x83;
	DDRA = 0xFF;
}

int main(void)
{
	unsigned char i = 0;
	init();
start:
	PORTA = num[i];
	while ((PINC & 0x01) == 0x01);		// While signal high
	while ((PINC & 0x01) != 0x01);		// While signal low
	if ((PINC & 0x02) == 0x02)
		i = i < 9 ? i + 1 : 0;
	else
		i = i > 0 ? i - 1 : 9;
	goto start;
	return 1;
}
