#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

FILE *newfile(char *path, int index)
{
	char opath[strlen(path) + 4];
	FILE *out;
	if (opath == NULL) {
		fputs("Not enough memory\n", stderr);
		exit(1);
	}
	sprintf(opath, "%s.%02d", path, index);
	out = fopen(opath, "w");
	if (out == NULL) {
		fputs("Cannot open output file\n", stderr);
		exit(1);
	}
	return out;
}

void separate(char *path)
{
	char ch;
	int index = 1, new = 0;
	FILE *in = fopen(path, "r"), *out;
	if (in == NULL) {
		fputs("Cannot open input file\n", stderr);
		exit(1);
	}
	rewind(in);
	out = newfile(path, index++);
	while ((ch = fgetc(in)) != EOF) {
		if (ch == '\n') {
			new++;
			if (new > 1) {
				fclose(out);
				out = newfile(path, index++);
				continue;
			}
		} else
			new = 0;
		fputc(ch, out);
	}
	fclose(out);
	fclose(in);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fputs("Need 1 argument (file path)\n", stderr);
		return 1;
	}
	separate(argv[1]);
	return 0;
}
