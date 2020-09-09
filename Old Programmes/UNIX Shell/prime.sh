#! /bin/bash

if [ $# -eq 1 ]
then
	if [ "`factor $1`" = "$1: $1" ]
	then
		echo "prime"
	else
		echo "not prime"
	fi
elif [ $# -eq 2 ]
then
	for (( i=$1 ; i<=$2 ; i++ ))
	do
		x="$i: $i"
		if [ "`factor $i`" = "$i: $i" ]
		then
			echo "$i"
		fi
	done
else
	echo "Invalid number of arguments"
	echo "prime [num]"
	echo "prime [lower_bound] [upper_bound]"
fi
