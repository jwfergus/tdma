/**
 * @file
 * @author  Joshua Ferguson <jwfergus@asu.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * Copyright Joshua W. Ferguson 2012
 *
 * @section DESCRIPTION
 *
 * Initial implementation of MEL command server
 */

#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>

int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message , server_reply[2000];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
		
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected\n");
	

	int count = 1;
	int recv_return;
	while(count <=5)
	{
		//Send some data
		message = "HELLO SOCKET_WORLD \n\r";
		if( send(socket_desc , message , strlen(message) , 0) < 0)
		{
			//FAILURE
			printf("\n**Send Failed**\nCur Message: %s", message);
			fflush(stdout);
			return 1;
		}
		printf("\n**Data Sent**\ncount = %d\n",count);
		fflush(stdout);
		
		if((recv_return = read(socket_desc, server_reply, sizeof(server_reply))) && recv_return < 0)
		{
			//FAILURE
			printf("\n**Read Failed**\nrecv_return: %d", recv_return);
			fflush(stdout);
			return 1;
		}
		printf("\n**Data Rcvd**\nserver_reply = %s, count = %d\n",server_reply, count);
		fflush(stdout);
		count++;
		
	}
	
	return 0;
}
