#include <stdio.h>

int main (int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Parametrs: name of output file \n");
		return 1;
	} else {
		FILE *file;
		if (file = fopen(argv[1],"w")){
			char smb;
			while (smb != '-') {
				if((smb = getc(stdin)) != EOF) {
					if (smb != '-') putc(smb, file);
				} else {
					perror("Read symbol");
					return 1;
				}
			}
			if (fclose(file)){
				perror("Close file");
				return 1;
			} else return 0;
		} else {
			perror("Open file");
			return 1;
		}
	}
}
