#include <stdio.h>

int main(void)
{
	int i;
	puts("Please input N:");
	for (scanf("%d", &i); i >= 0; i--)
		printf("The %s of %d is %d\n", i % 2 ? "triple" : "square", \
			i, i % 2 ? i * i * i : i * i);
	return 0;
}

