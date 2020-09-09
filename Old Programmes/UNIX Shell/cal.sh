# Assignment no. : 8
# Aim            : Write a shell script to modify the cal command of UNIX/LINUX to do the following :
#                  a) Print the current month and current year when called without parameter.
#                  b) Print the calander of the month of the current year if only one argument is between 1 and 12.

#! /bin/bash

if [ $# -eq 0 ]; then
	date +%B,\ %Y
elif [ $# -eq 1 ]; then
	if [ $1 -ge 1 -a $1 -le 12 ]; then
		cal $1 `date +%Y`
	else
		echo "Error : Month must be between 1 to 12"
	fi
else
	echo "Error : Invalid arguments"
fi