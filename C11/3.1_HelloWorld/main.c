#include "lcd.h"

static inline void init(void)
{
	init_lcd();
	set_orientation(West);
	clear_screen();
}

int __attribute__((noreturn)) main(void)
{
	init();

	display.x = 100;
	display.y = 100;
	display.background = 0x07C0;
	display.foreground = 0xF800;
	display_string("Hello, world!");
	while (1);
}
