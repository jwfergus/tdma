/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 Joe Kopena, Drexel University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Joe Kopena <tjkopena@cs.drexel.edu>
 */

#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include <netinet/in.h>
extern "C" {
  #include <linux/netfilter.h>  /* Defines verdicts (NF_ACCEPT, etc) */
  #include <libnetfilter_queue/libnetfilter_queue.h>
}

using namespace std;
struct nfq_handle *nfqHandle;

struct nfq_q_handle *myQueue;
struct nfnl_handle *netlinkHandle;

double max_time;

int fd, res;
char buf[4096];
time_t start_time, current_time_diff;

//----------------------------------------------------------------------
//------------------------------------------------------
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
  if(((double)current_time_diff) >= max_time) {
        return nfq_set_verdict(myQueue, id, NF_REPEAT, 0, NULL);
  } 
  return nfq_set_verdict(myQueue, id, NF_ACCEPT, 0, NULL);

  // end Callback
}

//----------------------------------------------------------------------
//------------------------------------------------------
void signal_handler(int signal_num) {
  signal(SIGUSR1, signal_handler);
  printf("SIGUSR1 FOUND!\n");
  start_time = time(NULL);
  while ((res = recv(fd, buf, sizeof(buf), 0)) && res >= 0) {
 
    // I am not totally sure why a callback mechanism is used
    // rather than just handling it directly here, but that
    // seems to be the convention...
    
    nfq_handle_packet(nfqHandle, buf, res);

    // end while receiving traffic
    if(((double)current_time_diff) >= max_time) {
        break;
    } 
  }
  return;

  // end signal_handler
}


int main(int argc, char *argv[])
{
max_time = atof(argv[1]);
signal(SIGUSR1, signal_handler);


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

while (1)
sleep(3600);

  nfq_destroy_queue(myQueue);

  nfq_close(nfqHandle);

return 0;
}
