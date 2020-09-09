# Assignment no.      : 9c
# Aim                 : Write a shell script to generate all combinations of 1,2,3.

#! /bin/bash

comb ()
{
	x="1 2 3"
	if [ ${#1} -lt 3 ]; then
		for i in $x
		do
			param="$1$i"
			comb $param
		done
	else
		echo "$1"
	fi
}

comb ""
