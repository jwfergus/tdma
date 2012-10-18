#!/usr/bin/python

##################
# Initial MEL-node-server
# v0.3
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
import netfilter_functions
import bash_gui_functions
from subprocess import Popen, call, PIPE



def execute():
	# Communication Variables
	ip = '127.0.0.1'
	port = 4242
	buffer_size = 1024

	# Logic Variables
	open_connection_time = 2 #should be adjusted based on clock speed
	exit_message_received = False # Program exit command flag
	open_connect = False # flag signifying open connections state
	command_queue = Queue.Queue(0)


	# Start TCP handler to begin receiving commands which are added to the command queue
	TCP_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	TCP_handler_thread = threading.Thread(target=TCP_handler_functions.TCP_handler, args=(TCP_socket, command_queue, ip, port, buffer_size))
	TCP_handler_thread.start()
	time.sleep(0.5)
	
	# Initialize and start packet submodule
	netfilter_queue_process = Popen([os.getcwd()+'/packet_queuing_submodule', str(open_connection_time)], stdout=PIPE, stderr=PIPE)
	netfilter_functions.add_ICMP_to_queue_redirect()


	while True:
		try:
			open_connect = False
			while not open_connect:
				if __debug__:
					print 'Node.py - Blocking for command from queue'
				else:
					bash_gui_functions.print_overwrite_with_color("CLOSED", "red")
				encrypted_command = command_queue.get(True) # block for queue command
				if __debug__:
					print 'Node.py - Command pulled from queue'
				if security_functions.key_check(encrypted_command):
					if security_functions.get_command(encrypted_command) == 'open':
						if __debug__:
							print 'Node.py - Open command found'
							print 'Node.py - OPEN CONNECTIONS'
						else:
							bash_gui_functions.print_overwrite_with_color("OPEN", "green")
						open_connect = True
						open_connections(netfilter_queue_process.pid) # Open Connections
						time.sleep(open_connection_time)
					elif security_functions.get_command(encrypted_command) == 'exit':
						if __debug__:
							print 'Node.py - Exit command found'
						cleanup_and_exit(TCP_socket, netfilter_queue_process.pid) # Cleanup and Exit!
					else:
						raise Exception('Command not recognized')
		except Exception as exception:
			print type(exception)
			print exception.args
			cleanup_and_exit(TCP_socket, netfilter_queue_process.pid) # Cleanup and Exit!
		
def open_connections(pid):
	call(["kill", "-s", "SIGUSR1", str(pid)])
def cleanup_and_exit(TCP_socket, Queue_pid):
	# Need to write cleanup code
	#
	##############	
	TCP_socket.close()
	call(["kill", "-9", str(Queue_pid)])
	netfilter_functions.delete_ICMP_to_queue_redirect()
	exit()
