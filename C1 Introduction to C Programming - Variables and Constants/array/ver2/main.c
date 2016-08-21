#include <stdio.h>

int main(void)
{
	int monthDays[12];
	int whichmonth;
	const int BIG = 31, SMALL = 30, SPECIAL = 28;

	monthDays[0] = BIG;
	monthDays[1] = SMALL;
	monthDays[2] = SPECIAL;
	monthDays[3] = SMALL;
	monthDays[4] = BIG;
	monthDays[5] = SMALL;
	monthDays[6] = BIG;
	monthDays[7] = BIG;
	monthDays[8] = SMALL;
	monthDays[9] = BIG;
	monthDays[10] = SMALL;
	monthDays[11] = BIG;

	puts("Which month to ouput?");
	scanf("%d", &whichmonth);
	printf("There are %d days in month %d\n", monthDays[whichmonth - 1], whichmonth);

	//for (i = 0; i < 12; i++)
	//	printf("There are %d days in month %d\n", monthDays[i], i + 1);

	return 0;
}

