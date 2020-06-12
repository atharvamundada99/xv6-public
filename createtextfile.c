#include "fcntl.h"
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {

	int fd;
	int len;

	if(argc != 4) {
		printf(1, "Not enough Arguments\n");
		exit();
	}

	/*
	 * Creating the file
	 */
	fd = open(argv[1], O_CREATE | O_WRONLY);
	if(fd == -1) {
		printf(1, "File cannot be created\n");
		exit();
	}

	//the number of bytes to be written in the newly created file
	len = atoi(argv[3]);
	if(len > strlen(argv[2])) {
		printf(1, "The size of the string to be written is small\n");
		exit();
	}

	//writing into the newly created file from the string provided
	write(fd, argv[2], len);
	printf(1, "File of the speicified length was created\n");

	close(fd);
	exit();
}
