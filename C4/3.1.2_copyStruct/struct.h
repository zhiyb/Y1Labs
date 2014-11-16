#ifndef _STRUCT_H
#define _STRUCT_H

struct student {
	int id;
	char *name;
};

void copyStruct(struct student *o, const struct student *i);
void printStruct(const struct student *s);

#endif
