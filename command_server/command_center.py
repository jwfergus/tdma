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
import threading
import sys

##################
# Currently just a hardcoded, evenly time divided schedule based on the 
#	'number_list' variable
##################
def execute():
	time.sleep(2.5)
	port = 4242
	buffer_size = 1024
	key = 'secretKey!'

	# application_list is, essentially, our system-user-application state
	application_list = (('192.168.1.101', '192.168.1.102'),('192.168.1.103', '192.168.1.104'))
	number_of_iterations = 50

	for iteration in range(number_of_iterations):
		for application_number in range(len(application_list)):
			for box_to_start in application_list[application_number]:
				# Creates and opens socket to IP and issues secret key + open 
				#	command
				if __debug__:
					print 'command_center.py - opening connection to ' + box_to_start
				local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				local_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
				local_socket.connect((box_to_start,port))
				local_socket.send(key +' open')
				local_socket.close()
			
			time.sleep(5)
	
	for application_number in range(len(application_list)):
		for box_to_start in application_list[application_number]:
			# Creates and opens socket to IP and issues secret key + exit 
			#	command
			if __debug__:
				print 'command_center.py - opening connection for exit to ' + box_to_start
			local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			local_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
			local_socket.connect((box_to_start,port))
			local_socket.send(key +' exit')
			local_socket.close()

	
	sys.exit()
