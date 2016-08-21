#include <stdio.h>
#include <stdlib.h>

#define F(x) (2 * (x) * (x) - 3)
#define DF(x) (4 * (x))
#define NR(x) ((x) - F(x) / DF(x))

int main(void)
{
	double x0, x1;
	puts("Please specify the initial value:");
	scanf("%lg", &x1);
	do {
		x0 = x1;
		x1 = NR(x0);
	} while ((x0 != x1) && abs(x0 - x1) < 1000);
	if (abs(x0 - x1) >= 1000)
		puts("Error!");
	else
		printf("Result: %lg\n", x0);
	return 0;
}

