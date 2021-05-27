#include <stdlib.h>      // Contains declarations information
#include <stdio.h>      // I/O function
#include <sys/types.h>  // Defines data types
#include <sys/socket.h> // Define the type socklen_t
#include <netinet/in.h> // Contains definitions for the internet protocol family
#include <string.h>     // String function
#include <arpa/inet.h>  // Definitions for internet operations.
#define MAXLINE 2000    // Maximum text length
#define PORT 3000       // Server port



int main(int argc, char **argv)
{
        int sockfd;
        struct sockaddr_in servaddr;
        char sending[MAXLINE], receiving[MAXLINE];
        if (argc !=2) {
                perror("Usage: PLEASE ENTER IP address of the server");
                exit(1);
        }
	//Create a socket for client
        if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
                perror("connection error");
                exit(2);
        }
       
	//Creation of socket
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr= inet_addr("192.168.56.105");
        servaddr.sin_port =  htons(PORT); 

	//Connection  of client's socket
        if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
                perror("Connection to the server is error!!");
                exit(3);
        }

	printf("HELLO ECHO CLIENT!! WELCOME TO THE ECHO PROTOCOL");
	printf("\n.................................................");
	printf("\nPlease enter message: ");
	//Read the contents of the FILE*stdin
        while (fgets(sending, MAXLINE, stdin) != NULL) {
                send(sockfd, sending, strlen(sending), 0);

                if (recv(sockfd, receiving, MAXLINE,0) == 0){
                        perror("The server unexpectedly shut down.");
                        exit(4);
                }
	 	printf("ATTENTION CLIENT !! \n");
                printf("%s", "Received from the server: ");
                fputs(receiving, stdout);
        }
        exit(0);
}
