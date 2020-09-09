#!/bin/bash

if [ $# -eq 1 ]
then
	for x in `seq $1`
	do
		for y in `seq $x $1`
		do
			echo -n " "
		done
		for y in `seq $x`
		do
			echo -n " *"
		done
		echo
	done
else
	echo "ERROR : Invalid arguments"
fi
