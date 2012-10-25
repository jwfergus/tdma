#!/usr/bin/python

##################
# Netfilter commands - Node side
# v0.2
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# All commands in here must be run as super user
##################
import os

def initialize():
	#
	#	
	#
	os.system('modprobe iptable_filter')
def add_ICMP_to_queue_redirect():
	#
	#	Adds (see -A flag) rule into iptables/netfilter that redirects
	#		ICMP packets to queue-num 0
	os.system('sudo iptables -A OUTPUT -p icmp -j NFQUEUE --queue-num 0')
	
def delete_ICMP_to_queue_redirect():
	#
	#	Delets (see -D flag) rule into iptables/netfilter that redirects
	#		ICMP packets to queue-num 0
	os.system('sudo iptables -D OUTPUT -p icmp -j NFQUEUE --queue-num 0')
