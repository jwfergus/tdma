#!/usr/bin/python

##################
# Asynchronous TCP handle
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import Queue
import socket
import threading
import asyncore

class TCP_handler():
	
	_TCP_handler_instance = None
	queue = None
	ip = None
	port = None
	buffer_size = None

	def __init__(self, ip, port, buffer_size):
		print 'inside TCP_handler init'
		self.ip = ip
		self.port = port
		self.buffer_size = buffer_size
		queue = Queue.Queue()
		_TCP_handler_instance = threading.Thread(target=_TCP_handler, args=(ip, port, buffer_size))
		_TCP_handler_instance.start()
	def dequeue():
		return queue.get()
	def close():
		self.close()
		
class _TCP_handler(asyncore.dispatcher):
	__TCP_handler = None
	local_socket = None
	remote_connection = None
	remote_address = None
	
	def __init__(self, ip, port, buffer_size):
		asyncore.dispatcher.__init__(self)
		print 'inside _TCP_handler init'
		local_socket = self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
		local_socket.setblocking(0)
		local_socket.bind((ip,port))
		local_socket.listen(1)	
	def handle_accept(self):
		print 'inside _TCP_handler handle_accept'
		remote_connection, remote_address = local_socket.accept()
		__TCP_handler = __TCP_handler()
	def handle_close(self):
		print 'inside _TCP_handler handle_close'
		self.close()
	asyncore.loop()
	print 'asyncore.loop() called'

class __TCP_handler(asyncore.dispatcher):
	
	def __init__(self, buffer_size):
		asyncore.dispatcher.__init__(self)
		print 'inside __TCP_handler init'
		return
	def handle_read(self):
		print 'inside __TCP_handler handle_read'
		queue.put(self.recv(buffer_size))
	def handle_close(self):
		print 'inside __TCP_handler handle_close'
		self.close()
	asyncore.loop()
	print 'asyncore.loop() called'
	


	
	

