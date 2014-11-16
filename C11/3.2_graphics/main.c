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

	{
		rectangle rect = {
			.left = (display.width - 200) / 2,
			.right = rect.left + 200 - 1,
			.top = (display.height - 100) / 2,
			.bottom = rect.top + 100 - 1,
		};

		fill_rectangle(rect, YELLOW);
	}
	while (1);
}
