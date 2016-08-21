#include <stdio.h>

int main(void)
{
	char i, c;
	FILE *fp;
	if ((fp = fopen("newfile.txt", "w")) == NULL) {
		fputs("Cannot open file!\n", stderr);
		return 1;
	}
	for (i = 0; i < 25; i++) {
		for (c = 'a'; c <= 'z'; c++)
			fputc(c, fp);
		fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}
