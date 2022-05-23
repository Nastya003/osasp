#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <dirent.h>

int main (int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Invalid number of paremeters: N(array), n(Talor count)\n");
		return 1;
	}
	int N = strol(argv[1], NULL, 10);
	if (N <= 0) {
		fprintf(stderr,"Array length cant be less then 0\n");
		return 1;
	}
	int n = strol(argv[2], NULL, 10);
        if (n <= 0) { 
                fprintf(stderr,"2nd parameter cant be less then 0\n");
                return 1;
        }
	pid_t pid;
	FILE *file;

	for (int i = 0; i < N; i++) {

		for (int j = 0; j < n; j++) {
			pid = fork();
			switch(pid) {
				case 0:
				
				case -1:
					fprintf(stderr, "Child proc error\n");
					exit(1);
				default:
			}
		}
	}

}
