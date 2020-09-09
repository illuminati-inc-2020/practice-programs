# Assignment no.      : 4
# Aim                 : Write a shell script to implement a recursive shell function to find factorial of a given no.

#! /bin/bash

fact ()
{
	if [ $1 -eq 0 ]; then
		echo 1;
	else
		n=`expr $1 - 1`
		fn=`fact $n`
		fnn=`expr $1 \* $fn`
		echo $fnn
	fi
}

if [ $# -ne 1 ]; then
	echo "Error : Argument missing"
	echo "Format : factorial [number]"
else
	echo `fact $1`
fi
