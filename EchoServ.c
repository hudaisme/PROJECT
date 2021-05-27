#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define MAXLINE 2000 /* maximum text length*/
#define PORT 3000 /*port*/
#define BACKLOG 10 /*maximum number of client connections */

int main (int argc, char **argv)
{
        //Declaration variables
         int socket_desc, connfd, h;
         socklen_t clilen;
         char buf[MAXLINE];
         struct sockaddr_in client;
         struct sockaddr_in server;

         //creation of the socket
         socket_desc = socket (AF_INET, SOCK_STREAM, 0);
         if(socket_desc == -1)
         {
                printf("Could not create socket");
         }

         //preparation of the socket address
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(PORT);

        //Binding....
        bind (socket_desc, (struct sockaddr *) &server, sizeof(server));

        //Listening....
        listen (socket_desc, BACKLOG);
	printf("HELLO ECHO SERVER!!\n");
	printf("%s\n","Server is running.... \nDude, I'm waiting connections from client.......");
	printf("________________________________________________________________");
        //Infinite loop
        for ( ; ; ) {
                clilen = sizeof(client);
                connfd = accept (socket_desc, (struct sockaddr *) &client, &clilen);
        	printf("\nATTENTION !!\n");
	        printf("%s\n","Yeay!!! Received client request...");
                while ( (h = recv(connfd, buf, MAXLINE,0)) > 0)  {
                        printf("%s","String I received and sent it back to you: ");
                        puts(buf);
                        send(connfd, buf, h, 0);
                }
                if (h < 0) {
                        perror("OMG, cannot read");
                        exit(1);
                }
                close(connfd);

        }
        //Closing socket
        close (socket_desc);
}
