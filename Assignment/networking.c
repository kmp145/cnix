#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>//FOR inet_addr()

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
	
	int clientlen, newsockfd, line;
	char buffer[256];
	struct sockaddr_in clientAddress;
	
	
	listen(sockfd,5);
	clientlen = sizeof(clientAddress);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientlen);
	
	//fprintf(stdout,"New connection on:\t%s",clientAddress.sin_addr.s_addr);
	memset(buffer,0,256);
	line = write(newsockfd, "Connected",10);
	line = read( newsockfd, buffer, 255);

	if (line<0){//error reading from socket
	}
	fprintf(stdout,"You entered:\t%s\n", buffer);
	line = write(newsockfd, "Returning message",18);
}

void connectToFriend(int sockfd, char * targetIP, int targetPort){//still needs updating

	int line;
	char buffer[256];	
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

int main(){

	/*
	bind(address with socket)
	listen (for incoming connections on socket)
	accept(accept connection)
	*/
	//fprintf(stdout,"test\n");
	int sockfd;
	sockfd = createSocket();//change to pass port
	listenForConnection(sockfd);
	/*listen(sockfd,5);
	
	clientlen = sizeof(clientAddress);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientlen);*/
	
	return 0;
}
