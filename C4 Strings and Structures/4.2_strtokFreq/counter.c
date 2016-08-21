#include <stdio.h>
#include <string.h>
#include "strsize.h"
#include "counter.h"

#define DELIM " ;().,\n"

void count(char *str, struct counter *token)
{
	while (token->count != 0) {
		if (strcmp(str, token->word) == 0) {
			 token->count++;
			 return;
		}
		token++;
	}
	token->count++;
	strcpy(token->word, str);
	(token + 1)->count = 0;
}

void getTokens(char *text, struct counter *token)
{
	char *str;
	token->count = 0;
	count(strtok(text, DELIM), token);
	while ((str = strtok(NULL, DELIM)) != NULL)
		count(str, token);
}

void sortTokens(struct counter *token)
{
	int swap, i;
	struct counter tmp;

	//Sort tokens
	do {
		swap = 0;
		for (i = 0; (token + i + 1)->count != 0; i++)
			if ((token + i)->count > (token + i + 1)->count) {
				tmp.count = (token + i)->count;
				strcpy(tmp.word, (token + i)->word);

				(token + i)->count = (token + i + 1)->count;
				strcpy((token + i)->word, (token + i + 1)->word);

				(token + i + 1)->count = tmp.count;
				strcpy((token + i + 1)->word, tmp.word);

				swap++;
			}
	} while (swap);
}

void printTokens(const struct counter *token)
{
	while (token->count != 0) {
		printf("%*s | Appeared %d times\n", STRSIZE, token->word, token->count);
		token++;
	}
}
