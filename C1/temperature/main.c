#include <stdio.h>
#define CONV(f) (((f) - 32) / 1.8)

int main(void)
{
	printf("The Celsius degree of %fF is %f\n", (float)27, CONV((float)27));
	printf("The Celsius degree of %fF is %f\n", (float)13.1, CONV((float)13.1));
	return 0;
}
