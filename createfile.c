#include "fcntl.h"
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {

	int fd1, fd2;
	int len, res;
	char *str;

	if(argc != 4) {
		printf(1, "Not enough Arguments\n");
		exit();
	}

	/*
	 * Opening the two files - one to read from and the other to be created and written to
	 */
	fd1 = open(argv[1], O_CREATE | O_WRONLY);
	if(fd1 == -1) {
		printf(1, "File cannot be created\n");
		exit();
	}

	fd2 = open(argv[2], O_RDONLY);
	if(fd2 == -1) {
		printf(1, "File for reading is not present\n");
		exit();
	}

	//the number of bytes to be written in the newly created file
	len = atoi(argv[3]);

	//reading from the already existing file, 'len' number of bytes
	str = (char *)malloc(sizeof(char)*(len+1));
	res = read(fd2, str, len);
	str[res] = '\0';

	//writing into the newly created file
	write(fd1, str, len);
	printf(1, "File of the speicified length was created\n");

	close(fd1);
	close(fd2);
	exit();
}
