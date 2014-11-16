#include <stdio.h>

/* this is one way to define a constant in C */
#define ARRAY_SIZE 10

void fillArray(int *array, const int size);
void showArray(const int *array, const int size);

int main(void)
{
	int myArray[ARRAY_SIZE];

	fillArray(myArray, ARRAY_SIZE);
	showArray(myArray, ARRAY_SIZE);

	return 0;
}

/* 
    This function changes the array content,
    this is possible using a pointer.
*/
void fillArray(int *array, const int size)
{
	int i;

	printf("Filling an array..");

	for (i = 0; i < size; i++) {
		array[i] = i * 10;
	}

	printf("\ndone.\n");

	return;
}

/* 
    This function does not modify the array content,
    so we declare the first argument as "const",
    even though it is still a pointer..
*/
void showArray(const int *array, const int size)
{
	int j;

	printf("\n");
	printf("Showing an array:\n");

	for (j = 0; j < size; j++) {
		printf("element %d: %d\n", j, array[j]);
		/* 
		   because we declared the first argument
		   as const the following would cause a compiler error: try!
		   array[j] = 0; 
		 */
	}

	return;
}
