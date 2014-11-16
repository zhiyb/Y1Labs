#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

void initRand(void)
{
	srand((unsigned)time(NULL));
}

int askSize(void)
{
	int n;
	puts("Size of random `double' array?");
	scanf("%d", &n);
	if (n < 0) {
		fputs("Cannot accept a negative number!\n", stderr);
		exit(1);
	}
	return n;
}

void fillDoubleArray(int n, double *p)
{
	while(n--)
		*(p++) = (double)rand() / RAND_MAX;
}

void printDoubleArray(int n, double *p)
{
	int i = 0;
	while (n--)
		printf("Element %d is %g\n", i++, *(p++));
}

int main(void)
{
	int n = askSize();
	double *p = malloc(n * sizeof(double));
	initRand();
	fillDoubleArray(n, p);
	printDoubleArray(n, p);
	free(p);
	return 0;
}
