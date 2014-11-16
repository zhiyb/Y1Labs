#include <stdlib.h>
#include <stdio.h>

void randIntArray(unsigned int size, int *p)
{
	while (size--)
		*(p + size) = rand();
}

void printIntArray(const unsigned int size, const int *p)
{
	unsigned int i;
	for (i = 0; i < size; i++)
		printf("The value of (int)array[%d] is %d\n", i, *(p + i));
}
