#!/usr/bin/expect -f

##################
# Expect Script
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# Script for starting MEL on nodes
##################



# IMPORTANT VARIABLE, WILL NOT WORK WITHOUT CHANGE
set pass "CBCT1305"

# Get IP address as input
set input_ip $argv
set timeout 5

# spawn the scp thread
spawn ssh mel@$input_ip


# When prompted for a password, give it (MUST BE SET AT THE TOP OF THE FILE)
expect "password:" 
send "$pass\r" 
expect "$ "
send "cd mutual-exclusion-logic\r" 
expect "$ "
send "sudo -k\r"
expect "$ "
send "make\r"
expect "$ "
send "sudo su\r"
expect "mel:"
send "$pass\r" 
expect "# "
send "nohup python node_main.py &\r"
expect "'"
