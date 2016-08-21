#include "rc4.h"

#define SWAP(x, y) do { \
	x = x ^ y; \
	y = x ^ y; \
	x = x ^ y; \
} while (0)

void rc4::regen(const char *key, const unsigned short length)
{
	for (i = 0; i < 256; i++)
		s[i] = i;
	j = 0;
	for (i = 0; i < 256; i++) {
		j = (j + s[i] + key[i % length]) % 256;
		SWAP(s[i], s[j]);
	}
	i = 0;
	j = 0;
}

unsigned char rc4::output(void)
{
	i = (i + 1) % 256;
	j = (j + s[i]) % 256;
	SWAP(s[i], s[j]);
	return s[(s[i] + s[j]) % 256];
}

void rc4::codec(unsigned char *buff, const unsigned short length)
{
	for (int l = length; l; l--, buff++)
		*buff = *buff ^ output();
}
