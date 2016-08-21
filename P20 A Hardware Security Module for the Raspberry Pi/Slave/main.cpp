#include "spi.h"
#include "op.h"
#include "rc4.h"

const uint8_t keyIn[256] = {"Long term key, \01\06\02\07\023\065\032中文"};

int main(void)
{
	spi::init();

start:
	// Acknowledge
	while (spi::transfer(HSM_KEY) != HSM_KEY);

	// Receive key
	uint8_t key[256], i = 0, len;
	len = spi::transfer();
	//do
	while (i != len)
		key[i++] = spi::transfer();	// Cannot do XOR here: slow
	//while (i != len);

	// RC4 keystream preparation
	// Clear remaining bytes
	for (; len != 0; len++)			// 8Byte, 256 == 0
		key[len] = 0;
	// Do XOR with built in key
	do
		key[len] ^= keyIn[len];
	while (++len != 0);
	class rc4 codec((char *)key, 256);
	i = codec.output();

	while (spi::transfer(HSM_KEY + 1) != HSM_KEY + 1);

	// Send key stream
	do {	// A CPU time saver method, use i as buffer
		spi::send(i);
		i = codec.output();
	} while (spi::recv() == 0);

	goto start;

	return 1;
}
