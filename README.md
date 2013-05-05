Time Division Multiple Access
======================

Summary:

Time Division Multiple Access (TDMA) of network access is a system for enforcing time division of network access among arbitrarily defined pools of servers. Think of it as a way of ensuring a group of servers (Group A for instance) can neither send nor receive data from other groups (Group B, C, D, etc.). This property is enforced for each group, ensuring no network traffic is transmitted outside of a group. TDMA enforces this by running a network traffic daemon on each server (node) that receives and executes commands from a central server (control server). The control server maintains a schedule of network access and passes control commands to server groups allowing and denying them network access according to this schedule.

For more details on TDMA, see http://github.com/jwfergus/thesis 

How to run:


$sudo apt-get install libnetfilter-queue-dev build-essential

$modprobe iptable_filter

$make

$sudo python gui.py

To preface, the demo folder is specifically setup to demo the code in the lab. The real logic of the system is contained within the controlServer, lib, and node directories. 

This gui will give you 6 buttons. These buttons all link to scripts inside of the demonstration folder. Each button also ssh's into each of the nodes and runs a command before exiting. "update Repos" logs in and executes a "git clone" command to get the latest code from the impact server. "Kill and Flush" kills the node-side process and flushes the iptables rules (firewall). "Clean nohup.out" deletes the ping information stored on nodes. "Start Node MEL" makes and executes the MEL process on nodes. "Start User App" executes a randomized pinging application on each node.



