// TCP Client

// Must have the TCP  Server running before you can run this client

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
#include <pthread.h>

#define PORT	 12000
#define MAX_BACKLOG 3
#define BUFF_SIZE 1024

using namespace std;

string p_head = "\nclient> ";
string client_message = "Client X: Alice";

int main() { 
	int sockfd;
	char buffer[BUFF_SIZE] = {0};
	struct sockaddr_in servaddr;
	
	// Create a TCP socket
	// Notice the use of SOCK_STREAM for TCP connections
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	
	//Fill server information
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	//Connects to the server
	cout << p_head << "Connecting to Port " << servaddr.sin_port << " on sockfd(" << sockfd << ")...\n" << endl;
	if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0){
		cout << p_head << "Failed to connect to the server" << endl;
		return 1;
	}
	
	//Sends a message to the server
	send(sockfd, client_message.c_str(), strlen(client_message.c_str()), 0);
	
	//Receives a message from the server
	read(sockfd, buffer, BUFF_SIZE);
	
	cout << p_head << client_message << endl;
	cout << p_head << buffer << endl;
	close(sockfd);
	return 0;
}