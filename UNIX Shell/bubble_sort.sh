#!/bin/bash

if [ $# -gt 0 ]
then
	list=($*)
	for(( i=0 ; i<$#-1 ; i++ ))
	do
		for(( j=0 ; j<$#-$i-1 ; j++ ))
		do
			if [ ${list[$j]} -gt ${list[`expr $j + 1`]} ]
			then
				temp=${list[$j]}
				list[$j]=${list[`expr $j + 1`]}
				list[`expr $j + 1`]=$temp
			fi
		done
	done
	echo ${list[*]}
else
	echo "ERROR : Arguments missing"
fi
