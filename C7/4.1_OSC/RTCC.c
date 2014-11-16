/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */
#include "i2c.h"
#include "RTCC.h"

#define READ 1
#define WRITE 0

void init_clock(void)
{
    /* TODO: Code to initiliase interface and start clock */
	init_i2c_master();
	i2c_start();
	i2c_tx(0xDE | WRITE);	// Control byte
	i2c_tx(0x00);		// Address - Second
	i2c_tx(0x00);		// Data - Start, 00
	i2c_stop();
}

void set_time(rtcc t)
{
    /* TODO: Code to set time to value in t */
	i2c_start();
	i2c_tx(0xDE | WRITE);
	i2c_tx(0x00);
	i2c_tx(0x80 + t.ten_seconds * 0x10 + t.seconds);
	i2c_tx(t.ten_minutes * 0x10 + t.minutes);
	i2c_tx(t.ten_hours * 0x10 + t.hours);
	i2c_tx(t.day);
	i2c_tx(t.ten_date * 0x10 + t.date);
	i2c_tx(t.ten_month * 0x10 + t.month);
	i2c_tx(t.ten_year * 0x10 + t.year);
	i2c_stop();
}

rtcc get_time(void)
{
    /* TODO: Code to get time from RTCC and return it in an rtcc struct */
	uint8_t d;
	rtcc t;
	i2c_start();
	i2c_tx(0xDE | WRITE);
	i2c_tx(0x00);
	i2c_start();
	i2c_tx(0xDE | READ);
	d = i2c_rx_ack() & 0x7F;
	t.ten_seconds = d / 0x10;
	t.seconds = d % 0x10;
	d = i2c_rx_ack();
	t.ten_minutes = d / 0x10;
	t.minutes = d % 0x10;
	d = i2c_rx_ack();
	t.ten_hours = d / 0x10;
	t.hours = d % 0x10;
	d = i2c_rx_ack();
	t.day = d;
	d = i2c_rx_ack();
	t.ten_date = d / 0x10;
	t.date = d % 0x10;
	d = i2c_rx_ack();
	t.ten_month = d / 0x10;
	t.month = d % 0x10;
	d = i2c_rx_nack();
	t.ten_year = d / 0x10;
	t.year = d % 0x10;
	i2c_stop();
	return t;
}

