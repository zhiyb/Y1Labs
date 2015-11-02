#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <tft.h>
#include <colours.h>
#include <macros.h>

using namespace colours::b16;

struct rectangle
{
	uint8_t x;
	uint16_t y;
	uint8_t w, h;
};

void init()
{
	DDRB |= 1 << 7;		// LED
	PORTB |= 1 << 7;
	DDRD = 0x00;
	PORTD = 0xff;

	tft::init();
	stdout = tft::devout();
	sei();
}

#define SX	60
#define SY	45
#define SW	90
#define SH	25

int main()
{
	static const rectangle rects[8][4] = {
		{SX, SY, SW, SH},			// a
		{SX + SW, SY + SH, SH, SW},		// b
		{SX + SW, SY + SH + SW + SH, SH, SW},	// c
		{SX, SY + SH + SW + SH + SW, SW, SH},	// d
		{SX - SH, SY + SH + SW + SH, SH, SW},	// e
		{SX - SH, SY + SH, SH, SW},		// f
		{SX, SY + SH + SW, SW, SH},		// g
		{SX + SW + SH * 2, SY + SH + SW + SH + SW, SH, SH},	// dp
	};
	init();
	tft::setBGLight(true);

poll:
	uint8_t status = PIND;
	for (uint8_t i = 0; i != 8; i++) {
		uint16_t clr;
		if (status & 0x80)
			clr = Green;
		else
			clr = COLOUR_565(0x3f, 0x3f, 0x3f);
		const rectangle *rect = rects[i];
		tft::rectangle(rect->x, rect->y, rect->w, rect->h, clr);
		status <<= 1;
	}
	goto poll;
	return 1;
}
