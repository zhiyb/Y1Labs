#include <stdio.h>
#include "rand.h"
#include "floatarray.h"
#include "sort.h"

#define aSize(a) (sizeof(a) / sizeof(a[0]))
#define DIS(c) {puts(#c); c;}

int main(void)
{
	float fArray[3], oArray[3];

	puts("Initialise randam value calculation...");
	DIS(randInit());
	putchar('\n');

	printf("Fill (float)fArray[%d]...\n", (int)aSize(fArray));
	DIS(randFloatArray(aSize(fArray), fArray));
	putchar('\n');

	printf("Print (float)fArray[%d]...\n", (int)aSize(fArray));
	DIS(printFloatArray(aSize(fArray), fArray));
	putchar('\n');

	printf("Sort to (float)oArray[%d]...\n", (int)aSize(oArray));
	DIS(bubbleSort(aSize(fArray), fArray, oArray));
	putchar('\n');

	printf("Print (float)oArray[%d]...\n", (int)aSize(oArray));
	DIS(printFloatArray(aSize(oArray), oArray));
	putchar('\n');

	return 0;
}
