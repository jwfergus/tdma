#!/bin/bash

##################
# Bash Script
# v1.0
# author: Joshua Ferguson <joshuawferguson@gmail.com>
#
# Main script for checking dependencies on compute nodes.
#
# Parameters:
#	1: List of Node IP Addresses
#	2: user
##################

#
#	Variables for remote dependency checking (check script, output file, etc.)
#

USER=$2
REMOTE_DEP_CHECK_SCRIPT="check_deps.sh"
REMOTE_DEP_RESULTS="dependency_results"
OVERALL_DEP_RESULTS="full_system_dependency_results"
PASSWORD="impactlab"
DEP_PROBLEM=0

#
#	Function definition
#		Checks the passed IP address for dependencies by 1)sending over
#		the dependency check file (defined as REMOTE_DEP_CHECK_SCRIPT
#		above), 2) executing that script remotely, and 3) checking the
#		exit status of that command. See the ssh_scp_expect script
#		for more details about how the commands are executed remotely.
#
function check_dependencies {
	./ssh_scp_expect.sh scp $REMOTE_DEP_CHECK_SCRIPT $USER@$1:~/ $PASSWORD > /dev/null
	./ssh_scp_expect.sh ssh $USER@$1 "./$REMOTE_DEP_CHECK_SCRIPT $REMOTE_DEP_RESULTS;echo \$?" $PASSWORD > /dev/null
	STATUS=$?
	if [ $STATUS == 1 ]
		then
		./ssh_scp_expect.sh scp $USER@$1:~/$REMOTE_DEP_RESULTS . $PASSWORD > /dev/null
		echo "\n$1:" >> $OVERALL_DEP_RESULTS
		cat $REMOTE_DEP_RESULTS >> $OVERALL_DEP_RESULTS
		rm $REMOTE_DEP_RESULTS
		DEP_PROBLEM=1
	fi
}


#
#	Variables for progress calculation and printing.
#
NODE_COUNT=$(wc -l < "$1")
PROGRESS_COUNT=0
COMPLETE_STRING="% complete.\r"

#
#	Clear results file
#
echo "" > $OVERALL_DEP_RESULTS



while read line
do
	check_dependencies $line
	#
	#	This section prints the progress of the check. Since bash can't
	#		handle floating point, 'bc' is used to divide and 
	#		'printf' is used to format 'bc's output
	#
	PROGRESS_COUNT=$(($PROGRESS_COUNT+1))
	PROGRESS=$(printf "%.2f\n" $(bc <<< "scale = 4; ($PROGRESS_COUNT / $NODE_COUNT) * 100"))$COMPLETE_STRING
	echo -ne $PROGRESS
	
	

done < "$1"
if [ $DEP_PROBLEM == 1 ]
	then
	echo "Dependencies missing on some remote nodes, check log file: $OVERALL_DEP_RESULTS."
fi


