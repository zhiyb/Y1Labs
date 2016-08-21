#include <stdio.h>

int main(int argc, char *argv[])
{
#if 0
	for (int i = 0; i < argc; i++) {
		printf("The %dth argument: ", i);
		puts(argv[i]);
	}
#endif

	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d\n", a < b ? a : b);

	return 0;
}

