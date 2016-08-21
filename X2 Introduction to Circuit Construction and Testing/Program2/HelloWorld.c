/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <inttypes.h>
#include <ctype.h>
#include <avr/io.h>
#include <util/delay.h>

#define UNIT_LENGTH_MS 	200

static const struct
{
   const char character, *morse;
} code[] =
{
   { 'A', ".-"   },
   { 'B', "-..." },
   { 'C', "-.-." },
   { 'D', "-.."  },
   { 'E', "."    },
   { 'F', "..-." },
   { 'G', "--."  },
   { 'H', "...." },
   { 'I', ".."   },
   { 'J', ".---" },
   { 'K', ".-.-" },
   { 'L', ".-.." },
   { 'M', "--"   },
   { 'N', "-."   },
   { 'O', "---"  },
   { 'P', ".--." },
   { 'Q', "--.-" },
   { 'R', ".-."  },
   { 'S', "..."  },
   { 'T', "-"    },
   { 'U', "..-"  },
   { 'V', "...-" },
   { 'W', ".--"  },
   { 'X', "-..-" },
   { 'Y', "-.--" },
   { 'Z', "--.." },
   { ' ', " "    },
};

void LED_on(void)
{
	PORTB |= _BV(PINB7);
	_delay_ms(UNIT_LENGTH_MS);
}

void LED_off(void)
{
	PORTB &= ~_BV(PINB7);
	_delay_ms(UNIT_LENGTH_MS);
}

void output(const char* o)
{
	/*	International Morse code is composed of five elements:
	 *		dot: one unit long
	 *		dash: three units long
	 *		inter-element (between character elements) : one unit long
	 *		short gap (between letters) : three units long
	 *		medium gap (between words) : seven units long
     */
	uint8_t n = 0;
	while (o[n])
		switch (o[n++]) 
		{
			case '.' : LED_on(); LED_off(); break;
			case '-' : LED_on(); LED_on(); LED_on(); LED_off(); break;
			case ' ' : LED_off(); LED_off(); break;
		}
	LED_off(); LED_off();
}

void encode(const char *message)
{
	uint16_t i;
	uint8_t j;
  	for (i=0; message[i]; i++)
    	for (j=0; j<sizeof(code)/sizeof(*code); j++)
        	if (toupper(message[i]) == code[j].character)
				output(code[j].morse);
}

int main(void)
{
	/* set LED pin as an output */
	DDRB |= _BV(PINB7);
	/* forever loop */
	for (;;) encode("Hello World              ");
}


