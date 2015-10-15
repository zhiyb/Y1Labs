void sort(const int size, const float *input, float *output)
{
	int swap, i;

	// First, copy input buffer to output buffer
	for (i = 0; i < size; i++)
		*(output + i) = *(input + i);

	// Sort output buffer
	do {
		swap = 0;
		for (i = 0; i < size - 1; i++)
			if (*(output + i) > *(output + i + 1)) {
				float tmp = *(output + i);
				*(output + i) = *(output + i + 1);
				*(output + i + 1) = tmp;
				swap = 1;
			}
	} while (swap);
}

// Alternative method (recursive)
static void bSort(const int size, float *output)
{
	int swap, i;
	for (i = 0; i < size - 1; i++)
		if (*(output + i) > *(output + i + 1)) {
			float tmp = *(output + i);
			*(output + i) = *(output + i + 1);
			*(output + i + 1) = tmp;
			swap = 1;
		}
	if (swap)
		bSort(size, output);
}

void bubbleSort(const int size, const float *input, float *output)
{
	int i;

	// First, copy input buffer to output buffer
	for (i = 0; i < size; i++)
		*(output + i) = *(input + i);

	// Sort output buffer
	bSort(size, output);
}
