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
	
	//struct linger socketLingerOption;
	//socketLingerOption.l_onoff = 1;
	//socketLingerOption.l_linger = 5;
	printf("\n**Inside sendMessage - message: %s, ip: %s, port: %d**\n", message, ip, port);
	
	int socketFileDescriptor;
	struct sockaddr_in addressInfo;
	socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socketFileDescriptor == -1)
		{ printf("\n***Socket Creation Failed!**\n Error: %s", strerror(errno)); fflush(stdout);}
	
	//setsockopt(socketFileDescriptor, SOL_SOCKET, SO_LINGER, &socketLingerOption, sizeof(socketLingerOption));
	
	addressInfo.sin_addr.s_addr = inet_addr(ip);
	addressInfo.sin_family = AF_INET;
	addressInfo.sin_port = htons(port);
	
	if(connect(socketFileDescriptor, (struct sockaddr *)&addressInfo, sizeof(addressInfo)) < 0)
		{ printf("\n***Connect Problem!**\n Error: %s", strerror(errno)); fflush(stdout);}
	printf("\n**SendMessage connected to remote ip: %s**\n", ip);
	fflush(stdout);
	
	if( send(socketFileDescriptor, message, strlen(message), 0) < 0)
		{ printf("\n***Send Failed**\n Error: %s", strerror(errno)); fflush(stdout);}
	printf("\n**Data Sent to %s**\n", ip);
	fflush(stdout);
	shutdown(socketFileDescriptor, SHUT_RD);
	close(socketFileDescriptor);
	

}

char *receiveMessage(char* ip, int port){
	printf("\n**Inside receiveMessage - ip: %s, port: %d**\n", ip, port);
	
	int socketFileDescriptor, acceptedSockFileDescriptor;
	struct sockaddr_in localAddressInfo, remoteAddressInfo;
	socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFileDescriptor == -1)
		{ printf("\n***Socket Creation Failed!**\n Error: %s", strerror(errno)); fflush(stdout);}
	int socketOptionsValue = 1;
	setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEADDR, &socketOptionsValue, sizeof(socketOptionsValue));
	localAddressInfo.sin_addr.s_addr = inet_addr(ip);
	localAddressInfo.sin_family = AF_INET;
	localAddressInfo.sin_port = htons(port);
	
	if(bind(socketFileDescriptor, (struct sockaddr *)&localAddressInfo, sizeof(localAddressInfo)) < 0)
		{ printf("\n***Bind Failed!**\n Error: %s", strerror(errno)); fflush(stdout);}
	printf("\n**Bind done on ip: %s**\n", ip);
	fflush(stdout);
	
	listen(socketFileDescriptor, 2);
	unsigned int remoteAddressLength = sizeof(remoteAddressInfo);
	if((acceptedSockFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *) &remoteAddressInfo, &remoteAddressLength)) < 0)
		{ printf("\n***Accept Failed!**\n Error: %s", strerror(errno)); fflush(stdout);}
	printf("\n**Connection Accepted**\n");
	fflush(stdout);
	char* message = new char[1024];
	if( read(acceptedSockFileDescriptor, message, sizeof(message)) < 0)
		{ printf("\n***Read Failed**\n Error: %s", strerror(errno)); fflush(stdout);}
	printf("\n**Data Received**\n"); //Should correct this to specify which IP it is receiving from. . .
	fflush(stdout);
	
	close(acceptedSockFileDescriptor);
	close(socketFileDescriptor);
	return message;
}




