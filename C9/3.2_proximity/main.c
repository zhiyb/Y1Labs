#include <util/delay.h>
#include <stdio.h>
//#include "tft.h"
#include "debug.h"
#include "adc.h"

#define VOLT 3.3
#define VAL 0x200

void init(void)
{
	ADC_init();
	ADC_channel(1);
	//TFT_init();
	//stdout = tftout();
	//stderr = tftout();
	init_debug_uart0();
	DDRB |= _BV(7);
}

int main(void)
{
	init();

	puts("*** ADC for C9 ***");
	while (1) {
		uint16_t res = ADC_read();
		if (res < VAL)
			PORTB |= _BV(7);
		else
			PORTB &= ~_BV(7);
		printf("Result: 0x%X, volt: %fV\n", res, VOLT * res / 1024);
		_delay_ms(200);
	}

	return 1;
}
