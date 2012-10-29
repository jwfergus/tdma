#!/usr/bin/python

##################
# Update MEL repos on demo servers
# v0.1
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
# Uses expect script to login and update repos
##################
import os

def update():
	application_list = ('192.168.1.101', '192.168.1.102','192.168.1.103', '192.168.1.104')
	for ip_address in application_list:
		os.system("./update_repos_expect.sh " + ip_address)
