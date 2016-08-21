#include <stdio.h>

int main(void) {
	int integer_number;
	float floating_point_number;
	double double_precision_number; 
	char character;
	
	integer_number = 10; 
	floating_point_number = 323.44; 
	double_precision_number = 8.44e+4;
	character = 'e';
	
	printf("integer_number: %d\n", integer_number); 
	printf("floating_point_number: %f\n", floating_point_number); 
	printf("double_precision_number: %f\n", double_precision_number);
	printf("double_precision_number: %g\n", double_precision_number);
	/* this is an example of casting */
	printf("double_precision_number as int: %d\n", (int)double_precision_number);
	printf("character: %c\n", character); 

	return 0;
}
