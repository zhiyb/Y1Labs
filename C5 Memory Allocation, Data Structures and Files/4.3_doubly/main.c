#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "list.h"

#define DELIM " '\";().,\n"

int main(int argc, char *argv[])
{
	char *f = malloc(sizeof(char)), *str;
	int ch;
	FILE *fp;
	list *head;
	if (argc != 2) {
		fputs("Need 1 argument (file path)\n", stderr);
		return 1;
	}
	if ((fp = fopen(argv[1], "r")) == NULL) {
		fputs("Open file failed", stderr);
		return 1;
	}
	*f = '\0';
	while ((ch = fgetc(fp)) != EOF) {
		if ((f = realloc(f, sizeof(char) * (strlen(f) + 2))) == NULL) {
			fputs("realloc() failed!", stderr);
			return 1;
		}
		*(f + strlen(f) + 1) = '\0';
		*(f + strlen(f)) = (char)ch;
	}
	fclose(fp);

	head = list_create();
	list_insert_sorted(head, strtok(f, DELIM), 1);
	while ((str = strtok(NULL, DELIM)) != NULL)
		if (list_insert_sorted(head, str, 1) == 1)
			head->current->freq++;
	list_print(head);
	free(f);
	return 0;
}
