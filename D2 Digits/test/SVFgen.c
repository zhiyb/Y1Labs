/*
 * SVFgen.c
 *
 *  Created on: Jan 17, 2013
 *      Author: Steve Gunn & Er Khor
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int input_bit[32] =   { 183, 177, 168, 153, 150, 147, 141, 3, 135, 120, -1, 108, 105, 102, 96, 0, 93, 87, 84, 81, 72, 69, 54, 189, 48, 42, -1, 36, 27, 12, 6, 186 };
const int control_bit[32] = { 184, 178, 169, 154, 151, 148, 142, 4, 136, 121, -1, 109, 106, 103, 97, 1, 94, 88, 85, 82, 73, 70, 55, 190, 49, 43, -1, 37, 28, 13, 7, 187 };
const int output_bit[32] =  { 185, 179, 170, 155, 152, 149, 143, 5, 137, 122, -1, 110, 107, 104, 98, 2, 95, 89, 86, 83, 74, 71, 56, 191, 50, 44, -1, 38, 29, 14, 8, 188 };

char hex[49];

#define NO_TESTS 18
const char test_vector[NO_TESTS][32] = {
// Port 2.2, 4.2, *.7 are not usable, testing (1 - 3) & (2 - 4)
// Port  1.0  1.1  1.2  1.3  1.4  1.5  1.6  1.7    2.0  2.1  2.2  2.3  2.4  2.5  2.6  2.7    3.0  3.1  3.2  3.3  3.4  3.5  3.6  3.7    4.0  4.1  4.2  4.3  4.4  4.5  4.6  4.7
	{'0', '0', '0', '0', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'L', 'L', 'L', 'L', 'L', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
	{'1', '1', '1', '1', '1', '1', '1', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'H', 'H', 'H', 'H', 'H', 'H', 'H', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
	{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   '0', '0', 'X', '0', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'X', 'L', 'L', 'L', 'L', 'X'},
	{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   '1', '1', 'X', '1', '1', '1', '1', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'H', 'H', 'X', 'H', 'H', 'H', 'H', 'X'},

	{'1', '0', '0', '0', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'H', 'L', 'L', 'L', 'L', 'L', 'L', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
	{'0', '1', '0', '0', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'H', 'L', 'L', 'L', 'L', 'L', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
	{'0', '0', '1', '0', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'H', 'L', 'L', 'L', 'L', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
	{'0', '0', '0', '1', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'L', 'H', 'L', 'L', 'L', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
	{'0', '0', '0', '0', '1', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'L', 'L', 'H', 'L', 'L', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
	{'0', '0', '0', '0', '0', '1', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'L', 'L', 'L', 'H', 'L', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
	{'0', '0', '0', '0', '0', '0', '1', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'L', 'L', 'L', 'L', 'H', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},

	{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   '1', '0', 'X', '0', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'H', 'L', 'X', 'L', 'L', 'L', 'L', 'X'},
	{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   '0', '1', 'X', '0', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'H', 'X', 'L', 'L', 'L', 'L', 'X'},
	{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   '0', '0', 'X', '0', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'X', 'L', 'L', 'L', 'L', 'X'},
	{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   '0', '0', 'X', '1', '0', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'X', 'H', 'L', 'L', 'L', 'X'},
	{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   '0', '0', 'X', '0', '1', '0', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'X', 'L', 'H', 'L', 'L', 'X'},
	{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   '0', '0', 'X', '0', '0', '1', '0', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'X', 'L', 'L', 'H', 'L', 'X'},
	{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   '0', '0', 'X', '0', '0', '0', '1', 'X',   'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',   'L', 'L', 'X', 'L', 'L', 'L', 'H', 'X'},
};

char *bits_to_hex(int *bits)
{
	/* Passes 192 bit int array and converts bit values to a 48 element char array in hex format */
	/* Bits are reversed to ensure MSB appears at the left of the string.                        */
	int i, j, b = 191;
	int h;
	for (i = 0; i < 48; i++) {
		h = 0;
		for (j = 3; j >= 0; j--)
			if (bits[b--] == 1)
				h += pow(2, j);
		sprintf(&hex[i], "%X", h);
	}
	return hex;
}

void header()
{
	printf("// Test file for EPM3064A\n");
	printf("// =============== Init Sequence\n");
	printf("ENDIR IDLE;\n");
	printf("ENDDR IDLE;\n");
	printf("STATE RESET;\n");
	printf("STATE IDLE;\n");
	printf("// =============== Main Test\n");
	printf("SIR 10 TDI(055) SMASK(3ff);    // SAMPLE/PRELOAD\n");
	printf("SDR 192 \n");
}

void footer()
{
	printf("// =============== End of Test\n");
	printf("STATE RESET;\n");
	printf("// =============== EOF\n");
}

int main(void)
{
	int t, b;

	header();
	for (t = 0; t < NO_TESTS; t++) {
		// Initialise BSR bits to zero
		int bsr_tdi[192] = { 0 };
		int bsr_tdo[192] = { 0 };
		int bsr_mask[192] = { 0 };

		for (b = 0; b < 32; b++)
			if (control_bit[b] != -1)	// Make sure we ignore the two grounded pins
				switch (test_vector[t][b]) {
					// Configure the output pins
				case '0':
					bsr_tdi[control_bit[b]] = 1;
					break;
				case '1':
					bsr_tdi[control_bit[b]] = 1;
					bsr_tdi[output_bit[b]] = 1;
					break;
					// Configure the input tests
				case 'L':
					bsr_mask[input_bit[b]] = 1;
					break;
				case 'H':
					bsr_mask[input_bit[b]] = 1;
					bsr_tdo[input_bit[b]] = 1;
					break;
				case 'X':
					break;
				default:
					fprintf(stderr, "Error: Unknown character '%c' in test vector %d\n", test_vector[t][b], t);
				}

		printf("      ! Test Vector %d\n", t + 1);
		printf("        TDI(%s);\n", bits_to_hex(bsr_tdi));
		if (t == 0)
			printf("SIR 10 TDI(000) SMASK(3ff);    // EXTEST\n");
		printf("SDR 192 TDO(%s)\n", bits_to_hex(bsr_tdo));
		printf("       MASK(%s)%c\n", bits_to_hex(bsr_mask), (t == NO_TESTS - 1) ? ';' : ' ');
	}
	footer();

	return 0;
}
