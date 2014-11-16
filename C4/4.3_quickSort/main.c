#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

#define TOTALNUM 5

void fill(struct student *stu)
{
	strcpy(stu->name, "Victor");
	(stu++)->id = 3;
	strcpy(stu->name, "Norman");
	(stu++)->id = 1;
	strcpy(stu->name, "David");
	(stu++)->id = 5;
	strcpy(stu->name, "Bach");
	(stu++)->id = 2;
	strcpy(stu->name, "Mark");
	(stu++)->id = 4;
}

int main(void)
{
	int i;
	struct student stu[TOTALNUM];

	printf("Fill struct student stu[%d]...\n", TOTALNUM);
	fill(stu);
	putchar('\n');

	for (i = 0; i < TOTALNUM; i++) {
		printf("Print struct student stu[%d]...\n", i);
		printStruct(&stu[i]);
	}
	putchar('\n');

	printf("Sort struct student stu[%d] by ID...\n", TOTALNUM);
	qsort((void *)&stu[0], TOTALNUM, sizeof(stu[0]), structCmpID);
	putchar('\n');

	for (i = 0; i < TOTALNUM; i++) {
		printf("Print struct student stu[%d]...\n", i);
		printStruct(&stu[i]);
	}
	putchar('\n');

	printf("Sort struct student stu[%d] by name...\n", TOTALNUM);
	qsort((void *)&stu[0], TOTALNUM, sizeof(stu[0]), structCmpName);
	putchar('\n');

	for (i = 0; i < TOTALNUM; i++) {
		printf("Print struct student stu[%d]...\n", i);
		printStruct(&stu[i]);
	}

	return 0;
}
