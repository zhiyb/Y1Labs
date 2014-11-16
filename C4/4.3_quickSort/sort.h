#ifndef _SORT_H
#define _SORT_H

#include <stdlib.h>

void sort(void *base, size_t nmemb, size_t size, int(*compar)(const void *, const void *));

#endif
