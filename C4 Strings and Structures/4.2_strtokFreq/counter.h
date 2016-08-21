#ifndef _COUNTER_H
#define _COUNTER_H

#include "strsize.h"

struct counter {
	char word[STRSIZE];
	int count;
};

void count(char *str, struct counter *token);
void getTokens(char *text, struct counter *token);
void sortTokens(struct counter *token);
void printTokens(const struct counter *token);

#endif
