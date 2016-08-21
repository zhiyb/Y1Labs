#include <stdio.h>
#include "rand.h"
#include "intarray.h"
#include "matrix.h"

#define SIZE 5

int main(void)
{
	int a[SIZE * SIZE], b[SIZE * SIZE];
	int ma[SIZE][SIZE], mb[SIZE][SIZE], mc[SIZE][SIZE];

	puts("Initialise randam value calculation...");
	randInit();
	putchar('\n');

	printf("Fill 'a[%d]' with random values below 1000...\n", SIZE * SIZE);
	randIntArray(SIZE * SIZE, a, 1000);
	printIntArray(SIZE * SIZE, a);
	putchar('\n');

	printf("Convert 'a[%d]' to 'ma[%d][%d]'...\n", SIZE * SIZE, SIZE, SIZE);
	conv2Matrix(SIZE, a, ma);
	printMatrix(SIZE, ma);
	putchar('\n');

	puts("Horizontal flip from 'ma' to 'mb'...");
	hFlipMatrix(SIZE, ma, mb);
	printMatrix(SIZE, mb);
	putchar('\n');

	puts("Vertical flip from 'mb' to 'mc'...");
	vFlipMatrix(SIZE, mb, mc);
	printMatrix(SIZE, mc);
	putchar('\n');

	printf("Convert 'mb[%d][%d]' to 'b[%d]'...\n", SIZE, SIZE, SIZE * SIZE);
	conv2Array(SIZE, mb, b);
	printIntArray(SIZE * SIZE, b);

	return 0;
}
