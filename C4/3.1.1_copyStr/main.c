#include <stdio.h>
#include "copy.h"

int main(void)
{
	char input[15] = "Hello World!", output[15];
	copy(output, input);
	puts(output);
	return 0;
}
