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
 * Initial implementation of MEL Node-side
 */

#include<stdio.h>
#include<string.h>	
#include<sys/socket.h>
#include<arpa/inet.h>	
#include<unistd.h>	
#include<cerrno>
#include<iostream>
#include "comm_functions.h"

using namespace std;

void getIP(char* ip){
	//Get our IP address
	FILE *ipPipe;
	int status;

	ipPipe = popen("ifconfig | grep 'inet addr:192.' | awk '{split($2,a,\":\");print a[2]}'", "r");
	if (ipPipe == NULL) // ERROR!
	{
		cout << "Could not get IP address!" << endl;
	}

	if(fgets(ip, 100, ipPipe) == NULL)
		cout << "Problem getting IP address!" << endl;
	status = pclose(ipPipe);
}

int main(int argc , char *argv[])
{

	char message[1024], ip[128];
	char* incomingMessage;
	const char* send_ip = "192.168.1.1";

	//********************************************************
	// 		Main Loop
	getIP(ip);

	while(1)
	{
		//
		//		RECEIVE COMMAND FROM CENTRAL SERVER
		//
		receiveMessage(ip, incomingMessage, 8888);
		printf("\n**Data Rcvd**\nmessage = %s\n",incomingMessage);
		fflush(stdout);
		
		
		sleep(2);
		
		//
		//		SEND INFO BACK TO CENTRAL SERVER
		//
		char* sendIP = new char[sizeof(send_ip)+1];
		strcpy(sendIP, send_ip);
		
		sendMessage(message, sendIP, 8888);
		
		
	}
	
	return 0;
}
