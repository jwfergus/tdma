mutual-exclusion-logic
======================

Implementing mutual exclusion of network 


Still todo
1. convert to state pattern
2. disconnect state logic from tcp-connection
3. build key check system
	2.1 nest key check on node side s.t. it loops and keeps checking
4. create exception classes
5. setup install script
	4.1 create daemon user for script
	4.2 give sudoer access for single script file that uses IPTABLES
6. write Open Connect state s.t. the state can be cut short
	5.1 import subprocess, consider mutex
7. consider adjusting sleep time to ensure the entire switching process occurs 
	in less than 1s


