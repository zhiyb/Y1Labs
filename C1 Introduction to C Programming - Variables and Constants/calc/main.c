#include <stdio.h>

#define NEXT(i, j) ((i) + (j) - (i) % (j))

int main(void)
{
	int i[3] = {365, 12258, 996}, j[3] = {7, 23, 4}, t;

	for (t = 0; t < 3; t++)
		printf("%d,\t%d\t->\t%d\n", i[t], j[t], NEXT(i[t], j[t]));

	puts("Input i and j sparated by space");
	scanf("%d %d", &i[0], &j[0]);
	printf("The next multiple is %d\n", NEXT(i[0], j[0]));

	return 0;
}
