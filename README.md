mutual-exclusion-logic
======================

Implementing mutual exclusion of network 

To run:

$sudo apt-get install libnetfilter-queue-dev build-essential

$modprobe iptable_filter

$make

$sudo python gui.py

To preface, the demo folder is specifically setup to demo the code in the lab. The real logic of the system is contained within the controlServer, lib, and node directories. 

This gui will give you 6 buttons. These buttons all link to scripts inside of the demonstration folder. Each button also ssh's into each of the nodes and runs a command before exiting. "update Repos" logs in and executes a "git clone" command to get the latest code from the impact server. "Kill and Flush" kills the node-side process and flushes the iptables rules (firewall). "Clean nohup.out" deletes the ping information stored on nodes. "Start Node MEL" makes and executes the MEL process on nodes. "Start User App" executes a randomized pinging application on each node.



