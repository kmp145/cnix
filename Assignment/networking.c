#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>//FOR inet_addr()
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void sendFile(int peerSockfd, char fileName[120]){//should be called from listenForConnection()
	int line, convertedSize, dataSent = 0, offset = 0, remainingData, fd;
	ssize_t len;
	char fileSize[512], buffer[512];
	FILE *fp;
	struct stat fs;


	fd = open("testTransfer.txt", O_RDONLY);
	fp = fopen("testTransfer.txt", "r");
	fstat(fd, &fs);

	//fprintf(stdout,"%d\n",fs.st_size);
	sprintf(fileSize, "%d", fs.st_size);
	//fprintf(stdout, "%s\n", fileSize);
	convertedSize = atoi(fileSize);
	fprintf(stdout, "File size of \"%s\" %d bytes\n", fileName, convertedSize);
		
	line = send(peerSockfd, &convertedSize, sizeof(convertedSize), 0);
	fprintf(stdout, "File size that should of been sent:\t%d\n",convertedSize);
	if (line <0){
		fprintf(stdout, "error sending file size\n");
	}
	else
		fprintf(stdout, "should of worked\n");
	fprintf(stdout, "Server sent:\t%d characters\n", line);
	remainingData = convertedSize;
	//len = send(peerSockfd, &fd, convertedSize, 0);

	//while((fgets(buffer, 512, fp) != NULL)){
		//fprintf(stdout, "%s\n", buffer);
		//send(peerSockfd, &buffer, convertedSize, 0);
//}

	while (((dataSent = send(peerSockfd, fd, &offset, 512)) > 0) && (remainingData > 0)){
			fprintf(stdout, "1. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", dataSent, offset, remainingData);
			remainingData -= dataSent;
			fprintf(stdout, "2. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", dataSent, offset, remainingData);
		
		}

	//else{
		//fprintf(stdout, "File not readable!\n");
	//}	
	
	
	return;

}

void recieveFile(int sockfd, char fileName[120]){
	int line, fileSize;
	char buffer[255];
	FILE *fp;
	fp = fopen(fileName, "w");	

	line = read(sockfd, &fileSize, sizeof(int));
	fprintf(stdout, "%d\n", fileSize);
	line = read(sockfd, buffer, 255);//Test
	fputs(buffer,fp);

}


int createSocket(){
	 
	fprintf(stdout,"in createSocket()\n");

	int sockfd, port = 7777;//Change so port is passed

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
	
	int newsockfd, line, clientlen;
	char buffer[256];
	struct sockaddr_in clientAddress;
	
	
	listen(sockfd,5);
	clientlen = sizeof(clientAddress);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientlen);//update
	//fprintf(stdout,"New connection on:\t%s",clientAddress.sin_addr);
	memset(buffer,0,256);
	sendFile(newsockfd, "testTransfer.txt");
	/*line = write(newsockfd, "Connected",10);
	line = read( newsockfd, buffer, 255);
	if (line<0){//error reading from socket
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




int main(){

	/*
	bind(address with socket)
	listen (for incoming connections on socket)
	accept(accept connection)
	*/
	//fprintf(stdout,"test\n");
	int sockfd;
	sockfd = createSocket();//change to pass port
	//sendFile(sockfd, "testTransfer.txt");
	//connectToFriend(sockfd, "127.0.0.1", 7777);//connecting to friend
	listenForConnection(sockfd);
	/*listen(sockfd,5);
	
	clientlen = sizeof(clientAddress);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientlen);*/
	
	return 0;
}
