#include <stdio.h>
#include <string.h>
#include "struct.h"

int structCmp(struct student *a, const struct student *b)
{
	if (a->id != b->id)
		return a->id > b->id;
	return strcasecmp(a->name, b->name);
}

void printStruct(const struct student *s)
{
	printf("Student ID is: %d\n", s->id);
	printf("Student name is: %s\n", s->name);
}
