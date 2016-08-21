#include <malloc.h>
#include <string.h>
#include "struct.h"

int main(void)
{
	struct student a, b;
	a.id = 264245;
	a.name = (char *)malloc(sizeof(char) * (strlen("Someone") + 1));
	strcpy(a.name, "Someone");
	copyStruct(&b, &a);
	printStruct(&b);
	free(a.name);
	free(b.name);
	return 0;
}
