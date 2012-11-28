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
	while(count <=5)
	{
		//Send some data
		message = "HELLO SOCKET_WORLD \n\r";
		if( send(socket_desc , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		printf("Data Sent, count = %d\n",count);
		fflush(stdout);
		count++;
		sleep(2);
	}
	
	return 0;
}
