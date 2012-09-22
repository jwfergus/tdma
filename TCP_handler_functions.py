#!/usr/bin/python

##################
# Asynchronous TCP handle
# v0.2
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import socket
import Queue

def TCP_handler(queue, ip, port, buffer_size):

	while True:
		local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		local_socket.bind((ip,port))
		local_socket.listen(1)	
		print 'TCP_handler thread waiting for connection . . .'
		remote_connection, remote_address = local_socket.accept()
		print 'TCP_handler thread connection FOUND!'
		
		while True:
			command = remote_connection.recv()
			if not command:
				break
			queue.put(command)
			print 'TCP_handler command received: ', command
		remote_connection.close()
		

TCP_handler(Queue.Queue(0), '127.0.0.1', 4242, 1024)
