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

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

#define NUMBER_OF_SLOTS 20
using namespace std;

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
	int socket_desc;
	struct sockaddr_in server;
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

			}
			
			int closeAcksReceived = 0;
			
			listen(socket_desc , 5);

			while(closeAcksReceived < ApplicationList[i].size())
			{
			
				//	Block on READing a message back from server
				if((recv_return = read(socket_desc, server_reply, sizeof(server_reply))) && recv_return < 0)
				{
					//FAILURE
					printf("\n**Read Failed**\nrecv_return: %d", recv_return);
					fflush(stdout);
					return 1;
				}
				printf("\n**Data Rcvd**\nserver_reply = %s\n",server_reply);
				fflush(stdout);
			
			}
			
			close(socket_desc);
			
		
		}	
	
	}	


	
	return 0;
}
