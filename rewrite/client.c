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
	char message[1024];
	
	//
	//	Loop over Time Slot -> Application -> Node IP
	//
	vector< vector<string> > ApplicationList = getAppIPList("test.txt");
	for (int slotCount = 0; slotCount < NUMBER_OF_SLOTS; slotCount++)
	{

		for (vector< vector<string> >::size_type i = 0; i < ApplicationList.size(); i++)
		{
			printf("\n\n************\nSending Messages for App %d", i);
			fflush(stdout);
			for (vector<string>::size_type j = 0; j < ApplicationList[i].size(); j++)
			{
				//
				//	Per Node IP:
				//
				
				strcpy(message, "HELLO SOCKET_WORLD \n\r");
				char* sendIP = new char[ApplicationList[i][j].size()+1];
				strcpy(sendIP, ApplicationList[i][j].c_str());
				sendMessage(message, sendIP, 8888);

			}
			
			
			char ip[128];
			getIP(ip);

			printf("\n\n************\nReceiving Message Counts for App %d", i);
			fflush(stdout);
			
			countMessagesReceived(ip, 8888, ApplicationList[i].size());
			
			
			
		
		}	
	
	}	


	
	return 0;
}
