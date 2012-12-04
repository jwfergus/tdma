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
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main(int argc , char *argv[])
{
	char ip[100];
	getLocalIP(ip);
	printf("IPtest: %s", ip);
	
	
	int messageSize = 2000;
	char message[messageSize];
	strcpy(message, "HELLO SOCKET_WORLD \n\r");
	sendMessage(message, messageSize, "192.168.1.101", 8888);
	return 0;
}
