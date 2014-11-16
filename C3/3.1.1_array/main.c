#include <stdio.h>

#define aSize(a) (sizeof(a) / sizeof(a[0]))
#define DIS(c) {puts(#c); c;}

void printArray(const unsigned int size, const double *array)
{
	unsigned int i;
	for (i = 0; i < size; i++)
		printf("Value of (double)array[%d]: %g\n", i, *(array + i));
}

void averageArray(const unsigned int size, const double *array)
{
	int s = size;
	double sum;
	while (s--)
		sum += *(array + s);
	printf("Value of average: %g\n", sum / size);
}

int main(void)
{
	unsigned int i;
	double dArray[10];

	for (i = 0; i < aSize(dArray); i++)
		dArray[i] = (i + 1) + 0.01 * (i + 2);

	DIS(printArray(aSize(dArray), dArray));
	putchar('\n');
	DIS(averageArray(aSize(dArray), dArray));

	return 0;
}
