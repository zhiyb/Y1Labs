#include <util/delay.h>
#include "RTCC.h"
#include "debug.h"
#include "digitalPot.h"
#include "vectorGraphics.h"

int main(void)
{
	char time[9];
	rtcc t = {
		.seconds = 6,
		.ten_seconds = 5,
		.minutes = 4,
		.ten_minutes = 3,
		.hours = 2,
		.ten_hours = 1,
	};
	init_debug_uart0();
	init_pot();
	puts("Input current time:");
	t.ten_hours = getchar() - '0';
	t.hours = getchar() - '0';
	t.ten_minutes = getchar() - '0';
	t.minutes = getchar() - '0';
	t.ten_seconds = getchar() - '0';
	t.seconds = getchar() - '0';
	puts("3.3 RTCC - Initialise");
	init_clock();
	puts("3.3 RTCC - Set time");
	set_time(t);
	puts("3.3 RTCC - Loop start");
	while (1) {
		t = get_time();
		time[0] = t.ten_hours + '0';
		time[1] = t.hours + '0';
		time[2] = ':';
		time[3] = t.ten_minutes + '0';
		time[4] = t.minutes + '0';
		time[5] = ':';
		time[6] = t.ten_seconds + '0';
		time[7] = t.seconds + '0';
		time[8] = '\0';
		draw_string(time, 0, 0);
	}
	return 1;
}
