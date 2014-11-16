#include "lcd.h"
#include "bar.h"
#include "box.h"
#include "timer.h"
#include "rotary.h"

#define GAME_OVER_W 200
#define GAME_OVER_H 100
#define GAME_OVER_X ((display.width - GAME_OVER_W) / 2)
#define GAME_OVER_Y ((display.height - GAME_OVER_H) / 2)
#define GAME_OVER_BGC 0x667F
#define GAME_OVER_STR "GAME OVER!"
#define GAME_OVER_STRX (GAME_OVER_X + (GAME_OVER_W - 6 * 10) / 2)
#define GAME_OVER_STRY (GAME_OVER_Y + (GAME_OVER_H - 8) / 2)
#define GAME_OVER_STR_FGC 0xF800
#define GAME_OVER_STR_BGC GAME_OVER_BGC

void game_over(void)
{
	rectangle rect = {
		.left = GAME_OVER_X,
		.right = GAME_OVER_X + GAME_OVER_W - 1,
		.top = GAME_OVER_Y,
		.bottom = GAME_OVER_Y + GAME_OVER_H - 1,
	};
	fill_rectangle(rect, GAME_OVER_BGC);
	display.x = GAME_OVER_STRX;
	display.y = GAME_OVER_STRY;
	display.foreground = GAME_OVER_STR_FGC;
	display.background = GAME_OVER_STR_BGC;
	display_string(GAME_OVER_STR);
	display.background = BLACK;
get:
	switch (ROE_get()) {
	case ROE_SW1:
	case ROE_SW2:
		goto new;
	}
	goto get;
new:
	while (ROE_get() != ROE_N);
	clear_screen();
	bar_init();
	box_init();
	timer0_init();
}
