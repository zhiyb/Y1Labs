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

// (freq)kHz for 50ms
#define sound(freq) { \
	for (m = 0; m < freq * 50; m++) { \
		PORTA |= 0x01; \
		_delay_us(500 / freq); \
		PORTA &= ~0x01; \
		_delay_us(500 / freq); \
	} \
}

int main(void)
{
	uint8_t i = 0;
	uint16_t m;
	init();
start:
	PORTA = num[i];
pressed:
	while (!(PINC & 0x80));
	_delay_ms(5);		// De-bouncing
	if (!(PINC & 0x80))
		goto pressed;
notpressed1:
	while ((PINC & 0x01) == 0x01)		// While signal high
		if (!(PINC & 0x80)) {
			_delay_ms(5);		// De-bouncing
			if (PINC & 0x80)
				goto notpressed1;
			i = i < 9 ? i + 1 : 0;
			sound(4);
			goto start;
		}
notpressed2:
	while ((PINC & 0x01) != 0x01)		// While signal low
		if (!(PINC & 0x80)) {
			_delay_ms(5);		// De-bouncing
			if (PINC & 0x80)
				goto notpressed2;
			i = i < 9 ? i + 1 : 0;
			sound(4);
			goto start;
		}
	if ((PINC & 0x02) == 0x02) {
		i = i < 9 ? i + 1 : 0;
		sound(4);
	} else {
		i = i > 0 ? i - 1 : 9;
		sound(1);
	}
	goto start;
	return 1;
}
