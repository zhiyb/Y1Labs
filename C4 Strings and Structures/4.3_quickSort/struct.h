#ifndef _STRUCT_H
#define _STRUCT_H

#define NAMESIZE 10

struct student {
	int id;
	char name[NAMESIZE];
};

int structCmpID(const void *pa, const void *pb);
int structCmpName(const void *pa, const void *pb);
void printStruct(const struct student *s);

#endif
