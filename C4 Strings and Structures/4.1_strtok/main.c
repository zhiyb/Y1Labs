#include <stdio.h>
#include <string.h>

#define DELIM " ;().,\n"
#define STRSIZE 32

int getTokens(char *text, char (*token)[STRSIZE], int size)
{
	char *str;
	int i = 1;
	strcpy(*token, strtok(text, DELIM));
	while ((str = strtok(NULL, DELIM)) != NULL && i < size)
		strcpy(*(token + i++), str);
	**(token + i) = '\0';
	return i;
}

int main(void)
{
	char text[] = "C (pronounced like the letter C) is a general-purpose computer programming language developed between 1969 and 1973 by Dennis Ritchie at the Bell Telephone Laboratories for use with the Unix operating system. Although C was designed for implementing system software, it is also widely used for developing portable application software. C is one of the most widely used programming languages of all time and there are very few computer architectures for which a C compiler does not exist. C has greatly influenced many other popular programming languages, most notably C++, which began as an extension to C.";
	char token[128][STRSIZE];
	int i;
	puts(text);
	putchar('\n');
	printf("Got %d words\n", getTokens(text, token, 128));
	putchar('\n');
	for (i = 0; i < 128 && token[i][0] != '\0'; i++)
		printf("%s%s", i == 0 ? "" : " | ", token[i]);
	putchar('\n');
	return 0;
}
