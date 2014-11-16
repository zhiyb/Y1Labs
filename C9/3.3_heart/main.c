#include <util/delay.h>
#include <stdio.h>
//#include "tft.h"
#include "debug.h"
#include "adc.h"

#define VOLT 3.3
#define VAL 400

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
	uint8_t flag = 0;
	init();

	puts("*** ADC for C9 ***");
	while (1) {
		uint16_t res;
		ADC_channel(2);
		res = ADC_read();
		printf("Result: 0x%X, volt: %fV\n", res, VOLT * res / 1024);
		if (res > VAL) {
			if (!flag) {
				PORTB |= _BV(7);
				_delay_ms(100);
				PORTB &= ~_BV(7);
				_delay_ms(100);
				flag = 1;
			} else
				_delay_ms(200);
		} else {
			PORTB &= ~_BV(7);
			_delay_ms(200);
			flag = 0;
		}
	}

	return 1;
}
