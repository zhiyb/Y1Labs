#include <stdio.h>
#include "strcmp.h"

#define COM(a, b) { \
	puts("Compare between " a " and " b); \
	printf("Result: %d\n", strCmp(a, b)); \
}

int main(void)
{
	COM("Hello", "HelloWorld");
	COM("HelloWorld", "Hello");
	COM("aaa", "aab");
	COM("aba", "aaa");
	COM("Hello, world!", "Hello, world!");
	return 0;
}
