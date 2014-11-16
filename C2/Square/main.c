#include <stdio.h>

int main(void)
{
	int i;
	puts("Please input N:");
	for (scanf("%d", &i); i >= 0; i--)
		printf("The square of %d is %d\n", i, i * i);
	return 0;
}

