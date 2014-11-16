/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */

#include <stdint.h>

void draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
uint8_t draw_char(uint8_t c, uint8_t x, uint8_t y);
uint8_t draw_digit(uint8_t i, uint8_t x, uint8_t y);
int8_t draw_string(char *str, uint8_t x, uint8_t y);

