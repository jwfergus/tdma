#!/usr/bin/python

##################
# Main executable for the compute nodes
#  Starts MEL threads on the node
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import time
from node import node
import threading
import commands

# Obtain our locally assigned IP address
assigned_ip = commands.getoutput("ifconfig | grep 'inet addr:192.' | awk '{split($2,a,\":\");print a[2]}'")
Node_thread = threading.Thread(target=node.execute(assigned_ip, 3))
Node_thread.start()
time.sleep(0.5)

Node_thread.join()
