#!/usr/bin/python

##################
# Bash GUI functions
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# Set of simple abstractions for reporting what's happening to the user
##################
import sys

def print_overwrite_with_color(data_to_print, color):
	if(color == "green"):
		ascii_color = "\x1B[32;40m"
	elif(color == "red"):
		ascii_color = "\x1B[31;40m"	
	else:
		raise AttributeError("color: \'" + str(color) + "\' is not available")
		
	sys.stdout.write("\r\033[K")
	sys.stdout.write(ascii_color + str(data_to_print) + "\x1B[0m")
	sys.stdout.flush()
	
