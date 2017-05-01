#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){

	/*
	bind(address with socket)
	listen (for incoming connections on socket)
	accept(accept connection)
	*/
	int sockfd, newsockfd, port = 7777,clientlen;

	struct sockaddr_in serverAddress, clientAddress;
	
	memset(&serverAddress, 0, sizeof(serverAddress));//intialise serv_addr to 0
	//missing memmove here might be for client
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);//set port number

	sockfd = socket(AF_INET, SOCK_STREAM, 0);//create socket
	bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	listen(sockfd,5);
	
	clientlen = sizeof(clientAddress);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientlen);
	
	return 0;
}
