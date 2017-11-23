#include "rc4.h"

#define SWAP(x, y) do { \
	unsigned char t = x; \
	x = y; \
	y = t; \
} while (0)

void rc4::regen(const char *key, const unsigned short length)
{
	i = 0;
	do
		s[i] = i;
	while (++i);
	j = 0;
	do {
		j = j + s[i] + key[i % length];
		SWAP(s[i], s[j]);
	} while (++i);
	j = 0;
}

unsigned char rc4::output(void)
{
	i++;
	j += s[i];
	SWAP(s[i], s[j]);
	unsigned char t = s[i] + s[j];
	return s[t];
}

void rc4::codec(unsigned char *buff, const unsigned short length)
{
	for (unsigned short l = length; l; l--, buff++)
		*buff = *buff ^ output();
}
