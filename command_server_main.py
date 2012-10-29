#!/usr/bin/python

##################
# Main executable for the command server
#  Starts MEL thread on the command server
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

import time
from command_server import *
import node
import threading

Command_center_thread = threading.Thread(target=command_center.execute)
Command_center_thread.start()
time.sleep(0.5)

Command_center_thread.join()
