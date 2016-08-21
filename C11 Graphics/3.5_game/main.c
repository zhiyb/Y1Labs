#include <util/delay.h>
#include "lcd.h"
#include "rotary.h"
#include "timer.h"
#include "bar.h"
#include "box.h"

static inline void init(void)
{
	init_lcd();
	set_orientation(West);
	clear_screen();
	bar_init();
	box_init();
	ROE_init();
	timer0_init();
}

int __attribute__((noreturn)) main(void)
{
	uint8_t cheat = 0, mode = 0;
	init();

get:
	switch (ROE_get()) {
	case ROE_CW1:
		if (mode)
			bar_sizew(1);
		else
			bar_movex(1);
		break;
	case ROE_CCW1:
		if (mode)
			bar_sizew(0);
		else
			bar_movex(0);
		break;
	case ROE_CW2:
		if (mode)
			bar_sizeh(1);
		else if (!cheat)
			bar_movey(1);
		break;
	case ROE_CCW2:
		if (mode)
			bar_sizeh(0);
		else if (!cheat)
			bar_movey(0);
		break;
	case ROE_SW1:
		cheat = !cheat;
		while (ROE_get() == ROE_SW1);
		break;
	case ROE_SW2:
		mode = !mode;
		while (ROE_get() == ROE_SW2);
		break;
	default:
		if (!mode && timer0()) {
			if (cheat)
				bar_follow();
			box_move();
		}
	}
	goto get;
}
