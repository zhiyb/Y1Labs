#ifndef BOX_H
#define BOX_H

#include "lcd.h"
#include "game.h"

#define BOX_SIZE 5
#define BOX_INITX ((display.width - BOX_SIZE) / 2)
#define BOX_INITY ((display.height - BOX_SIZE) / 2)
#define BOX_FGC YELLOW
#define BOX_BGC 0x1082 //0x667F
//#define BOX_TRACE_CLR_CHANGE

struct {
	uint16_t x, y;
	uint8_t dx, dy;
} box;

#include "bar.h"

static inline void box_show(uint16_t colour)
{
	rectangle rect = {
		.left = box.x,
		.right = box.x + BOX_SIZE - 1,
		.top = box.y,
		.bottom = box.y + BOX_SIZE - 1,
	};
	fill_rectangle(rect, colour);
}

static inline void box_init(void)
{
	box.x = BOX_INITX;
	box.y = BOX_INITY;
	box.dx = 1;
	box.dy = 1;
	box_show(BOX_FGC);
}

static inline void box_move(void)
{
#ifdef BOX_TRACE_CLR_CHANGE
	static uint16_t colour = 0x0000;
	box_show(colour);
	colour += 0x0841;
#else
	box_show(BOX_BGC);
#endif
movex:
	if (box.dx) {
		if (box.x == display.width - BOX_SIZE) {
			box.dx = 0;
			goto movex;
		}
		box.x += 1;
	} else {
		if (box.x <= bar.x + bar.w) {
			if (box.x == 0) {
				game_over();
				return;
			}
			if (box.x >= bar.x)
				if (box.y + BOX_SIZE >= bar.y && \
				    box.y <= bar.y + bar.h) {
					box.dx = 1;
					box.x = bar.x + bar.w;
					goto movex;
				}
		}
		box.x -= 1;
	}
movey:
	if (box.dy) {
		if (box.y == display.height - BOX_SIZE) {
			box.dy = 0;
			goto movey;
		}
		box.y += 1;
	} else {
		if (box.y == 0) {
			box.dy = 1;
			goto movey;
		}
		box.y -= 1;
	}
	box_show(BOX_FGC);
}

#endif
