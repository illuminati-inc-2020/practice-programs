#!/bin/bash

hour=`date +%k`
if [ $hour -ge 0 -a $hour -lt 6 ]; then
	echo "Good Night"
elif [ $hour -ge 6 -a $hour -lt 12 ]; then
	echo "Good Morning"
elif [ $hour -ge 12 -a $hour -lt 18 ]; then
	echo "Good Afternoon"
elif [ $hour -ge 18 -a $hour -lt 24 ]; then
	echo "Good Night"
fi

