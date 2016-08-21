#include <util/delay.h>
#include "digitalPot.h"

#define delay() _delay_us(0)

int main(void)
{
	init_pot();

	while (1) {
		uint8_t i = 0;
		setXpot(0x00);
		setYpot(0x00);
		delay();
		while (i++ != 255) {
			incXpot();
			incYpot();
			delay();
		}
	}
	return 1;
}
