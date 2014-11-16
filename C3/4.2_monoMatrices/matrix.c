#include <stdio.h>

void printMatrix(const int size, const int *m)
{
	int i, j;
	for (i = 0; i < size; i++) {
		putchar('{');
		for (j = 0; j < size; j++)
			printf("%d,\t", *(m + i * size + j));
		puts("},");
	}
}

void hFlipMatrix(const int size, const int *a, int *b)
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			*(b + i * size + j) = *(a + i * size + (size - j - 1));
}

void vFlipMatrix(const int size, const int *a, int *b)
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			*(b + i * size + j) = *(a + (size - i - 1) * size + j);
}
