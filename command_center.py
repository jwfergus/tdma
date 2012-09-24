#!/usr/bin/python

##################
# client for testing
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import socket
from time import sleep

ip = '127.0.0.1'
port = 4242
buffer_size = 1024
key = 'secret key!'
message = 'open connections'

local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
local_socket.connect((ip,port))

local_socket.send('secret key!')
sleep(1.1)
local_socket.send('open connections')
sleep(1.1)
local_socket.send('secret key!')
sleep(1.1)
local_socket.send('open connections')
sleep(1.1)
local_socket.send('secret key!')
sleep(1.1)
local_socket.send('exit')
local_socket.close()

print 'Central_Command - Script complete: exiting'
