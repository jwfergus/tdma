#!/usr/bin/expect -f

##################
# Expect Script
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# Script for starting user app (application_ping.py)
##################



# IMPORTANT VARIABLE, WILL NOT WORK WITHOUT CHANGE
set pass "CBCT1305"

# Get IP address as input
set input_ip $argv
set timeout 10

# spawn the scp thread
spawn ssh mel@$input_ip


# When prompted for a password, give it (MUST BE SET AT THE TOP OF THE FILE)
expect "password:" 
send "$pass\r" 
expect "$ "
send "nohup python mutual-exclusion-logic/demonstration/application_ping.py 5 30 &\r"
expect "$ "










