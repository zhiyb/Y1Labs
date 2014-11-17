#include <bcm2835.h>
#include <iostream>
#include <cstdlib>
#include "op.h"
#include "gpio.h"

#define DELAY	1000000

#define HSM_REQ	PIN(16)
#define HSM_ACK	PIN(18)

#define TRANSFER(v)	bcm2835_spi_transfer(v)

using namespace std;

void init(void)
{
	bcm2835_init();
	bcm2835_spi_begin();
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);

	GPIO_PUD_UP(HSM_REQ);
	GPIO_OUTPUT(HSM_REQ);
	GPIO_SET(HSM_REQ);
	GPIO_PUD_UP(HSM_ACK);
	GPIO_INPUT(HSM_ACK);
	GPIO_SET(HSM_ACK);
}

bool ackCheck(bool high)
{
	unsigned long i;
	for (i = 0; i < DELAY; i++)
		if (high ? GPIO_READ(HSM_ACK) : !GPIO_READ(HSM_ACK))
			break;
	if (i == DELAY)
		return false;
	return true;
}

int main(int argc, char *argv[])
{
	{
		if (argc != 3) {
			cerr << "Wrong argument number!" << endl;
			goto err;
		}

		unsigned int len = atoi(argv[2]);
		if (len > 256) {
			cerr << "Key too long!" << endl;
			goto err;
		}

		init();

		if (GPIO_READ(HSM_ACK)) {
			cerr << "HSM not accessible!" << endl;
			goto err;
		}

		GPIO_CLR(HSM_REQ);
		//TRANSFER(0xFF);
		TRANSFER(HSM_KEY);

		// Send key
		char *p = argv[1];
		for (unsigned int i = 0; i < len; i++) {
			TRANSFER(HSM_NEXT);
			TRANSFER((unsigned char)*p++);
		}
		TRANSFER(HSM_END);

		if (!ackCheck(true)) {
			cerr << "HSM response timed out! " << __LINE__ << endl;
			goto err;
		}
		GPIO_SET(HSM_REQ);

		if (!ackCheck(false)) {
			cerr << "HSM response timed out! " << __LINE__ << endl;
			goto err;
		}
		// Receive key stream & codec
		int c;
		while ((c = cin.get()) != -1)
			cout << (char)((unsigned char)c ^ TRANSFER(c));

		GPIO_CLR(HSM_REQ);
		TRANSFER(0xFF);

		GPIO_SET(HSM_REQ);
		bcm2835_spi_end();
		bcm2835_close();
		return 0;
	}
 err:
	bcm2835_spi_end();
	bcm2835_close();
	return 1;
}
