#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>//FOR inet_addr()
#include <sys/stat.h>
#include <sys/types.h>

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
	/*
	fprintf(stdout,"listening...\n");
	
	int newsockfd, line, clientlen;
	char buffer[256];
	struct sockaddr_in clientAddress;
	
	
	listen(sockfd,5);
	clientlen = sizeof(clientAddress);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientlen);//update
	//fprintf(stdout,"New connection on:\t%s",clientAddress.sin_addr);
	memset(buffer,0,256);
	line = write(newsockfd, "Connected",10);
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


void sendFile(int sockfd, char fileName[120]){//should be called from listenForConnection()
	int fileSize, line, convertedSize;

	FILE *fp; 
	if((fp = fopen(fileName, "rb"))){
		
		fseek(fp,0,SEEK_END);
		fileSize = ftell(fp);
		rewind(fp);
		
		convertedSize = htonl(fileSize);
		fprintf(stdout, "Size of \"%s\": %d bytes\n",fileName,fileSize);//DEBUG
		line = write(sockfd, &convertedSize, sizeof(convertedSize));

		line = send(sockfd, fp, fileSize, 0);
			
	}
	else{
		fprintf(stdout, "File not readable!\n");
	}	
	
	
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
	fclose(fp);

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
		recieveFile(sockfd, "testTransfer.txt");
		//line = read(sockfd, buffer, 255);
		//if(line <0){
			//fprintf(stdout,"error reading");
	}
		//fprintf(stdout,"%s\n",buffer);
		//fgets(buffer,255,stdin);
		//line = write(sockfd, buffer, strlen(buffer));
		//line = read(sockfd, buffer, 255);
		//fprintf(stdout,"%s\n",buffer);
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
	connectToFriend(sockfd, "127.0.0.1", 7777);//connecting to friend
	//listenForConnection(sockfd);
	/*listen(sockfd,5);
	
	clientlen = sizeof(clientAddress);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientlen);*/
	
	return 0;
}
