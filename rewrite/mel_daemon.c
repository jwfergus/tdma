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
#include <iomanip>
#include <cstdlib>
#include <netinet/in.h>
#include "comm_functions.h"
using namespace std;

extern "C" {
  #include <linux/netfilter.h>  /* Defines verdicts (NF_ACCEPT, etc) */
  #include <libnetfilter_queue/libnetfilter_queue.h>
}

using namespace std;

struct nfnl_handle *nfnlHandle;
struct nfq_q_handle *nfQueue;
struct nfq_handle *nfqHandle;

int netfilterFileDescriptor, nfqRecvReturn;
char nfqRecvBuffer[4096];

double max_time = 2;
time_t startTime, currentTime;
char* timeStringToPrint;


	//
	//	Process and release a packet onto the network
	//
	static int ProcessPacket(nfq_q_handle *nfQueue, struct nfgenmsg *nfqMessage, nfq_data *packet, void *unused) 
	{
		nfqnl_msg_packet_hdr *packetHeader;
		uint32_t packetID = 0;
		packetHeader = nfq_get_msg_packet_hdr(packet);
		packetID = ntohl(packetHeader->packet_id);
		return nfq_set_verdict(nfQueue, packetID, NF_ACCEPT, 0, NULL);
	}

	 
	 
	 
	 


void getIP(char* ip){
	//Get our IP address
	FILE *ipPipe;

	ipPipe = popen("ifconfig | grep 'inet addr:192.' | awk '{split($2,a,\":\");print a[2]}'", "r");
	if (ipPipe == NULL) // ERROR!
	{
		cout << "Could not get IP address!" << endl;
	}

	if(fgets(ip, 100, ipPipe) == NULL)
		cout << "Problem getting IP address!" << endl;
	pclose(ipPipe);
}

void closeEgress(){
	//Get our IP address
	FILE *iptablesPipe;

	//iptablesPipe = popen("sudo iptables -A OUTPUT ! -d 192.168.1.1 -j NFQUEUE --queue-num 0", "r");
	iptablesPipe = popen("sudo iptables -A OUTPUT -p icmp -j NFQUEUE --queue-num 0", "r");
	if (iptablesPipe == NULL) // ERROR!
	{
		cout << "Could not close Egress!" << endl;
	}
	pclose(iptablesPipe);
}

void openEgress(){
	//Get our IP address
	FILE *iptablesPipe;

	//iptablesPipe = popen("sudo iptables -D OUTPUT ! -d 192.168.1.1 -j NFQUEUE --queue-num 0", "r");
	iptablesPipe = popen("sudo iptables -D OUTPUT -p icmp -j NFQUEUE --queue-num 0", "r");
	if (iptablesPipe == NULL) // ERROR!
	{
		cout << "Could not open Egress!" << endl;
	}
	pclose(iptablesPipe);
}

void establishNFQueueConnection(){
	// make initial queue handle
	nfqHandle = nfq_open();

	// Ensure no other processes are messing with packets
	if (nfq_unbind_pf(nfqHandle, AF_INET) < 0) {
	cout << "Problem with nfq_unbind - are you running as super user?" << endl; 
	exit(1);
	}

	// Bind handler to AF_INET packets (IPv4)
	nfq_bind_pf(nfqHandle, AF_INET);

	// Specify the queue number and the callback
	nfQueue = nfq_create_queue(nfqHandle,  0, &ProcessPacket, NULL);

	// Makes the queue enable userspace packet copying
	nfq_set_mode(nfQueue, NFQNL_COPY_PACKET, 0xffff);
	
	// Grab the file descriptor handle
	nfnlHandle = nfq_nfnlh(nfqHandle);
	netfilterFileDescriptor = nfnl_fd(nfnlHandle);
}

int main(int argc , char *argv[])
{
	char message[1024], ip[128];
	char* incomingMessage;
	const char* send_ip = "192.168.1.1";


	getIP(ip);
	closeEgress();
	establishNFQueueConnection();

	while(1)
	{
		//
		//		RECEIVE COMMAND FROM CENTRAL SERVER
		//
		incomingMessage = receiveMessage(ip, 8888);
		printf("\n******mel_daemon - Data Rcvd**\nmessage = %s\n",incomingMessage);
		fflush(stdout);
		delete(incomingMessage);	
		
		//
		//		BUSYWAIT (I KNOW I'M BAD) FOR PACKETS TO PROCESS
		//
		//	So this is complicated enough that it deserves a little explaining. 
		//	While we're still within the time window to send packets (the while statement)
		//	
		//
		//
		startTime = time(NULL);
		while ( ((currentTime = time(NULL))-startTime) < max_time ) {
			cout << "start time: " << startTime << "current time: " << time(NULL) << endl;
			nfqRecvReturn = recv(netfilterFileDescriptor, nfqRecvBuffer, sizeof(nfqRecvBuffer), MSG_DONTWAIT);
			if(nfqRecvReturn >= 0)
			{
				nfq_handle_packet(nfqHandle, nfqRecvBuffer, nfqRecvReturn);
			}
			

		}	 
		 
		
		//
		//		SEND ACK BACK TO CENTRAL SERVER
		//
		char* sendIP = new char[sizeof(send_ip)+1];
		strcpy(sendIP, send_ip);
		sendMessage(message, sendIP, 8888);
	
	}
	
	// Cleanup 
	nfq_destroy_queue(nfQueue);
	nfq_close(nfqHandle);
	openEgress();

	return 0;
}
