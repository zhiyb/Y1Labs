#include <stdio.h>
#include <stdlib.h>
#define CALC(n) ((n) * (n) - (n) + 41)

int main(void)
{
	int input;
	puts("Please input the value of n:");
	scanf("%d", &input);
	printf("The result is %d\n", CALC(input));
	return 0;
}
