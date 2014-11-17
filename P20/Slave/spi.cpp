#include "spi.h"

#define SPI_PORT PORTB
#define SPI_PIN PINB
#define SPI_DDR DDRB
#define SPI_SS (1 << 4)
#define SPI_MOSI (1 << 5)
#define SPI_MISO (1 << 6)
#define SPI_SCK (1 << 7)

void spi::init(void)
{
	// Slave mode, 12MHz / 4
	SPI_DDR &= ~(SPI_SS | SPI_MOSI | SPI_SCK);
	SPI_DDR |= SPI_MISO;
	SPI_PORT |= SPI_SS | SPI_MOSI | SPI_MISO | SPI_SCK;
	SPCR = _BV(SPE);// | _BV(SPR0);
	//SPSR = _BV(SPI2X);
	SPSR = 0;
}

uint8_t spi::transfer(const uint8_t value)
{
	SPDR = value;
	while(!(SPSR & _BV(SPIF)));
	return SPDR;
}

void spi::send(const uint8_t value)
{
	//while(!(SPSR & _BV(SPIF)));	// <- Will cause problem
	SPDR = value;
}

uint8_t spi::recv(void)
{
	while(!(SPSR & _BV(SPIF)));
	return SPDR;
}
