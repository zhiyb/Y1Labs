#include <util/delay.h>
#include <stdio.h>
//#include "tft.h"
#include "debug.h"
#include "adc.h"

#define VOLT 3.3

void init(void)
{
	ADC_init();
	ADC_channel(0);
	init_debug_uart0();
	//TFT_init();
	//stdout = tftout();
	//stderr = tftout();
}

int main(void)
{
	init();

	puts("*** ADC for C9 ***");
	while (1) {
		uint16_t res = ADC_read();
		printf("Result: 0x%X, volt: %fV\n", res, VOLT * res / 1024);
		_delay_ms(1000);
	}

	return 1;
}
