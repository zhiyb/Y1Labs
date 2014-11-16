#include <util/delay.h>
#include "lcd.h"

#define STARTX ((display.width - SIZE) / 2)
#define STARTY ((display.height - SIZE) / 2)
#define SIZE 5
#define BGC (0x0841 * 2)
#define FGC YELLOW
//#define COLOUR_CHANGE
#define DELAY() _delay_ms(4)

uint8_t xd, yd;
uint16_t x, y;

static inline void object_show(uint16_t colour)
{
	rectangle rect = {
		.left = x,
		.right = x + SIZE - 1,
		.top = y,
		.bottom = y + SIZE - 1,
	};
	fill_rectangle(rect, colour);
}

static inline void object_move(void)
{
#ifdef COLOUR_CHANGE
	static uint16_t colour = 0x0000;
	object_show(colour);
	colour += 0x0841;
#else
	object_show(BGC);
#endif
movex:
	if (xd) {	// Moving right
		if (x == display.width - SIZE) {
			xd = 0;
			goto movex;
		}
		x++;
	} else {	// Moving left
		if (x == 0) {
			xd = 1;
			goto movex;
		}
		x--;
	}
movey:
	if (yd) {	// Moving down
		if (y == display.height - SIZE) {
			yd = 0;
			goto movey;
		}
		y++;
	} else {	// Moving up
		if (y == 0) {
			yd = 1;
			goto movey;
		}
		y--;
	}
	object_show(FGC);
}

static inline void init(void)
{
	init_lcd();
	set_orientation(West);
	clear_screen();
	x = STARTX;
	y = STARTY;
	xd = 1;
	yd = 1;
	object_show(BGC);
}

int __attribute__((noreturn)) main(void)
{
	init();

	while (1) {
		DELAY();
		object_move();
	}
}
