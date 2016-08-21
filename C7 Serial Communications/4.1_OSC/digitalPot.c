/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */

#include "spi.h"

void init_pot(void)
{
    /* TODO: Code to initiliase interface */
	init_spi_master();
	spi_tx(0x43);		// TCON: Write 0x03FF
	spi_tx(0xFF);		// TCON: Write 0x03FF
}

void decXpot(void)
{
    /* TODO: Code to decrement first pot by 1 */
	spi_tx(0x08);		// Decrement Wiper 0
}

void incXpot(void)
{
    /* TODO: Code to increment first pot by 1 */
	spi_tx(0x04);		// Increment Wiper 0
}

void decYpot(void)
{
    /* TODO: Code to decrement second pot by 1 */
	spi_tx(0x18);		// Decrement Wiper 1
}

void incYpot(void)
{
    /* TODO: Code to increment second pot by 1 */
	spi_tx(0x14);		// Increment Wiper 1
}

void setXpot(uint8_t x)
{
    /* TODO: Code to set first pot to a value between 0 and 255 */
	spi_tx(0x00);		// Wiper 0: Write Data (10-bit, first 2 is 00)
	spi_tx(x);		// Data
}

void setYpot(uint8_t y)
{
    /* TODO: Code to set second pot to a value between 0 and 255 */
	spi_tx(0x10);		// Wiper 1: Write Data (10-bit, first 2 is 00)
	spi_tx(y);		// Data
}

