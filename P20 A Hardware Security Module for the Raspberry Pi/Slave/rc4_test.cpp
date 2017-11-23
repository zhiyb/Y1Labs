#include <stdio.h>
#include <string.h>
#include "rc4.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	char key[16] = {0};
	memcpy(key, argv[1], strlen(argv[1]));
	rc4 enc(key, sizeof(key));
	int c;
	while ((c = getchar()) != -1)
		putchar(c ^ enc.output());
	return 0;
}
