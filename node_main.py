#!/usr/bin/python

##################
# Main executable for the compute nodes
#  Starts MEL threads on the node
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import time
import command_center
import node
import threading

Node_thread = threading.Thread(target=node.execute)
Node_thread.start()
time.sleep(0.5)

Node_thread.join()
