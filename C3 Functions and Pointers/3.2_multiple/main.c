#include <stdio.h>
#include "rand.h"
#include "intarray.h"

#define aSize(a) (sizeof(a) / sizeof(a[0]))
#define DIS(c) {puts(#c); c;}

int main(void)
{
	int iArray[10];

	puts("Initialise randam value calculation...");
	DIS(randInit());
	putchar('\n');

	printf("Initialise (int)iArray[%d]...\n", (int)aSize(iArray));
	DIS(randIntArray(aSize(iArray), iArray));
	putchar('\n');

	printf("Print (int)iArray[%d]...\n", (int)aSize(iArray));
	DIS(printIntArray(aSize(iArray), iArray));
	putchar('\n');

	return 0;
}
