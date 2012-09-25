#!/usr/bin/python

##################
# Initial MEL-node-server
# v0.2
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import socket
import security_functions
import time
from sys import exit
import threading
import Queue
import TCP_handler_functions
import os

def execute():
	# Communication Variables
	ip = '127.0.0.1'
	port = 4242
	buffer_size = 1024

	# Logic Variables
	sleep_time = .990 #should be adjusted based on clock speed
	exit_message_received = False # Program exit command flag
	open_connect = False # flag signifying open connections state
	command_queue = Queue.Queue(0)


	# Start TCP handler to begin receiving commands which are added to the command queue
	TCP_handler_thread = threading.Thread(target=TCP_handler_functions.TCP_handler, args=(command_queue, ip, port, buffer_size))
	TCP_handler_thread.start()
	time.sleep(0.5)



	while True:
		try:
			if __debug__:
				print 'Node.py - CLOSE CONNECTIONS'
			close_connections() # Close Connections
			open_connect = False
			while not open_connect:
				if __debug__:
					print 'Node.py - Blocking for command from queue'
				encrypted_command = command_queue.get(True) # block for queue command
				if __debug__:
					print 'Node.py - Command pulled from queue'
				if security_functions.key_check(encrypted_command):
					if security_functions.get_command(encrypted_command) == 'open':
						if __debug__:
							print 'Node.py - Open command found'
							print 'Node.py - OPEN CONNECTIONS'
						open_connect = True
						open_connections() # Open Connections
						time.sleep(sleep_time)
					elif security_functions.get_command(encrypted_command) == 'exit':
						if __debug__:
							print 'Node.py - Exit command found'
						cleanup_and_exit() # Cleanup and Exit!
					else:
						raise Exception('Command not recognized')
		except Exception as exception:
			print type(exception)
			print exception.args
			cleanup_and_exit() # Cleanup and Exit!
		
def close_connections():
	os.system('iptables -A INPUT -p icmp -j DROP')
def open_connections():
	os.system('iptables -D INPUT -p icmp -j DROP')
def cleanup_and_exit():
	# Need to write cleanup code
	#
	##############
	os.system('iptables -D INPUT -p icmp -j DROP')
	exit()
