#include <stdio.h>

void conv2Matrix(const int size, const int *a, int (*m)[size])
{
	int i;
	for (i = 0; i < size * size; i++)
		m[i / size][i % size] = a[i];
}

void conv2Array(const int size, int (*m)[size], int *a)
{
	int i;
	for (i = 0; i < size * size; i++)
		a[i] = m[i / size][i % size];
}

void printMatrix(const int size, int (*ma)[size])
{
	int i, j;
	for (i = 0; i < size; i++) {
		putchar('{');
		for (j = 0; j < size; j++)
			printf("%d,\t", ma[i][j]);
		puts("},");
	}
}

void hFlipMatrix(const int size, int (*ma)[size], int (*mb)[size])
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			mb[i][j] = ma[i][size - j - 1];
}

void vFlipMatrix(const int size, int (*ma)[size], int (*mb)[size])
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			mb[i][j] = ma[size - i - 1][j];
}
