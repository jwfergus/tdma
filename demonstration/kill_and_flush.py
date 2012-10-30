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

def update():
	application_list = ('192.168.1.101', '192.168.1.102','192.168.1.103', '192.168.1.104')
	for ip_address in application_list:
		os.system("./kill_and_flush_expect.sh " + ip_address)


if __name__ == "__main__":
	update()
