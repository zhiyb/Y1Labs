#include <malloc.h>
#include <string.h>
#include "struct.h"
//#include "copy.h"

void copyStruct(struct student *o, const struct student *i)
{
	o->id = i->id;
	o->name = (char *)malloc(sizeof(char) * (strlen(i->name) + 1));
	strcpy(o->name, i->name);
	//copy(o->name, i->name);
}

void printStruct(const struct student *s)
{
	printf("Student ID is: %d\n", s->id);
	printf("Student name is: %s\n", s->name);
}
