#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <inttypes.h>

namespace spi {
	void init(void);
	uint8_t transfer(const uint8_t value = 0xFF);
	void send(const uint8_t value = 0xFF);
	uint8_t recv(void);
}

#endif
