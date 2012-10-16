mutual-exclusion-logic
======================

Implementing mutual exclusion of network 

To compile NF_Q,
install libnetfilter-queue-dev, make sure to insert the iptable_filter and ip_queue modules

Still todo

1. convert to state pattern

2. disconnect state logic from tcp-connection

3. build key check system

	3.1 nest key check on node side s.t. it loops and keeps checking
	
4. create exception classes

5. setup install script

	5.1 create daemon user for script
	
	5.2 give sudoer access for single script file that uses IPTABLES
	
6. write Open Connect state s.t. the state can be cut short

	6.1 import subprocess, consider mutex
	
7. consider adjusting sleep time to ensure the entire switching process occurs in less than 1s

8. create startup routine that gets initialization data from central server

	8.1 including time window size

9. create function to modify time window size


