#include "fcntl.h"
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
	int fd, offset;
	int len, res;
	char *str;

	if(argc != 5) {
		printf(1, "The number of arguments are not correct\n");
		exit();
	}
		
	//opening the given file
	fd = open(argv[1], O_RDWR);
	if(fd == -1) {
		printf(1, "File not found\n");
		exit();
	}

	//seek to the given location
	offset = atoi(argv[2]);
	lseek(fd, offset, SEEK_SET);

	//read the required bytes
	len = atoi(argv[3]);
	str = (char *)malloc(sizeof(char) * (len+1));
	res = read(fd, str, len);
	str[res] = '\0';

	//compare with the given string
	if(strcmp(argv[4], str) == 0) {
		printf(1, "The Two strings are the same. Hence lseek works\n");
	}
	else {
		printf(1, "The two strings are different\n");
	}

	close(fd);
	free(str);
	exit();
}
