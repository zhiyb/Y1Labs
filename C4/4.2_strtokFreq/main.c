#include <stdio.h>
#include <string.h>
#include "strsize.h"
#include "counter.h"

int main(void)
{
	char text[] = "C (pronounced like the letter C) is a general-purpose computer programming language developed between 1969 and 1973 by Dennis Ritchie at the Bell Telephone Laboratories for use with the Unix operating system. Although C was designed for implementing system software, it is also widely used for developing portable application software. C is one of the most widely used programming languages of all time and there are very few computer architectures for which a C compiler does not exist. C has greatly influenced many other popular programming languages, most notably C++, which began as an extension to C.";
	struct counter token[128];

	puts(text);
	putchar('\n');

	getTokens(text, token);
	sortTokens(token);
	printTokens(token);

	return 0;
}
