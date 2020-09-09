#!/bin/bash

if [ $# -eq 2 ]
then
	if [ $1 -gt 0 -a $2 -gt 0 ]
	then
		x=$1
		y=$2
		while [ $x -ne $y ]
		do
			if [ $x -gt $y ]
			then
				x=`expr $x - $y`
			else
				y=`expr $y - $x`
			fi
		done
		echo $x
	else
		echo ERROR : arguments must be positive integer
	fi
else
	echo ERROR : arguments missing
fi
