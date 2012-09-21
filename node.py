#!/usr/bin/python

##################
# Initial MEL-node-server
# v0.2
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import socket
import security_functions
from time import sleep
from sys import exit

# Communication Variables
ip = '127.0.0.1'
port = 4242
buffer_size = 1024

# Logic Variables
sleep_time = .990 #should be adjusted based on clock speed
exit_message_received = False # Program exit command flag
open_signal_received = False # Signal to open all connections

local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
local_socket.bind((ip,port))
local_socket.listen(1)


print 'Node - Connection address:', address

# Check the key





while not exit_message_received:
	try:
		open_signal_received = False
		#OPEN CONNECTIONS
		print 'Node - Opening all connections'
		sleep(sleep_time)
		
		#CLOSE CONNECTIONS
		print 'Node - Closing all connections'
		while not open_signal_received:
			# Check the key
			data = connection.recv(buffer_size)
			if not security_functions.key_check(data):
				print 'inc security key. was: ', data
				connection.close()
				raise Exception('Node - incorrect security key - EXITING')
			else:
				print 'Node - client key validated' 
			
			while True:
				while True:
					data = connection.recv(buffer_size)
					if data:
						break
					sleep(.005)
				print 'Node - received data:', data
				if data == 'open connections':
					open_signal_received = True
					break
				if data == 'exit':
					raise Exception('Node - Exit command received.')
					
					
	except Exception, exception_message:
		print exception_message
		connection.close()
		exit()
		


