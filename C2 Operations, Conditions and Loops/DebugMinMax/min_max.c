#include <stdio.h>

#define SIZE 10

int main(void) {
    double data[SIZE] = {1,2,3,4,5,1,2,3,4,5};
    double max = data[0], min = data[0];
    int i;

    for (i=0; i<SIZE; i+=1)
    {
		if (max < data[i]){
			max = data[i];
    	}
    	if (min > data[i]){
    		min = data[i];
		}
    }

    printf("max: %.2f, min: %.2f\n", max, min);

    return 0;
}

