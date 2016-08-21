#ifndef BAR_H
#define BAR_H

#include "lcd.h"

#define BAR_INITH 50
#define BAR_INITW 3
#define BAR_INITX 0
#define BAR_INITY ((display.height - BAR_INITH) / 2)
#define BAR_INTVX 3
#define BAR_INTVY 10
#define BAR_FGC GREEN
#define BAR_BGC BLACK

struct {
	uint16_t x, y;
	uint8_t w, h;
} bar;

#include "box.h"

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

static inline void bar_init(void)
{
	bar.x = BAR_INITX;
	bar.y = BAR_INITY;
	bar.w = BAR_INITW;
	bar.h = BAR_INITH;
	bar_show(BAR_FGC);
}

static inline void bar_movex(uint8_t dir)
{
	bar_show(BAR_BGC);
	if (dir) {
		if (bar.x + bar.w < display.width - BOX_SIZE - BAR_INTVX - 1)
			bar.x += BAR_INTVX;
		else
			bar.x = display.width - bar.w - BOX_SIZE - 1;
	} else {
		if (bar.x > BAR_INTVX)
			bar.x -= BAR_INTVX;
		else
			bar.x = 0;
	}
	bar_show(BAR_FGC);
}

static inline void bar_movey(uint8_t dir)
{
	bar_show(BAR_BGC);
	if (dir) {
		if (bar.y + bar.h < display.height - BAR_INTVY)
			bar.y += BAR_INTVY;
		else
			bar.y = display.height - bar.h;
	} else {
		if (bar.y > BAR_INTVY)
			bar.y -= BAR_INTVY;
		else
			bar.y = 0;
	}
	bar_show(BAR_FGC);
}

static inline void bar_sizew(uint8_t dir)
{
	bar_show(BAR_BGC);
	if (dir)
		bar.w += bar.w < BAR_INITW;
	else
		bar.w -= bar.w > 1;
	if (bar.x + bar.w > display.width - BOX_SIZE - 1)
		bar.x = display.width - bar.w - BOX_SIZE - 1;
	bar_show(BAR_FGC);
}

static inline void bar_sizeh(uint8_t dir)
{
	bar_show(BAR_BGC);
	if (dir)
		bar.h += bar.h < BAR_INITH * 3;
	else
		bar.h -= bar.h > 1;
	if (bar.y + bar.h > display.height)
		bar.y = display.height - bar.h;
	bar_show(BAR_FGC);
}

static inline void bar_follow(void)
{
	bar_show(BAR_BGC);
	if (box.y < bar.h / 2)
		bar.y = 0;
	else if (box.y > display.height - bar.h / 2)
		bar.y = display.height - bar.h;
	else
		bar.y = box.y - bar.h / 2;
	if (bar.x + bar.w > box.x) {
		if (box.x < bar.w)
			bar.x = 0;
		else
			bar.x = box.x - bar.w;
	}
	bar_show(BAR_FGC);
}

static inline void bar_cheat(uint8_t e)
{
	if (e) {
		bar.y = 0;
		bar.h = display.height;
		bar_show(BAR_FGC);
	} else {
		bar_show(BAR_BGC);
		bar.y = BAR_INITY;
		bar.h = BAR_INITH;
		bar_show(BAR_FGC);
	}
}

#endif
