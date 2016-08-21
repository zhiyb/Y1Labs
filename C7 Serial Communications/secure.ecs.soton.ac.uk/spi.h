/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */

#include <avr/io.h>

void init_spi_master(void);
void spi_tx(uint8_t b);
uint8_t spi_rx(void);

