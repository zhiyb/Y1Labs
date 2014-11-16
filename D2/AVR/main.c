#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "libili9341/tft.h"

#define WRITE(addr, dat) do { \
	RAM_write(addr, dat); \
	printf("Write value: %02X, %02X\n", addr, dat); \
} while (0)
#define READ(addr) printf("Read value: %02X, %02X\n", addr, RAM_read(addr))

#define RAM_NCE		_BV(0)
#define RAM_NWE		_BV(1)
#define RAM_NOE		_BV(4)
#define RAM_ADDRCP	_BV(5)
#define RAM		(RAM_NCE | RAM_NWE | RAM_NOE)
#define RAM_ADDR	3
 
#define LOAD	(0x00 << 5)
#define STORE	(0x01 << 5)
#define ADD	(0x02 << 5)
#define SUB	(0x03 << 5)
#define BNE	(0x04 << 5)
#define LSHIFT	(0x05 << 5)
#define RSHIFT	(0x06 << 5)
#define EXTRA	(0x07 << 5)

// Extra op codes
#define LED	(0x00 << 5)
#define MOD2	(0x01 << 5)

#if 0
#define A	0x1E
#define B	0x1F
const uint8_t data[32] = {
	/* 0x00 */	LOAD	| B,	// '- MULTI'
	/* 0x01 */	BNE	| 0x1D,	// 'DO'
	/* 0x02 */	EXTRA	| 0x03,
	/* 0x03 */	LED,
	/* 0x04 */	EXTRA	| 0x05,	// '- DO'
	/* 0x05 */	MOD2,
	/* 0x06 */	BNE	| 0x1C,	// 'NZ'
	/* 0x07 */	RSHIFT,
	/* 0x08 */	STORE	| B,
	/* 0x09 */	LOAD	| A,
	/* 0x0A */	LSHIFT,
	/* 0x0B */	STORE	| A,
	/* 0x0C */	BNE	| 0x1B,	// 'MULTI'
	/* 0x0D */	SUB,		// '- NZ'
	/* 0x0E */	STORE	| B,
	/* 0x0F */	LOAD	| A,
	/* 0x10 */	ADD	| A,
	/* 0x11 */	STORE	| A,
	/* 0x12 */	BNE	| 0x1B,	// 'MULTI'
	/* 0x13 */	0x00,
	/* 0x14 */	0x00,
	/* 0x15 */	0x00,
	/* 0x16 */	0x00,
	/* 0x17 */	0x00,
	/* 0x18 */	0x00,
	/* 0x19 */	0x00,
	/* 0x1A */	0x00,
	/* 0x1B */	0x00,		// 'MULTI'
	/* 0x1C */	0x0D,		// 'NZ'
	/* 0x1D */	0x04,		// 'DO'
	/* 0x1E */	0x02,		// A
	/* 0x1F */	0x03,		// B
};
#else
const uint8_t data[32] = {
	LOAD	| 0x03,
	BNE	| 0x04,
	LED,
	0x01,
	0x01,
};
#endif

void init(void)
{
	DDRB |= 0x80;			// LED
	PORTB |= 0x80;
	tft_init();
	tft_setOrient(FlipLandscape);
	tft_setBackground(0x0000);
	tft_setForeground(0x667F);
	tft_clean();
	stdout = tftout();
	tft_setBGLight(1);
}

void RAM_write(uint8_t addr, uint8_t dat)
{
	DDRD = 0xFF;
	DDRB = 0xFF;
	PORTD = addr;
	_delay_us(10);
	PORTB = 0xFF;
	PORTB = 0xFF & ~RAM_ADDRCP;
	PORTD = dat;
	_delay_us(10);
	PORTB = RAM_NOE;
	_delay_us(10);
	PORTB = 0xFF & ~RAM_ADDRCP;
	_delay_us(10);
}

uint8_t RAM_read(uint8_t addr)
{
	uint8_t dat;
	DDRB = 0xFF;
	DDRD = 0xFF;
	PORTD = addr;
	PORTB = 0xFF;
	_delay_us(10);
	PORTB = 0xFF & ~RAM_ADDRCP;
	DDRD = 0x00;
	PORTD = 0xFF;
	PORTB = RAM_NWE;
	_delay_us(10);
	dat = PIND;
	PORTB = 0xFF & ~RAM_ADDRCP;
	_delay_us(10);
	return dat;
}

void RAM_write_all(void)
{
	uint8_t addr;
	for (addr = 0; addr < 32; addr++)
		RAM_write(addr, data[addr]);
}

void RAM_read_all(void)
{
	uint8_t addr;
	for (addr = 0; addr < 32; addr++) {
		printf("%02X, ", RAM_read(addr));
		if (addr % 4 == 3)
			putchar('\n');
	}
}

int main(void)
{
	init();

	tft_setZoom(3);

start:
	tft_clean();
	DDRB = 0xFF;
	PORTB = 0xFF & ~RAM_ADDRCP;
	RAM_read_all();
	_delay_ms(5000);
	RAM_write_all();
	tft_clean();
	RAM_read_all();
	DDRB = 0x00;
	PORTB = 0xFF;
	DDRD = 0x00;
	PORTD = 0xFF;
	_delay_ms(10000);
	goto start;

	while (1);

	return 1;
}
