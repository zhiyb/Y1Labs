#include <stdlib.h>
#include <stdio.h>

void randFloatArray(unsigned int size, float *p)
{
	while (size--)
		*(p + size) = rand() * 0.000001;
}

void printFloatArray(const unsigned int size, const float *p)
{
	unsigned int i;
	for (i = 0; i < size; i++)
		printf("The value of (float)array[%d] is %g\n", i, *(p + i));
}
