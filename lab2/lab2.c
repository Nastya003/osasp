#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


long double SizeBloks = 0, SizeAll = 0;

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
	char path[5000];
	if (strcmp(dirname,"/")) strcat(dirname, "/");
	while((d = readdir(dir))) {
		if (!strcmp(d->d_name,".") || !strcmp(d->d_name,"..")) continue;
		strcpy(path, dirname);
		strcat(path, d->d_name);
		lstat(path, &buf);
		if (S_ISDIR(buf.st_mode)) {
			dirsize(path);
		} else
		if (!S_ISDIR(buf.st_mode)) {
			sum += buf.st_size;
			disksum += (buf.st_blocks * 512);
		}
	}
	printf("%s Size: %ld Disk size: %ld\n",dirname, sum, disksum);
	SizeBloks += disksum;
	SizeAll += sum;
	if (closedir(dir)) {
		perror("Close directory");
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Parameters: name of directory\n");
		return 1;
	}
	int Disk = 0;
	dirsize(argv[1]);
	printf("Disk usage: %Lf\n", (SizeAll/SizeBloks)*100);
	return 0;
}
