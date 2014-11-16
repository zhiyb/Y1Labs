#include <stdio.h>
#include "rand.h"
#include "intarray.h"
#include "matrix.h"

#define SIZE 5

int main(void)
{
	int a[SIZE * SIZE], b[SIZE * SIZE], c[SIZE * SIZE];

	puts("Initialise randam value calculation...");
	randInit();
	putchar('\n');

	printf("Fill 'a[%d]' with random values below 1000...\n", SIZE * SIZE);
	randIntArray(SIZE * SIZE, a, 1000);
	printIntArray(SIZE * SIZE, a);
	putchar('\n');

	puts("Output 'a' in matrix format...");
	printMatrix(SIZE, a);
	putchar('\n');

	puts("Horizontal flip from 'a' to 'b'...");
	hFlipMatrix(SIZE, a, b);
	printMatrix(SIZE, b);
	putchar('\n');

	puts("Vertical flip from 'b' to 'c'...");
	vFlipMatrix(SIZE, b, c);
	printMatrix(SIZE, c);

	return 0;
}
