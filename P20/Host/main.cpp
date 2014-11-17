/* Author:	yz39g13@soton.ac.uk, ss4g13@soton.ac.uk
 * Usage:	HSM_Host Keyphrase [Keyphrase length]
 * Input & Output redirection:
 * HSM_Host keyphrase < input_file > output_file
 */

#include <iostream>
#include <string>
#include <bcm2835.h>
#include "op.h"

#define TRANSFER(v)	bcm2835_spi_transfer(v)

using namespace std;

void init(void)
{
	bcm2835_init();
	bcm2835_spi_begin();
	// Approx. 2MHz
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
}

int main(int argc, char *argv[])
{
	unsigned int len;
	char *p;
	int c;
	if (argc != 2 && argc != 3) {
		cerr << "Wrong argument number!" << endl;
		return 1;
	}

	if (argc == 3)
		len = stoi(argv[2]);
	else
		len = string(argv[1]).length();
	if (len == 0 || len > 256) {
		cerr << "Key length not acceptable!" << endl;
		return 1;
	}

	init();

	// Acknowledge
	if (TRANSFER(0xFF) != HSM_KEY || TRANSFER(HSM_KEY) != HSM_KEY) {
		cerr << "HSM not accessible: " << __LINE__ << endl;
		bcm2835_spi_end();
		bcm2835_close();
		return 1;
	}

	// Send key
	p = argv[1];
	TRANSFER(len & 0xFF);
	for (unsigned int i = 0; i < len; i++)
		TRANSFER((unsigned char)*p++);

	//Wait for MCU
	while (TRANSFER(0xFF) != HSM_KEY + 1);
	TRANSFER(HSM_KEY + 1);

	// Receive key stream & codec
	while ((c = cin.get()) != -1)				// -1: Read stream failed
		cout << (char)((unsigned char)c ^ TRANSFER(0));

	// Transfer finished
	TRANSFER(0xFF);
	bcm2835_spi_end();
	bcm2835_close();
	return 0;
}
