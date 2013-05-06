#!/bin/bash

##################
# Bash Script
# v1.0
# author: Joshua Ferguson <joshuawferguson@gmail.com>
#
# Sub-script for checking dependencies on compute nodes - run locally on node.
#
# Parameters:
#	1: file to save results in
##################

#
# EXIT_STATUS is a flag used to determine if the remote caller needs to 
#	copy back the local log (i.e., if a problem occured). Throughout this 
#	script, if a problem occures this exit status flag should be switched to
#	1
#
# The echo statement is just to clear our local log file (the file name being
#	passed in as a parameter)
#
EXIT_STATUS=0
echo "" > $1


#
#	In this section we're testing for necessary packages installed
#
#
PACKAGES_TO_TEST=(build-essential libnetfilter-queue-dev)

for PACKAGE_NUMBER in $(seq 0 $((${#PACKAGES_TO_TEST[@]} - 1)) )
do
	if ! $(dpkg-query -W ${PACKAGES_TO_TEST[PACKAGE_NUMBER]} &> /dev/null)
		then
		echo " ${PACKAGES_TO_TEST[PACKAGE_NUMBER]} not installed." >> $1
		EXIT_STATUS=1
	fi
done	

if [ $EXIT_STATUS == 0 ]
	then
	rm $1
fi

exit $EXIT_STATUS
