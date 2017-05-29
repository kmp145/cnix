#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>//FOR inet_addr()
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include "networking.h"
#include "logger.h"

void sendFile(int peerSockfd, char fileName[120]){


	
	int fileSize = 0, fd, line, remainingData, dataSent = 0;
	char logmsg[50];
	ssize_t len;
	off_t offset;
	struct stat fs;
	
	if((fd = open(fileName, O_RDONLY))){
		fstat(fd, &fs);
		//sprintf(fileSize, "%d", fs.st_size);
		fileSize = fs.st_size;
		remainingData = fileSize; 
		fprintf(stdout, "Filesize of \"%s\": %d\n", fileName, fileSize);
		line = send(peerSockfd, &fileSize, sizeof(fileSize), 0);

		while (((dataSent = sendfile(peerSockfd, fd, &offset, BUFSIZ)) > 0) && (remainingData > 0)){
			fprintf(stdout, "Data sent:\t%d\n", dataSent);
			remainingData -= dataSent;
		
		}
		strcpy(logmsg, fileName);
		strcat(logmsg, " was sent to a friend");
		logThis(logmsg, "log.txt");
		
	}//IF FILE exists
}



void recieveFile(int sockfd, char fileName[120]){
	
	
	int line, fileSize, remainingData = 0;
	char buffer[255];
	ssize_t len;
	FILE *fp;
	fp = fopen(fileName, "w");

	read(sockfd, buffer, BUFSIZ);
	//fprintf(stdout, "%s\n", buffer);
	fileSize = atoi(buffer);
	//fileSize = 21;
	fprintf(stdout, "Filesize recieved:\t%d\n", fileSize);
	remainingData = fileSize;

	while (((len = recv(sockfd, buffer, BUFSIZ, 0)) > 0) && (remainingData > 0)){

		remainingData -= len;
		fputs(buffer, fp);
        }
	fclose(fp);
	close(sockfd);
	logThis("File was recieved from friend\n", "log.txt");//Change to use variables

}


int createSocket(int port){
	 
	fprintf(stdout,"in createSocket()\n");

	int sockfd;// port = 7777;//Change so port is passed

	struct sockaddr_in serverAddress;
	
	memset(&serverAddress, 0, sizeof(serverAddress));//intialise serv_addr to 0
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);//set port number

	sockfd = socket(AF_INET, SOCK_STREAM, 0);//create socket
	bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	fprintf(stdout,"Socket successfully created on port %d\n", port);
	return sockfd;
}

void listenForConnection(int sockfd){
	
	fprintf(stdout,"listening...\n");
	
	int newsockfd, line;
	socklen_t clientlen;
	char buffer[256];
	struct sockaddr_in clientAddress;
	
	
	listen(sockfd,5);
	clientlen = sizeof(clientAddress);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientlen);//update
	//fprintf(stdout,"New connection on:\t%s",clientAddress.sin_addr);
	memset(buffer,0,256);
	sendFile(newsockfd, "testTransfer.txt");
	line = 2;//DEBUG
	printf("%d\n",line);
	//line = write(newsockfd, "Connected",10);
	//line = read( newsockfd, buffer, 255);
	/*if (line<0){//error reading from socket
		fprintf(stdout,"Error connecting...\n");
	}
	else{
		fprintf(stdout,"You entered:\t%s\n", buffer);
		line = write(newsockfd, "Returning message",18);
	}*/
	return;
}





void connectToFriend(int sockfd, char * targetIP, int targetPort){//still needs updating

	int line;
	char buffer[256];
	
	//sockfd = createSocket();
	struct sockaddr_in targetAddress;
	memset(&targetAddress,0,sizeof(targetAddress));
	targetAddress.sin_family = AF_INET;
	targetAddress.sin_addr.s_addr = inet_addr(targetIP);
	targetAddress.sin_port = htons(targetPort);
	if(connect(sockfd, (struct sockaddr*)&targetAddress, sizeof(targetAddress)) < 0){
		fprintf(stdout,"Error connecting...\n");
	}
	else{
		line = read(sockfd, buffer, 255);
		if(line <0){
			fprintf(stdout,"error reading");
		}
		fprintf(stdout,"%s\n",buffer);
		fgets(buffer,255,stdin);
		line = write(sockfd, buffer, strlen(buffer));
		line = read(sockfd, buffer, 255);
		fprintf(stdout,"%s\n",buffer);
	}
	
	
	
}

void listenHandler(int port){
	int sockfd;
	sockfd = createSocket(port);
	listenForConnection(sockfd);
	return;
}

void downloadHandler(int port, char IPAddress[17], int tarPort){
	int sockfd;
	sockfd = createSocket(port);
	connectToFriend(sockfd, IPAddress, tarPort);
	return;
}
/*

int main(){

	
	bind(address with socket)
	listen (for incoming connections on socket)
	accept(accept connection)
	
	sendFile(5, "testTransfer.txt");
	fprintf(stdout,"1. server\n2. Client\n");
	//fgets()
	int sockfd;
	sockfd = createSocket();//change to pass port
	//sendFile(sockfd, "testTransfer.txt");
	//connectToFriend(sockfd, "127.0.0.1", 7777);//connecting to friend
	//loadFriends();
	listenForConnection(sockfd);
	listen(sockfd,5);
	
	clientlen = sizeof(clientAddress);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientlen);
	
	return 0;
}*/
