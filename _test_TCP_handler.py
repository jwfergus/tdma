#!/usr/bin/python

##################
# TEST CLASS - testing TCP_handler.py
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import time
import socket
import Queue
import TCP_handler_functions
import threading
import sys


ip = '127.0.0.1'
port = 4242
buffer_size = 1024
key = 'secret key!'
message = 'open connections'
queue = Queue.Queue(0)

TCP_handler_thread = threading.Thread(target=TCP_handler_functions.TCP_handler, args=(queue, ip, port, buffer_size))
TCP_handler_thread.start()
time.sleep(0.5)

number_list = (1,2,3,4,5)
for number in number_list:
	local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	local_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	local_socket.connect((ip,port))
	local_socket.send('secret key! #' + str(number))
	time.sleep(.5)
	print '_test_TCP found in queue: ', queue.get()
	local_socket.close()
	

local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
local_socket.connect((ip,port))
local_socket.send('system exit')
sys.exit()


