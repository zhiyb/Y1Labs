#ifndef _MATRIX_H
#define _MATRIX_H

void conv2Matrix(const int size, const int *a, int (*ma)[size]);
void conv2Array(const int size, int (*m)[size], int *a);
void printMatrix(const int size, int (*m)[size]);
void hFlipMatrix(const int size, int (*ma)[size], int (*mb)[size]);
void vFlipMatrix(const int size, int (*ma)[size], int (*mb)[size]);

#endif
