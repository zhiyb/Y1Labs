#include <util/delay.h>
#include "lcd.h"
#include "rotary.h"

#define BAR_INITH 50
#define BAR_INITW 3
#define BAR_INITX 3
#define BAR_INITY ((display.height - BAR_INITH) / 2)
#define BAR_INTV 5
#define BAR_FGC GREEN
#define BAR_BGC BLACK

struct {
	uint16_t x, y;
	uint8_t w, h;
} bar;

static inline void bar_show(uint16_t colour)
{
	rectangle rect = {
		.left = bar.x,
		.right = bar.x + bar.w - 1,
		.top = bar.y,
		.bottom = bar.y + bar.h - 1,
	};
	fill_rectangle(rect, colour);
}

static inline void init(void)
{
	init_lcd();
	set_orientation(West);
	clear_screen();
	bar.x = BAR_INITX;
	bar.y = BAR_INITY;
	bar.w = BAR_INITW;
	bar.h = BAR_INITH;
	bar_show(BAR_FGC);
	ROE_init();
}

int __attribute__((noreturn)) main(void)
{
	init();

get:
	switch (ROE_get()) {
	case ROE_CW1:
	case ROE_CW2:
		bar_show(BAR_BGC);
		if (bar.y + bar.h < display.height)
			bar.y += BAR_INTV;
		else
			bar.y = display.height - bar.h;
		bar_show(BAR_FGC);
		break;
	case ROE_CCW1:
	case ROE_CCW2:
		bar_show(BAR_BGC);
		if (bar.y > BAR_INTV)
			bar.y -= BAR_INTV;
		else
			bar.y = 0;
		bar_show(BAR_FGC);
		break;
	}
	goto get;
}
