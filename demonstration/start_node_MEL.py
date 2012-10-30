#!/usr/bin/python

##################
# Kill Node processes and Flush IPTables on demo nodes
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# 
##################
import os
import sys

def start():
	application_list = ('192.168.1.101', '192.168.1.102','192.168.1.103', '192.168.1.104')
	for ip_address in application_list:
		os.system("./start_node_MEL_expect.sh " + ip_address)


if __name__ == "__main__":
	start()
