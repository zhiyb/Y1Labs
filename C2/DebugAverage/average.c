#include <stdio.h>

#define SIZE 10

int main(void) {
    double avg = 0;
    double data[SIZE] = {1,2,3,4,5,1,2,3,4,5};
    int i;

    for (i=0; i<SIZE; i+=1)
    {
	printf("<Debug> avg: %g, i: %d, data[i]: %g\n", avg, i, data[i]);
        avg += data[i];
    }
    avg = avg / SIZE;

    printf("average: %.2f\n", avg);

    return 0;
}

