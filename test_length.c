#include "fcntl.h"
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
	int fd1, fd2;
	int size;
	int chunksize;
	int res, i;
	char *str;

	if(argc != 2) {
		printf(1, "The number of arguments are not correct\n");
		exit();
	}

	/*
	 * Opening the two files -> one for reading and other for writing
	 */
	fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1) {
		printf(1, "File not found\n");
		exit();
	}

	fd2 = open("copy.txt", O_CREATE | O_WRONLY);
	if(fd2 == -1) {
		printf(1, "Copy file cannot be created\n");
		exit();
	}

	//finding the size of the original file
	size = lseek(fd1, 0, SEEK_END);
	printf(2, "The size of the original file is %d\n", size);

	//Making the copy file of the required size
	str = (char *)malloc(sizeof(char) * size);
	memset(str, 0, size);
	write(fd2, str, size);

	//dividing the original file size into 10 chunks
	if(size%10 == 0)
		chunksize = size / 10;
	else
		chunksize = (size / 10) + 1;

	//writing the chunks in the copy file in the order 2, 1, 4, 3, 6, 5, 8, 7, 10, 9
	str = (char *)malloc(sizeof(char)*(chunksize+1));
	i = 2;
	while(i <= 10) {
		lseek(fd1, (i-1)*chunksize, SEEK_SET);
		res = read(fd1, str, chunksize);
		str[res] = '\0';

		lseek(fd2, (i-1)*chunksize, SEEK_SET);
		write(fd2, str, res);

		if(i%2 == 0)
			i--;
		else
			i+=3;
	}
	
	close(fd1);
	close(fd2);
	exit();
}
