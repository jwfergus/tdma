#!/usr/bin/perl

##################
# Stop all node-side code and flush iptables
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# Done in perl since python script would kill itself
##################

system("killall -9 python");
system("killall packet_queuing_submodule");
system("killall mel_daemon");
system("iptables --flush");
