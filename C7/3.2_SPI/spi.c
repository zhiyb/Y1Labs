/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */

#include "spi.h"

void init_spi_master(void)
{
	DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7);
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0); /* F_SCK = F_CPU/16 = 750 kHz */
}

void spi_tx(uint8_t b)
{
	SPDR = b;
	while(!(SPSR & _BV(SPIF)));
}

uint8_t spi_rx(void) {
	while(!(SPSR & _BV(SPIF)));
	return SPDR;
}
