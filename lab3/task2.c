#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>

void PrintInfo() {
	struct timeval curtime;
	printf("PID %d Parent PID %d ", getpid(), getppid());
	if (gettimeofday(&curtime, NULL)) {
		fprintf(stderr, "Time output\n");
	} else {
		int msec = curtime.tv_usec / 1000;
		int sec = curtime.tv_sec % 60;
		int min = (curtime.tv_sec / 60) % 60;
		int hours = (curtime.tv_sec / 3600 + 3) % 24;

		printf("Time is: %02d:%02d:%02d:%03d\n\n", hours, min, sec, msec);
	}
}
int main() {
	printf("Main PID:\n");
	PrintInfo();

	printf("Cild PID:\n");
	for (int i=0; i<2; i++) {
		pid_t pid = fork();
		switch(pid) {
			case -1:
				fprintf(stderr, "child process error\n");
				break;
			case 0:
				PrintInfo();
				exit(0);
			default:
				break;
		}
	}
	if(system("ps -x") == -1) {
		perror("system");
	}
	while(1) {
		if(wait(NULL) == -1) {
			fprintf(stderr, "Child proc closing\n");
			return 1;
		}
	}
	return 0;
}
