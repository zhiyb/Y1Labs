#include <stdio.h>
#include <string.h>

struct student {
	int id;
	char name[32];
};

int main(void)
{
	struct student a;
	a.id = 26424;
	strcpy(a.name, "Norman");
	printf("Student ID: %d, name: %s\n", a.id, a.name);
	return 0;
}
