void sort(const int size, const float *input, float *output)
{
	int swap, i;
	float tmp;

	// First, copy input to output
	for (i = 0; i < size; i++)
		*(output + i) = *(input + i);

	// Sort output
	do {
		swap = 0;
		for (i = 0; i < size - 1; i++)
			if (*(output + i) > *(output + i + 1)) {
				tmp = *(output + i);
				*(output + i) = *(output + i + 1);
				*(output + i + 1) = tmp;
				swap++;
			}
	} while (swap);
}

// Alternative method
void bSort(const int size, float *output)
{
	int swap, i;
	float tmp;
	for (i = 0; i < size - 1; i++)
		if (*(output + i) > *(output + i + 1)) {
			tmp = *(output + i);
			*(output + i) = *(output + i + 1);
			*(output + i + 1) = tmp;
			swap++;
		}
	if (swap)
		bSort(size, output);
}

void bubbleSort(const int size, const float *input, float *output)
{
	int i;

	// First, copy input to output
	for (i = 0; i < size; i++)
		*(output + i) = *(input + i);

	// Sort output
	bSort(size, output);
}
