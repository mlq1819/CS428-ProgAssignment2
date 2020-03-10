// TCP Server

// Must have this server running before you can run the TCP Client code

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <thread>
#include <csignal>
#include <vector>

#define PORT	 12000
#define MAX_BACKLOG 12


using namespace std;

vector<thread> threads;

void signalHandler( int signum ){
	while(threads.size()>0){
		cout << "Waiting on thread " << threads.size()+1 << "..." << endl;
		threads.end().join();
		cout << "Thread " << threads.size()+1 << " ended" << endl;
		threads.pop_back();
	}
	exit(signum);
}

int main() { 
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr; // cliaddr; //might not be relevant for TCP connections
	threads = vector<thread>();
	signal(SIGINT, signalHandler); //sets up a handler for if the program is forcibly closed
	
	// Create a TCP socket
	// Notice the use of SOCK_STREAM for TCP connections
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	//memset(&cliaddr, 0, sizeof(cliaddr));  //likely unnecessary here
	
	/*if(setsockopt(sockfd, )<0){ //might be relevant later for manipulating server options
		cout << "Failed to initialize socket options" << endl;
		return 1;
	}*/
	
	
	
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	// Bind the socket with the server address 
	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	
	std::cout << "\nserver> Running on Port " << servaddr.sin_port << "\n" << std::endl;
	
	
	
	/*
	// random generator
	srand(time(0));

        while (1) {
		//Receive the client packet along with the address it is coming from
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 
			MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		buffer[n] = '\0';

		//If a random number in the range of 0 to 10 is less than 4,
		//we consider the packet lost and do not respond
		if (rand()%10 < 4) continue;

		//Otherwise, the server responds
		sendto(sockfd, (const char *)buffer, strlen(buffer), 
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
	}*/
	return 0; 
} 
