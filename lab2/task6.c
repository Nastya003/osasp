#include <stdio.h>
#include <dirent.h>

int dirlist(const char *dirname);

int main(int argc, char argv[]) {
	printf("Current directory:\n");
	dirlist("./");
	printf("\n");
	printf("Root directory:\n");
	dirlist("/");
}

int dirlist(const char *dirname) {
	DIR *dir;
	if (!(dir = opendir(dirname))) {
		perror("Open directory");
		return 1;
	}
	struct dirent *d;
	while((d = readdir(dir))) {
		printf("%s\n",d->d_name);
	}
	if (closedir(dir)) {
		perror("Close directory");
		return 1;
	}
	return 0;
}
