/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */

#include "vectorFont.h"
#include "digitalPot.h"

void draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	/* Bresenham's algorithm */
	uint8_t dx, dy;
	int8_t sx, sy;
	int16_t err, e2;
	void (*nudgeX)(void);
	void (*nudgeY)(void);
	
	if (x0 < x1) {
		dx = x1 - x0;
		sx = 1;
		nudgeX = incXpot;
	} else {
		dx = x0 - x1;
		sx = -1;
		nudgeX = decXpot;
	}
	if (y0 < y1) {
		dy = y1 - y0;
		sy = 1;
		nudgeY = incYpot;
	} else {
		dy = y0 - y1;
		sy = -1;
		nudgeY = decYpot;
	}
	err = dx-dy;
	setXpot(x0);
	setYpot(y0);
	while(x0!=x1 || y0!=y1)
	{
		e2 = 2*err;
		if (e2 > -dy) { 
			err -= dy;
			x0 += sx;
			nudgeX();
		}
		if (e2 < dx) { 
			err += dx;
			y0 += sy; 
			nudgeY();
		}
	}
}

int8_t draw_char(uint8_t c, uint8_t x, uint8_t y)
{
	/* Use the Hershey font to draw vector based characters */
	int8_t x0, y0, x1, y1;
	int8_t width = 0;
	uint16_t i;
	if (c<127) {
		for(i=pgm_read_word_near(hershey_offset + c); i<pgm_read_word_near(hershey_offset + c + 1)-2; i+=2) {
			x0 = pgm_read_byte_near(hershey_vertices + i);
			y0 = pgm_read_byte_near(hershey_vertices + i + 1);
			x1 = pgm_read_byte_near(hershey_vertices + i + 2);
			y1 = pgm_read_byte_near(hershey_vertices + i + 3);
			if ((x0==-1 && y0==-1) || (x1==-1 && y1==-1))
				continue; /* Pen up */
			draw_line(x0+x, y0+y, x1+x, y1+y);
		}
		width = pgm_read_byte_near(hershey_width + c);
	}
	return width;
}

int8_t draw_digit(uint8_t i, uint8_t x, uint8_t y)
{
	if (i>=0 && i<=9)
		return draw_char(i + 48, x, y);
	else 
		return 0;
}

int8_t draw_string(char *str, uint8_t x, uint8_t y)
{
	uint8_t i;
	int8_t width = 0;

	for(i=0; str[i]; i++)
		width += draw_char(str[i], x + width, y);

	return width;
}

