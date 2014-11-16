/*  Author: Steve Gunn & Rex Bannerman
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: To minimise unwanted interactions in the test:
 *   			- Power from the external supply
 *              - Attach interface cable for download after tests complete
 *
 *          LED D1 does not interfere with the test and JP3 should be set to Usr.
 *          Test results are limited to 512 bytes to be compatible with the EEPROM 
 *          for all devices in the ATmega*4PA family. The first 8 bytes are used 
 *          to store a test identifier, which is incremented on each new run.
 */

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/delay.h>

#define PIN(port)   _SFR_IO8(0x00 + (((port) - 'A') * 3))
#define DDR(port)   _SFR_IO8(0x01 + (((port) - 'A') * 3))
#define PORT(port)  _SFR_IO8(0x02 + (((port) - 'A') * 3))

uint8_t write_eeprom(char *message, uint16_t index)
{
	uint8_t length = strlen(message);
	eeprom_write_block(message, (void *)index, length);
	return length;
}

void fill_eeprom(char c, uint16_t start_index)
{
	uint16_t index;
	for(index=start_index; index<=E2END; index++) 
		eeprom_write_byte((uint8_t *)index, c);
}

void update_test_identifier(void)
{
	char id[8];
	uint8_t i=4;
	eeprom_read_block(id, 0, 8);	
	do  /* Increment test counter */ 
		id[i] = (id[i]=='9' ? '0' : id[i] + 1);
	while(id[i--]=='0' && i>0);
	eeprom_write_block((id[0]=='{') ? id : "{0000}\r\n", 0, 8);
}

void port_test(char port, char* result)
{
	uint8_t pattern, pass=0x00;
	/* Set 8-bits of out port as outputs */
	DDR(port) = 0xFF;  
	/* Set test pattern as 0b10000000 and shift bit for each test */
	for(pattern=0x80; pattern>0x00; pattern >>= 1)
	{
		/* Set output bit low and turn on pull-ups on input bits  */
		PORT(port) = 0xFF - pattern;
		/* Configure 7-bits of port as inputs and 1-bit as output */ 
		DDR(port) = pattern;
		/* Small delay for synchronisation                        */
		asm("nop");
		/* Are all the input bits still high? (PASS)              */
		if (PIN(port)==0xFF-pattern)
			pass+=pattern;
	}
	sprintf(result, "%c->%c: 0x%02X 0x%02X [%s]\r\n", port, port, 
			pass, 0xFF - pass, (pass==0xFF) ? "PASS" : "FAIL");
}

void io_test(char out, char in, char* result)
{
	uint8_t fl, fh, hi, lo;
	PORT(in)  = 0xFF;  /* Enable pull-ups on input port     */
	DDR(in)   = 0x00;  /* Set 8-bits of in port as inputs   */
	PORT(out) = 0xFF;  /* Set all output bits high          */
	DDR(out)  = 0xFF;  /* Set 8-bits of out port as outputs */
	asm("nop");        /* Small delay for synchronisation   */
	hi = PIN(in);      /* Read inputs with pull-ups         */
	PORT(out) = 0x00;  /* Set all output bits low           */
	asm("nop");        /* Small delay for synchronisation   */
	lo = PIN(in);      /* Read inputs with pull-ups         */
	PORT(in)  = 0x00;  /* Disable pull-ups on input port    */
	asm("nop");        /* Small delay for synchronisation   */
	fl = PIN(in);      /* Read inputs with tri-state        */
	PORT(out) = 0xFF;  /* Set all output bits high          */
	asm("nop");        /* Small delay for synchronisation   */
	fh = PIN(in);      /* Read inputs with tri-state        */
	sprintf(result, "%c->%c: 0x%02X 0x%02X 0x%02X 0x%02X [%s]\r\n", out, in, 
			hi, lo, fh, fl, (hi==0xFF && lo==0x00) ? "PASS" : "FAIL");
}

int main(void)
{
	char out, in, test_result[255];
	uint16_t eeprom_index = 8;	
	/* Disable watchdog timer */
	MCUSR &= ~_BV(WDRF);
	wdt_disable();
	/* Disable JTAG in software, so that it does not interfere with Port C        */
	MCUCR |= _BV(JTD);
	MCUCR |= _BV(JTD);
	/* Perform tests and store the results in the EEPROM.                         */
	update_test_identifier();
	for(out='A'; out<='D'; out++)
		for(in='A'; in<='D'; in++)
		{
			if (out==in)
				port_test(out, test_result);
			else
				io_test(out, in, test_result);
			eeprom_index += write_eeprom(test_result, eeprom_index);
		}
	fill_eeprom(' ', eeprom_index);
	/* Enable watchdog timer and wait for it to generate a reset to enter the BL. */
	wdt_enable(WDTO_15MS);	
	while(1);
}
