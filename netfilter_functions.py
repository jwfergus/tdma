#!/usr/bin/python

##################
# Netfilter commands - Node side
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################
import os

def add_ICMP_to_queue_redirect():
	#
	#	Gotta write this part!
	#
	os.system('sudo iptables -A OUTPUT -p icmp -j NFQUEUE --queue-num 0')
	
def delete_ICMP_to_queue_redirect():
	#
	#	Gotta write this part!
	#
	os.system('sudo iptables -D OUTPUT -p icmp -j NFQUEUE --queue-num 0')
