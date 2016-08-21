#ifndef _STRUCT_H
#define _STRUCT_H

struct student {
	int id;
	char *name;
};

int structCmp(struct student *a, const struct student *b);
void printStruct(const struct student *s);

#endif
