#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define aSize(a) (sizeof(a) / sizeof(a[0]))
#define DIS(c) {puts(#c); c;}

void randInit(void)
{
	srand((unsigned)time(NULL));
}

void randIntArray(unsigned int size, int *p)
{
	while (size--)
		*p++ = rand();
}

void printIntArray(const unsigned int size, const int *p)
{
	unsigned int i;
	for (i = 0; i < size; i++)
		printf("The value of (int)array[%d] is %d\n", i, *p++);
}

int main(void)
{
	int iArray[10];

	puts("Initialise randam value calculation...");
	DIS(randInit());
	putchar('\n');

	printf("Initialise (int)iArray[%d]...\n", aSize(iArray));
	DIS(randIntArray(aSize(iArray), iArray));
	putchar('\n');

	printf("Print (int)iArray[%d]...\n", aSize(iArray));
	DIS(printIntArray(aSize(iArray), iArray));
	putchar('\n');

	return 0;
}
