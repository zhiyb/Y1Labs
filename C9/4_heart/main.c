#include <util/delay.h>
#include <stdio.h>
//#include "tft.h"
#include "debug.h"
#include "adc.h"

#define VOLT 3.3
#define PROX 0x200
#define HEART 2

void init(void)
{
	ADC_init();
	//TFT_init();
	//stdout = tftout();
	//stderr = tftout();
	init_debug_uart0();
	DDRB |= _BV(7);
}

int main(void)
{
	uint8_t flag = 0, calc = 0;
	init();

	puts("*** ADC for C9 ***");
	while (1) {
		uint16_t res;
		ADC_channel(1);
		res = ADC_read();
		if (res > PROX) {
			PORTB &= ~_BV(7);
			flag = 0;
			calc = 0;
			continue;
		}
		ADC_channel(2);
		res = ADC_read();
		calc++;
		PORTB &= ~_BV(7);
		if (res > HEART) {
			if (!flag) {
				printf("Res: 0x%X, v: %fV, BPM: %f\n", \
					res, VOLT * res / 1024, \
					600.0 / calc);
				PORTB |= _BV(7);
				flag = 1;
				calc = 0;
			}
		} else
			flag = 0;
		_delay_ms(100);
	}

	return 1;
}
