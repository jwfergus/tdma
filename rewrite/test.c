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




/**
 * PACK QUEUE CODE START
 */

struct nfq_handle *nfqHandle;
struct nfq_q_handle *myQueue;
struct nfnl_handle *netlinkHandle;

int fd, res;
char buf[4096];

double max_time = 2;
time_t start_time, current_time_diff, current_time;
char* time_string_to_print;


	static int Callback(nfq_q_handle *myQueue, struct nfgenmsg *msg, nfq_data *pkt, void *cbData) {
		uint32_t id = 0;
		nfqnl_msg_packet_hdr *header;

		cout << "pkt recvd: ";

		if ((header = nfq_get_msg_packet_hdr(pkt))) {
			id = ntohl(header->packet_id);
			cout << "id " << id << ";"; 
		}
		cout << endl;
		
		current_time_diff = time(NULL) - start_time;
		if(((double)current_time_diff) >= max_time) 
		{
			current_time = time(NULL);
			time_string_to_print = ctime(&current_time);
			cout <<"Inside CallBack > Verdict_Repeat. Time = " << time_string_to_print << endl;
			return nfq_set_verdict(myQueue, id, NF_REPEAT, 0, NULL);
		} 
		current_time = time(NULL);
		time_string_to_print = ctime(&current_time);
		cout <<"Inside CallBack > Verdict_Accept. Time = " << time_string_to_print<< endl;
		return nfq_set_verdict(myQueue, id, NF_ACCEPT, 0, NULL);
		
		
	}

	/**
	 * PACK QUEUE CODE END
	 */
	 
	 
	 
	 


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

	iptablesPipe = popen("sudo iptables -A OUTPUT ! -d 192.168.1.1 -j NFQUEUE --queue-num 0", "r");
	if (iptablesPipe == NULL) // ERROR!
	{
		cout << "Could not close Egress!" << endl;
	}
	pclose(iptablesPipe);
}

void openEgress(){
	//Get our IP address
	FILE *iptablesPipe;

	iptablesPipe = popen("sudo iptables -D OUTPUT ! -d 192.168.1.1 -j NFQUEUE --queue-num 0", "r");
	if (iptablesPipe == NULL) // ERROR!
	{
		cout << "Could not open Egress!" << endl;
	}
	pclose(iptablesPipe);
}

int main(int argc , char *argv[])
{




	/**
	 * PACK QUEUE CODE START
	 */
	 
	 
	// Get a queue connection handle from the module
	if (!(nfqHandle = nfq_open())) {
	cerr << "Error in nfq_open()" << endl;
	exit(-1);
	}

	// Unbind the handler from processing any IP packets
	// Not totally sure why this is done, or if it's necessary...
	if (nfq_unbind_pf(nfqHandle, AF_INET) < 0) {
	cerr << "Error in nfq_unbind_pf()" << endl;
	exit(1);
	}

	// Bind this handler to process IP packets...
	if (nfq_bind_pf(nfqHandle, AF_INET) < 0) {
	cerr << "Error in nfq_bind_pf()" << endl;
	exit(1);
	}

	// Install a callback on queue 0
	if (!(myQueue = nfq_create_queue(nfqHandle,  0, &Callback, NULL))) {
	cerr << "Error in nfq_create_queue()" << endl;
	exit(1);
	}

	// Turn on packet copy mode
	if (nfq_set_mode(myQueue, NFQNL_COPY_PACKET, 0xffff) < 0) {
	cerr << "Could not set packet copy mode" << endl;
	exit(1);
	}

	netlinkHandle = nfq_nfnlh(nfqHandle);
	fd = nfnl_fd(netlinkHandle);
	
	/**
	 * PACK QUEUE CODE END
	 */






	char ip[128];
	const char* send_ip = "192.168.1.1";

	//*********************************
	// 		Main Loop
	getIP(ip);

	while(1)
	{
		//
		//		RECEIVE COMMAND FROM CENTRAL SERVER
		//
	
		
		
			
		/**
		 * PACK QUEUE CODE START
		 */
		start_time = time(NULL);
		while ( ((res = recv(fd, buf, sizeof(buf), MSG_DONTWAIT)) && res >= 0) || ((start_time - (current_time = time(NULL))) < max_time) ) {
		start_time = time(NULL);

			// I am not totally sure why a callback mechanism is used
			// rather than just handling it directly here, but that
			// seems to be the convention...
			cout << "res = " << res << endl;
			current_time = time(NULL);

		}
		/**
		 * PACK QUEUE CODE END
		 */
		 
		 
		 
		
		//
		//		SEND INFO BACK TO CENTRAL SERVER
		//
		char* sendIP = new char[sizeof(send_ip)+1];
		strcpy(sendIP, send_ip);
		
	
	}
	
	openEgress();
	
	/**
	 * PACK QUEUE CODE START
	 */
	nfq_destroy_queue(myQueue);
	nfq_close(nfqHandle);
	/**
	 * PACK QUEUE CODE END
	 */
	 
	 
	 
	 
	 
	return 0;
}
