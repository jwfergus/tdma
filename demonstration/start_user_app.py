#!/usr/bin/python

##################
# Start user application / ping application on nodes
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# 
##################
import os
import sys

def start_user_app():
	application_list = ('192.168.1.101', '192.168.1.102','192.168.1.103', '192.168.1.104')
	for ip_address in application_list:
		os.system("./start_user_app_expect.sh " + ip_address)


if __name__ == "__main__":
	start_user_app()
