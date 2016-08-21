#include <string.h>
#include "strsize.h"

void sort(const int size, char (*src)[STRSIZE], char (*dst)[STRSIZE])
{
	int swap, i;
	char tmp[STRSIZE];

	// First, copy src to dst
	for (i = 0; i < size; i++)
		strcpy(*(dst + i), *(src + i));

	// Sort output
	do {
		swap = 0;
		for (i = 0; i < size - 1; i++)
			if (strcasecmp(*(dst + i), *(dst + i + 1)) > 0) {
				strcpy(tmp, *(dst + i));
				strcpy(*(dst + i), *(dst + i + 1));
				strcpy(*(dst + i + 1), tmp);
				swap++;
			}
	} while (swap);
}
