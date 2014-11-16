#include <stdio.h>
#include "sort.h"

#define SIZE 5

void print(const int size, char (*s)[STRSIZE])
{
	int i;
	for (i = 0; i < size; i++)
		printf("Element %d: %s\n", i, *(s + i));
}

int main(void)
{
	char src[SIZE][STRSIZE] = {
		"Hello, world!",
		"hello",
		"Actually",
		"Zepler",
		"26424",
	}, dst[SIZE][STRSIZE];

	printf("Print src[%d][%d]...\n", SIZE, STRSIZE);
	print(SIZE, src);
	putchar('\n');

	puts("Sort src to dst...");
	sort(SIZE, src, dst);
	putchar('\n');

	printf("Print dst[%d][%d]...\n", SIZE, STRSIZE);
	print(SIZE, dst);
	putchar('\n');

	return 0;
}
