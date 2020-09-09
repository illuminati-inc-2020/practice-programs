#!/bin/bash

if [ $# -gt 0 ]
then
	key=$1
	list=(${*:2})
	lb=0
	ub=`expr ${#*} - 2`
	while [ $lb -le $ub ]
	do
		if [ $lb -eq $ub -a $key -eq ${list[$lb]} ]
		then
			echo "$key found at index $lb"
			exit
		fi
		mid=`expr \( $lb + $ub \) / 2`
		if [ $key -lt ${list[$mid]} ]
		then
			ub=`expr $mid - 1`
		elif [ $key -gt ${list[$mid]} ]
		then
			lb=`expr $mid + 1`
		else
			echo "$key found at index $mid"
			exit
		fi
	done
	echo "$key not found"
else
	echo "ERROR : arguments missisng"
fi
