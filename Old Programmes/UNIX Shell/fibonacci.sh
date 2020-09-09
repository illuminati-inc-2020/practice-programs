#!/bin/bash

fib()
{
	if [ $1 -le 0 ]
	then
		echo 0
	elif [ $1 -eq 1 ]
	then
		echo 1
	else
		local x=`expr $1 - 1`
		x=`fib $x`
		local y=`expr $1 - 2`
		y=`fib $y`
		local z=`expr $x + $y`
		echo $z
	fi
}

for (( i=0 ; i<=$1 ; i++ ))
do
	echo `fib $i`
done
