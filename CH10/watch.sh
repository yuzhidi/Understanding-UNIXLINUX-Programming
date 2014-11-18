#!/bin/sh
#
#  watch.sh  - a simple version of the watch utility, written in sh
#
	who | sort > prev		# get initial user list
	while true			# true is a program: exit(0);
	do
		sleep 30		# wait a while
		who | sort > current	# get current user list
		echo "Logged out:"	# print header
		comm -23 prev current	# and results
		echo "Logged in:"	# header
		comm -13 prev current   # and results
		mv current prev		# make now past
	done
