# Write Script to find out biggest number from given three nos. Nos are argument. Print error if sufficient arguments are not supplied.

#! /bin/bash

if [ $# -lt 2 ]; then
	echo "Error : Arguments missing"
	echo "Format : biggest_of [no1] [no2] ..."
else
	big=$1
	for x in $* 
	do
		if [ $x -gt $big ]; then
			let big=$x
		fi
	done
	echo $big
fi
