#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

int main(){
	int fd;
	char fileSize[256];
	struct stat fs;


	fd = open("testTransfer.txt", O_RDONLY);
	fstat(fd, &fs);

	fprintf(stdout,"%d\n",fs.st_size);
	sprintf(fileSize, "%d", fs.st_size);
	fprintf(stdout, "%s\n", fileSize);
	
	return 0;
}
