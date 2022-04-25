#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

int dirsize(char *dirname) {
	DIR *dir;
	if (!(dir = opendir(dirname))) {
		perror("Open directory");
		return 1;
	}
	struct dirent *d;
	struct stat buf;
	long int sum = 0;
	long int disksum = 0;
	while((d = readdir(dir))) {
		if (strcmp(d->d_name,".") && strcmp(d->d_name,"..")) {
			strcpy(file, dirname);
			strcat(file, "/");
 			strcat(file, d->d_name);
		}
		stat(dirname, &buf);
		if (S_ISDIR(buf.st_mode)) {
			dirsize (dirname);
		} else
		if (S_ISREG(buf.st_mode)) {
			sum += buf.st_size;
			disksum += (buf.st_bloks * 512);
		}
	}
	printf("%s %ld %ld\n",dirname, sum, disksum);


}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Parameters: name of directory");
		return 1;
	}
	
}
