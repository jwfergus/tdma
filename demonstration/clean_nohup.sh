#!/usr/bin/expect -f

##################
# Expect Script
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# Script for killing node processes and flushing iptables
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
send "sudo -k\r"
expect "$ "
send "sudo rm mutual-exclusion-logic/node/nohup.out\r"
expect "mel:"
send "$pass\r" 
expect "$ "
