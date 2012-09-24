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
import threading
import Queue

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
		# Close Connections
		#
		###################
		open_connect = False
		while not open_connect:
			#block for queue command
			encrypted_command = command_queue.get(True)
			if security_functions.key_check(command):
				if security_functions.get_command(encrypted_command) == 'open':
					open_connect = True
					# Open Connections
					#
					##################
					time.sleep(sleep_time)
					
				elif security_functions.get_command(encrypted_command) == 'exit':
					# Exit Cleanup
					#
					##############
					exit()
				else:
					raise Exception('Command not recognized')
	except Exception as exception:
		print type(exception)
		print exception.args
		# Exit Cleanup
		#
		##############
		exit()
