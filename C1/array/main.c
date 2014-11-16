#include <stdio.h>

int main(void)
{
	int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i;

	printf("There are %d days in month 1\n", monthDays[0]);
	printf("There are %d days in month 2\n", monthDays[1]);
	printf("There are %d days in month 3\n", monthDays[2]);
	printf("There are %d days in month 4\n", monthDays[3]);
	printf("There are %d days in month 5\n", monthDays[4]);
	printf("There are %d days in month 6\n", monthDays[5]);
	printf("There are %d days in month 7\n", monthDays[6]);
	printf("There are %d days in month 8\n", monthDays[7]);
	printf("There are %d days in month 9\n", monthDays[8]);
	printf("There are %d days in month 10\n", monthDays[9]);
	printf("There are %d days in month 11\n", monthDays[10]);
	printf("There are %d days in month 12\n", monthDays[11]);

	//for (i = 0; i < 12; i++)
	//	printf("There are %d days in month %d\n", monthDays[i], i + 1);

	return 0;
}

