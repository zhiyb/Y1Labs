#include <stdio.h>

void sort(const int size, const float input[], float output[])
{
	int j = 0 /*Temporary variable*/, swapped = 0 /*Is swap finished?*/;
	float tmp;		//Temporary variable for swap values

	//First, copy input to output
	for (j = 0; j < size; j++)
		output[j] = input[j];

	//Sort output
	while (swapped == 0) {	//Continue sort until no more swap available
		swapped = 1;	//Set finished sign TRUE (will change if swap)
		//Compare between [j] and [j + 1],
		//so the range is 0 <= j < (size - 1)
		for (j = 0; j < (size - 1); j++)
			//If need to swap
			if (output[j] > output[j + 1]) {
				//Set finished sign to FALSE
				swapped = 0;
				//Swap [j] and [j + 1]
				tmp = output[j];
				output[j] = output[j + 1];
				output[j + 1] = tmp;
			}
	}
}
