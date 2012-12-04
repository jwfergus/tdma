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
#include<cerrno>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include "comm_functions.h"

#define NUMBER_OF_SLOTS 20
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

vector< vector<string> > getAppIPList(const char *filename)
{
	vector< vector<string> > listOfIPs;
	string line;
	ifstream appIPListFile (filename);
	if (appIPListFile.is_open())
	{
		int appID = 0;
		while ( appIPListFile.good())
		{	int nodeID = 0;
			listOfIPs.push_back (vector< string> (0) );
			getline (appIPListFile,line);
			istringstream lineAsStringStream( line );
			while (!lineAsStringStream.eof())
			{
				string field;
				getline( lineAsStringStream, field, ' ' ); 
				listOfIPs[appID].push_back (field);
				nodeID++;
			}
			appID++;
		}
		appIPListFile.close();
	}
	else cout << "Unable to open file"; 
	listOfIPs.pop_back();
	
	/**
	*
	*	print the list of application IPs  
	*
	**/
	cout << "\n*****Printing App List*****\n" << endl;
	
	for (vector< vector<string> >::size_type i = 0; i < listOfIPs.size(); i++)
	{
		cout << "Application " << i << " IPs:"<< endl;
		for (vector<string>::size_type j = 0; j < listOfIPs[i].size(); j++)
		{
			cout << listOfIPs[i][j] << "; ";
		}
		cout << "\n" << endl;
	}
	
	return listOfIPs;

}


int main(int argc , char *argv[])
{
	int socket_desc, rcv_ack_socket, c;
	struct sockaddr_in server, client;
	char message[2000] , server_reply[2000];
	int recv_return;
	
	//
	//	Loop over Time Slot -> Application -> Node IP
	//
	vector< vector<string> > ApplicationList = getAppIPList("test.txt");
	for (int slotCount = 0; slotCount < NUMBER_OF_SLOTS; slotCount++)
	{

		for (vector< vector<string> >::size_type i = 0; i < ApplicationList.size(); i++)
		{
		
			for (vector<string>::size_type j = 0; j < ApplicationList[i].size(); j++)
			{
				//
				//	Per Node IP:
				//
				
				//	Create socket
				socket_desc = socket(AF_INET , SOCK_STREAM , 0);
				if (socket_desc == -1)
					printf("Could not create socket");
				
				
				//	IP pulled from Node IP list (ApplicationList)
				server.sin_addr.s_addr = inet_addr(ApplicationList[i][j].c_str());
				server.sin_family = AF_INET;
				server.sin_port = htons( 8888 );
				
				strcpy(message, "HELLO SOCKET_WORLD \n\r");
				char* sendIP = new char[ApplicationList[i][j].size()+1];
				strcpy(sendIP, ApplicationList[i][j].c_str());
				sendMessage(message, sendIP, 8888);
				/**
				//	Connect to remote server OR DIE! 
				if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0){puts("connect error");return 1;}
				printf("Connected to %s.\n", ApplicationList[i][j].c_str());
				fflush(stdout);
	
				//	Send message
				strcpy(message, "HELLO SOCKET_WORLD \n\r");
				if( send(socket_desc , message , strlen(message) , 0) < 0)
				{
					//FAILURE
					printf("\n**Send Failed**\nCur Message: %s", message);
					fflush(stdout);
					return 1;
				}
				printf("\n**Data Sent**\n");
				fflush(stdout);
				
				close(socket_desc);
				//**/

			}
			
			int closeAcksReceived = 0;
			
			rcv_ack_socket = socket(AF_INET , SOCK_STREAM , 0);
			int optval;
			optval = 1;
			setsockopt(rcv_ack_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
			if (rcv_ack_socket == -1){printf("Could not create socket: %s", strerror(errno));}			

			char ip[100];
			getIP(ip);

			//Prepare the sockaddr_in structure
			server.sin_family = AF_INET;
			server.sin_addr.s_addr = inet_addr(ip);
			server.sin_port = htons( 8888 );

			//Bind
			if( bind(rcv_ack_socket,(struct sockaddr *)&server , sizeof(server)) < 0)
			{
			printf("\n**bind failed**\n, %s", strerror(errno));
			return 1;
			}
			printf("bind done on ip: %s",ip);
			fflush(stdout);


			listen(rcv_ack_socket , 5);

			while(closeAcksReceived < ApplicationList[i].size())
			{
			
				//	Block on READing a message back from server
				printf("Before accepting connection");
				fflush(stdout);
				int new_socket = accept(rcv_ack_socket, (struct sockaddr *)&client, (socklen_t*)&c);
				printf("After accepting connection, but before reading");
				fflush(stdout);
				
				if((recv_return = read(new_socket, server_reply, sizeof(server_reply))) && recv_return < 0)
				{
					//FAILURE
					printf("\n**Read Failed**\nrecv_return: %d, sock_errno: %s", recv_return, strerror(errno));
					fflush(stdout);
					return 1;
				}
				printf("\n**Data Rcvd**\nserver_reply = %s\n",server_reply);
				fflush(stdout);
				closeAcksReceived++;
			
			}
			
			close(rcv_ack_socket);
			
		
		}	
	
	}	


	
	return 0;
}
