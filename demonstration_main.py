#!/usr/bin/python

##################
# Demonstration Main
#  creates the threads necessary to demonstrate functionality of MEL
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################
import time
import command_center
import node
import threading

Command_center_thread = threading.Thread(target=command_center.execute)
Command_center_thread.start()
time.sleep(0.5)

Node_thread = threading.Thread(target=node.execute)
Node_thread.start()
time.sleep(0.5)

Command_center_thread.join()
Node_thread.join()

