#!/bin/bash

if [ $# -gt 0 ]
then
	list=($*)
	for (( fu=0 ; fu<$# ; fu++ ))
	do
		min=${list[$fu]}
		index=$fu
		for (( i=$fu+1 ; i<$# ; i++ ))
		do
			if [ ${list[$i]} -lt $min ]
			then
				min=${list[$i]}
				index=$i
			fi
		done
		list[$index]=${list[$fu]}
		list[$fu]=$min
	done	
	echo ${list[*]}
else
	echo "ERROR : Argument missing"
fi
