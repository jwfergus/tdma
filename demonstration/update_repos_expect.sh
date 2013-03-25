#!/usr/bin/expect -f

##################
# Expect Script
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# Script for testing updating demonstration repos
##################



# IMPORTANT VARIABLE, WILL NOT WORK WITHOUT CHANGE
set pass "impactlab"

# Get IP address as input
set input_ip $argv
set timeout 5

# spawn the scp thread
spawn ssh mel@$input_ip


# When prompted for a password, give it (MUST BE SET AT THE TOP OF THE FILE)
expect "password:" 
send "$pass\r" 
expect "$ "
send "sudo -k\r"
expect "$ "
send "sudo rm -r mutual-exclusion-logic\r"
expect "mel:"
send "$pass\r" 
expect "$ "
send "git clone git@github.com:jwfergus/mutual-exclusion-logic.git\r"
expect "$ "


