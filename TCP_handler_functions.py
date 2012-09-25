#!/usr/bin/python

##################
# Asynchronous TCP handle
# v0.2
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import socket
import Queue
import sys

def TCP_handler(queue, ip, port, buffer_size):
	if __debug__:
		print 'TCP_handler thread - Inside TCP_handler thread'	
	local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	local_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	local_socket.bind((ip,port))
	local_socket.listen(1)	
	while True:
		if __debug__:
			print 'TCP_handler thread - waiting for connection . . .'
		remote_connection, remote_address = local_socket.accept()
		if __debug__:
			print 'TCP_handler thread - connection FOUND!'
		
		while True:
			command = remote_connection.recv(buffer_size)
			if not command:
				break
			queue.put(command)
			if __debug__:
				print 'TCP_handler thread - command received: ', command
		remote_connection.close()
		

