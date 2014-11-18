#!/bin/sh
#
#  watch.sh  - a simple version of the watch utility, written in sh
#

	who | cut -d" " -f1 | sort -u > prev	# get current user list
	while true			# true is a program: exit(0);
	do
		sleep 30		# wait a while
		who | cut -d" " -f1 | sort -u > current	# get current user list
		echo "Logged out:"	# print header
		comm -23 prev current	| sed 's/^/   /' # and results
		echo "Logged in:"	# header
		comm -13 prev current   | sed 's/^/   /' # And results
	done
