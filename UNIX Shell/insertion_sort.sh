#!/bin/bash

if [ $# -gt 0 ]
then
	list=($*)
	for (( fu=1 ; fu<$# ; fu++ ))
	do
		temp=${list[$fu]}
		flag=0
		for (( i=$fu-1 ; i>=0 ; i-- ))
		do
			if [ $temp -gt ${list[$i]} ]
			then
				flag=1
				list[`expr $i + 1`]=$temp
				break
			fi
			list[`expr $i + 1`]=${list[$i]}
		done
		if [ $flag -eq 0 ]
		then
			list[0]=$temp
		fi
	done
	echo ${list[*]}
else
	echo "ERROR : Arguments missing"
fi
