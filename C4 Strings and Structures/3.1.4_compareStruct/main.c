#include <stdio.h>
#include "struct.h"

struct student a, b;

void compare(int ida, char *namea, int idb, char *nameb)
{
	a.id = ida;
	b.id = idb;
	a.name = namea;
	b.name = nameb;
	puts("Compare between:");
	printStruct(&a);
	printStruct(&b);
	printf("Result: %d\n", structCmp(&a, &b));
}

int main(void)
{
	compare(3, "David", 3, "Mark");
	compare(4, "Victor", 3, "Victor");
	compare(6, "Norman", 6, "Norman");
	return 0;
}
