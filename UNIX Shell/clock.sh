# Write a shell script to implement background process that wil continually print current time in upper right corner of the screen while user can do normal job in normal prompt (using tput command)

#! /bin/bash

while [ 1 ]
do
	tput sc
	date=`date $*`
	let "col=`tput cols`-${#date}"
	tput cup 0 $col
	echo $date
	tput rc
	tput sgr0					#Turn off all attrbutes
	sleep 1
done
