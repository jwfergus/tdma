#!/usr/bin/python

##################
# Command center
#  Issues commands to nodes.
# v0.2
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import time
import socket
import Queue
import TCP_handler_functions
import threading
import sys

def execute():
	time.sleep(2.5)
	ip = '127.0.0.1'
	port = 4242
	buffer_size = 1024
	key = 'secretKey!'

	number_list = (1,2)
	for number in number_list:
	
		if __debug__:
			print 'command_center.py - opening connection'
		local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		local_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		local_socket.connect((ip,port))
		local_socket.send(key +' open')
		time.sleep(2.5)
		local_socket.close()
	

	if __debug__:
		print 'command_center.py - opening connection for exit'
	local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	local_socket.connect((ip,port))
	local_socket.send(key +' exit')
	sys.exit()
