#include <util/delay.h>
#include "RTCC.h"
#include "debug.h"

int main(void)
{
	rtcc t = {
		.seconds = 6,
		.ten_seconds = 5,
		.minutes = 4,
		.ten_minutes = 3,
		.hours = 2,
		.ten_hours = 1,
	};
	init_debug_uart0();
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
		printf("%02d:%02d:%02d\n", t.ten_hours * 10 + t.hours, \
				t.ten_minutes * 10 + t.minutes, \
				t.ten_seconds * 10 + t.seconds);
		_delay_ms(5000);
	}
	return 1;
}
