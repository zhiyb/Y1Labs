#include <stdio.h>

int main(void) {
	int integer_number;
	float floating_point_number;
	double double_precision_number; 
	char character;
	const int myid = 426424533;
	const double pi = 3.14159265358979;
	
	printf("Please input the value of integer:\n");
	scanf("%d", &integer_number);
 
	floating_point_number = 323.44; 
	double_precision_number = 8.44e+4;
	character = 'e';
	
	printf("<Input> integer_number: %d\n", integer_number); 
	printf("floating_point_number: %f\n", floating_point_number); 
	printf("double_precision_number: %f\n", double_precision_number);
	printf("double_precision_number: %g\n", double_precision_number);
	/* this is an example of casting */
	printf("double_precision_number as int: %d\n", (int)double_precision_number);
	printf("character: %c\n", character); 
	printf("<Const> My ID: %d\n", myid);
	printf("<Const> Value of PI: %lf\n", pi);

	return 0;
}
