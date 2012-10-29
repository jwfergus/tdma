#!/usr/bin/expect -f

##################
# Expect Script
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# Script for testing updating demonstration repos
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

sleep 1
send "sudo rm -r mutual-exclusion-logic\r"
expect {
	"mel:" {
		send "$pass\r" 
	}

	"$ " 
}
sleep 1
send "git clone git@impact.asu.edu:mutual-exclusion-logic.git\r"
sleep 1


