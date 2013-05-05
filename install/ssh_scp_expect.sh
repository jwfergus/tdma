#!/usr/bin/expect -f

##################
# Expect Script
# v1
# author: Joshua Ferguson <joshuawferguson@gmail.com>
# 
# Script for executing a command over SSH or sending a file through scp
#
# Parameters:
#	1: command (either ssh or scp)
#	2: remote location
#	3: remote command
#	4: password
##################

# check user input to make sure we have all of our parameters
if { [llength $argv] != 4} {
    puts "\nError - This script needs 4 parameters to execute: \n\n\t1) command to execute (ssh or scp)"
    puts "\t2) parameter 1 (i.e., file to be moved in the case of scp, or user@remote for ssh)"
    puts "\t2) parameter 2 (i.e., file destination for scp, or command to execute in single quotes \'\' for ssh)"
    puts "\t3) password\n";
    exit 1
} 
log_user 0


# set our variables from command line arguments
set command_to_execute [lindex $argv 0]
set param_1 [lindex $argv 1]
set param_2 [lindex $argv 2]
set password [lindex $argv 3]

# spawn the scp thread
spawn $command_to_execute $param_1 $param_2


# When prompted for a password, give it
expect "password:" 
send "$password\r" 

log_user 1
#
#	~!~ SPECIAL ~!~
#
# This bit of expect is used to determine the return code. For this project
#	I need to know the return codes of some commands executed remotely,
#	so it's important for the expect script to also return the same.
#
expect {
1	{exit 1}
"$ "	{exit 0}
}
