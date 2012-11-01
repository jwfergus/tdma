#!/usr/bin/python

##################
# Randomized Ping Application
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 	Call ping_application( # of iterations, seconds per iteration)
##################

import random
import os
import threading
import time
import sys

def ping(ip_address, count):
	interval = "0." + str(random_number_generator.randint(3,9))
	print "interval is " + str(interval)
	os.system("ping -c " + str(count) + " -i " + interval + " " + ip_address + " >> " + ping_results_filename)



def ping_application(target_ip, iterations, window_size):
	for x in range(0,iterations):
		ping_thread = threading.Thread(target=ping, args=([target_ip, window_size]))
		ping_thread.start()
		time.sleep(window_size)

random_number_generator = random.Random()
random_number_generator.seed(0)
ping_results_filename = "ping_results"

os.system( "rm " + ping_results_filename )
time.sleep(1)


iterations = int(sys.argv[1])
window_size = int(sys.argv[2])
assigned_ip = commands.getoutput("ifconfig | grep 'inet addr:192.' | awk '{split($2,a,\":\");print a[2]}'")
if(assigned_ip == "192.168.1.101")
	target_ip = "192.168.1.102"
elif(assigned_ip == "192.168.1.102")
	target_ip = "192.168.1.101"
elif(assigned_ip == "192.168.1.103")
	target_ip = "192.168.1.104"
elif(assigned_ip == "192.168.1.104")
	target_ip = "192.168.1.103"
	

ping_application(target_ip, iterations, window_size)


	
