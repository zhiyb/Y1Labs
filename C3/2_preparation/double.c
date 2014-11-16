#include <stdio.h>

#define aSize(a) (sizeof(a) / sizeof(a[0]))
#define DIS(c) {puts(#c); c;}

void double2Zero(double *p)
{
	*p = 0;
}

void doubleArray2Zero(unsigned int size, double *p)
{
	while (size--)
		*(p + size) = 0;
}

int main(void)
{
	unsigned int i;
	double d = 3.14159, dArray[3];

	for (i = 0; i < aSize(dArray); i++)
		dArray[i] = (i + 1) + 0.1 * (i + 2);

	printf("Value of (double)d: %g\n", d);
	DIS(double2Zero(&d));
	printf("Value of (double)d: %g\n", d);
	putchar('\n');

	for (i = 0; i < aSize(dArray); i++)
		printf("Value of (double)dArray[%d]: %g\n", i, dArray[i]);
	DIS(doubleArray2Zero(aSize(dArray), dArray));
	for (i = 0; i < aSize(dArray); i++)
		printf("Value of (double)dArray[%d]: %g\n", i, dArray[i]);

	return 0;
}
