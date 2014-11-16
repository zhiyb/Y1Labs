/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */
#include <stdint.h>

typedef struct {
	uint8_t seconds;
	uint8_t ten_seconds;
	uint8_t minutes;
	uint8_t ten_minutes;
	uint8_t hours;
	uint8_t ten_hours;
	uint8_t day;
	uint8_t date;
	uint8_t ten_date;
	uint8_t month;
	uint8_t ten_month;
	uint8_t year;
	uint8_t ten_year;
} rtcc;

void init_clock(void);
void set_time(rtcc t);
rtcc get_time(void);

