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
 
#include "comm_functions.h"

#include<stdio.h>
#include<iostream>
#include<string>
#include<cerrno>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr

using namespace std;


void getLocalIP(char* ip){
	FILE *ipPipe;
	int status;

	ipPipe = popen("ifconfig | grep 'inet addr:192.' | awk '{split($2,a,\":\");print a[2]}'", "r");
	if (ipPipe == NULL) 
		{ printf("\n***Could not get IP address!**\n Error: %s", strerror(errno)); fflush(stdout);}

	if(fgets(ip, 100, ipPipe) == NULL)
		{ printf("\n***Problem getting IP address!**\n Error: %s", strerror(errno)); fflush(stdout);}
		
	status = pclose(ipPipe);
}

void sendMessage(char* message, char* ip, int port){

	printf("Inside sendMessage - message: %s, ip: %s, port: %d", message, ip, port);
	cout << "\n***************\n" << endl;
	
	int socketFileDescriptor;
	struct sockaddr_in address_info;
	socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFileDescriptor == -1)
		{ printf("\n***Socket Creation Failed!**\n Error: %s", strerror(errno)); fflush(stdout);}
	address_info.sin_addr.s_addr = inet_addr(ip);
	address_info.sin_family = AF_INET;
	address_info.sin_port = htons(port);
	
	if(connect(socketFileDescriptor, (struct sockaddr *)&address_info, sizeof(address_info)) < 0)
		{ printf("\n***Connect Problem!**\n Error: %s", strerror(errno)); fflush(stdout);}
	printf("SendMessage connected to remote ip: %s", ip);
	fflush(stdout);
	
	if( send(socketFileDescriptor, message, strlen(message), 0) < 0)
		{ printf("\n***Send Failed**\n Error: %s", strerror(errno)); fflush(stdout);}
	printf("\n**Data Sent to %s**\n", ip);
	fflush(stdout);
	close(socketFileDescriptor);

}



