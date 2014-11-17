#include "spi.h"
#include "op.h"
#include "rc4.h"

// HSM: Hardware Security Module
#define HSM_REQ	_BV(0)
#define HSM_ACK	_BV(1)

#define HIGH()	PORTB |= HSM_ACK
#define LOW()	PORTB &= ~HSM_ACK
#define READ()	PINB & HSM_REQ

const uint8_t keyIn[256] = {"Long term key, \01\06\02\07\023\065\032中文"};

void init(void)
{
	DDRB |= HSM_ACK;
	DDRB &= ~HSM_REQ;
	PORTB |= HSM_ACK | HSM_REQ;

	spi::init();
}

int main(void)
{
	init();

start:
	LOW();

	while (READ());
	while (spi::transfer() != HSM_KEY);

	// Receive key
	uint8_t key[256], len = 0;
keyRecv:
	switch (spi::transfer()) {
	case HSM_NEXT:
		key[len++] = spi::transfer();	// Cannot do XOR here, too slow
		goto keyRecv;
	case HSM_END:
		goto keyRecvEnd;
	default:
		goto start;
	}
keyRecvEnd:
	HIGH();
	// Clear remaining bytes
	for (; len != 0; len++)
		key[len] = 0;
	// Do XOR with built in key
	do
		key[len] ^= keyIn[len];
	while (++len != 0);

	// Send key stream
	class rc4 codec((char *)key, 256);
	while (!READ());
	LOW();
	while (READ())
		spi::transfer(codec.output());

	goto start;

	return 1;
}
