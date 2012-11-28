#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;
	char inc_message[2000];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	
	// START EGRESS BLOCK THREAD
	//
	// *************************

	puts("Connected");

	int recv_return;
	int count = 0;
	while(recv_return =read(new_socket, inc_message , sizeof(inc_message)) && recv_return >= 0){
		printf("recv_return = %d\n",recv_return);
		fflush(stdout);
		count++;
		if(count >=5)
		{
			break;
		}
	}
	printf("after while loop, last message was: %s, recv_return was: %d", inc_message, recv_return);
	
	
	//Reply to the client
//	message = "Hello Client , I have received your connection. But I have to go now, bye\n";
//	write(new_socket , message , strlen(message));
	
	if (new_socket<0)
	{
		perror("accept failed");
		return 1;
	}
	
	return 0;
}
