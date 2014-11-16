#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	int i;

	printf("Ten random numbers from 0 to 99\n\n");
	srand((unsigned)time(NULL));
	for (i = 0; i < 10; i++) {
		printf("%d\n", rand() % 100);
	}

	return 0;
}
