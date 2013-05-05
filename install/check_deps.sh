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

PACKAGES_TO_TEST=(build-essential libnetfilter-queue-dev)
EXIT_STATUS=0
echo "" > $1
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
