#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>//FOR inet_addr()
#include <string.h>
#include <unistd.h>
//#include "networking.h"//for testing


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

int main(){
	int sockfd, targetPort = 7777,line;
	//char *targetIP[255];
	char buffer[256];
	
	sockfd = createSocket();
	struct sockaddr_in targetAddress;
	memset(&targetAddress,0,sizeof(targetAddress));
	targetAddress.sin_family = AF_INET;
	//strcpy(targetAddress.sin_addr.s_addr,"127.0.0.1");
	targetAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	targetAddress.sin_port = htons(targetPort);
	//connect("127.0.0.1",7777);
	if(connect(sockfd, (struct sockaddr*)&targetAddress, sizeof(targetAddress)) < 0){
		fprintf(stdout,"Error connecting...\n");
	}


	line = read(sockfd, buffer, 255);
	fprintf(stdout,"%s\n",buffer);
	fgets(buffer,255,stdin);
	line = write(sockfd, buffer, strlen(buffer));
}
