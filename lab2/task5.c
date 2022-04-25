#include <stdio.h>
#include <sys/stat.h>
int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Parameters: name of src file, name of dest file\n");
		return 1;
	}
	FILE *f1 = fopen(argv[1], "r");
	if (!f1) {
		perror("Src file open");
		return 1;
	}
	FILE *f2 = fopen(argv[2], "w");
	if (!f2) {
		perror("Dest file open");
		fclose(f1);
		return 1;
	}
	char smb;
	while ((smb = fgetc(f1)) != EOF) {
		fputc(smb,f2);
	}
	struct stat buf;
	stat(argv[1], &buf);
	chmod (argv[2], buf.st_mode);
	if (fclose(f1)) {
		perror("Close src file");
		fclose(f2);
		return 1;
	}
	if (fclose(f2)) {
		perror("Close dest file");
		return 1;
	}
	return 0;
}
