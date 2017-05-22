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
	//ADD FILE:
	FILE *fp;
	char targetFile[512];
	fprintf(stdout, " Input file LOCATION:\t");//CHANGE TO something from io.c
	fgets(targetFile, 512, stdin);//CHANGE TO io.c
	fprintf(stdout, " Inputted:\t %s\n", targetFile);
	if ((fp = fopen(targetFile,"r"))){
		fprintf(stdout, "%s is a valid file...\n",targetFile);
	}
	else{
		fprintf(stdout, "%s is an invalid file...\n",targetFile);
	}
	return;
	
	return 0;
}
