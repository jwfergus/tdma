#!/usr/bin/python

##################
# TEST CLASS - testing TCP_handler.py
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import time
import TCP_handler
import socket
import asyncore

class client_test(asyncore.dispatcher):
	def __init__(self):
		asyncore.dispatcher.__init__(self)
		ip = '127.0.0.1'
		port = 4242
		buffer_size = 1024
		key = 'secret key!'
		message = 'open connections'
	def handle_connect(self):
		print 'connection successful!'
	def handle_write(self):
		self.send("Sending some data!")
my = client_test()
asyncore.loop()


