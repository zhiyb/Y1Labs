#include <stdio.h>
#include <string.h>
#include "struct.h"

int structCmpID(const void *pa, const void *pb)
{
	const struct student *a = pa, *b = pb;
	if (a->id != b->id)
		return a->id - b->id;
	return strcasecmp(a->name, b->name);
}

int structCmpName(const void *pa, const void *pb)
{
	int i;
	const struct student *a = pa, *b = pb;
	i = strcasecmp(a->name, b->name);
	if (i != 0)
		return i;
	return a->id - b->id;
}

void printStruct(const struct student *s)
{
	printf("Student ID is: %d\n", s->id);
	printf("Student name is: %s\n", s->name);
}
