// TCP Server

// Must have this server running before you can run the TCP Client code

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/time.h>
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <thread>
#include <csignal>
#include <vector>

#define PORT	 12000
#define MAX_BACKLOG 3
#define BUFF_SIZE 1024

int sockfd, cliXfd, cliYfd, valreadX, valreadY;
char * bufferXp;
char * bufferYp;
struct timeval timeX, timeY;

using namespace std;

void receive_data(int client){
	if(client==1){
		valreadX = read(cliXfd, bufferXp, BUFF_SIZE);
		gettimeofday(&timeX, NULL);
		cout << bufferXp << endl;
	} else {
		valreadY = read(cliYfd, bufferYp, BUFF_SIZE);
		gettimeofday(&timeY, NULL);
		cout << bufferYp << endl;
	}
}

int main() { 
	socklen_t len;
	
	char bufferX[BUFF_SIZE] = {0};
	char bufferY[BUFF_SIZE] = {0};
	bufferXp=bufferX;
	bufferYp=bufferY;
	struct sockaddr_in servaddr;
	struct sockaddr clientX, clientY;
	socklen_t cXsize, cYsize;
	
	// Create a TCP socket
	// Notice the use of SOCK_STREAM for TCP connections
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&clientX, 0, sizeof(clientX));
	memset(&clientY, 0, sizeof(clientY));
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	// Bind the socket with the server address 
	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	
	cout << "\nserver> Running on Port " << servaddr.sin_port << "\n" << endl;
	
	if(listen(sockfd, MAX_BACKLOG)<0){ //listen for a client
		cout << "Failed to connect to client 1" << endl;
		return 1;
	}
	cliXfd = accept(sockfd, &clientX, &cXsize);
	if(listen(sockfd, MAX_BACKLOG)<0){ //listen for a client
		cout << "Failed to connect to client 2" << endl;
		return 1;
	}
	cliYfd = accept(sockfd, &clientY, &cYsize);
	close(sockfd);
	
	//receive client information
	thread tX(receive_data, 1);
	thread tY(receive_data, 2);
	tX.join();
	tY.join();
	
	//manipulate received information
	string ack;
	if(timercmp(&timeX, &timeY, <)){
		ack = string(bufferX) << " received before " << string(bufferY);
	} else if(timercmp(&timeX, &timeY, >)){
		ack = string(bufferY) << " received before " << string(bufferX);
	} else {
		ack = string(bufferX) << " received simultaneously with " << string(bufferY);
	}
	send(cliXfd, ack , strlen(ack), 0); 
	send(cliYfd, ack , strlen(ack), 0);
	cout << "Sent acknowledgment to both X and Y" << endl;
	close(cliXfd);
	close(cliYfd);
	return 0; 
} 