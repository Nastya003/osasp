#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Parameters: name of file, number of strings\n");
		return 1;
	}
	char *endptr;
	int N = strtol(argv[2], &endptr, 10);
	if ((argv[2] == endptr) || (endptr - argv[2] < strlen(argv[2]))) {
		fprintf(stderr, "Second parameter must be a number\n");
		return 1;
	}
	if (N < 0) {
		printf("Invalid number of strings\n");
		return 1;
	}
	FILE *file = fopen(argv[1],"r");
	if (!file) {
		perror("File open");
		return 1;
	}
	char smb;
	int LineCount = 0;
	while((smb = fgetc(file)) != EOF) {
		if (smb == '\n') {
			LineCount++;
		}
		if (LineCount == N && N != 0) {
			getc(stdin);
			LineCount = 0;
		}
		putc(smb, stdout);
	}
	if (fclose(file)) {
		perror("Close file");
		return 1;
	} else return 0;
}
