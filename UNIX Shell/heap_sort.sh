#!/bin/bash

heapify()
{
	for (( i=1 ; i<$n ; i++ ))
	do
		for (( j=$i ; j>=0 ; j=($j-1)/2 ))
		do
			par=`expr \( $j - 1 \) / 2`
			if [ ${list[$j]} -gt ${list[$par]} ]
			then
				temp=${list[$j]}
				list[$j]=${list[$par]}
				list[$par]=$temp
			else
				break
			fi
		done
	done
}

destroy_heap()
{
	for (( i=$n-1 ; i>=0 ; i-- ))
	do
		temp=${list[0]}
		list[0]=${list[$i]}
		list[$i]=$temp
		for (( j=0 ; j<$i ; ))
		do
			lc=`expr $j \* 2 + 1` 
			rc=`expr $j \* 2 + 2` 
			if [ $lc -lt $i ]
			then
				if [ $rc -lt $i ]
				then
					if [ ${list[$lc]} -gt ${list[$j]} ]
					then
						if [ ${list[$rc]} -gt ${list[$lc]} ]
						then
							temp=${list[$j]}
							list[$j]=${list[$rc]}
							list[$rc]=$temp
							j=$rc
						else
							temp=${list[$j]}
							list[$j]=${list[$lc]}
							list[$lc]=$temp
							j=$lc
						fi
					else
						if [ ${list[$rc]} -gt ${list[$j]} ]
						then
							temp=${list[$j]}
							list[$j]=${list[$rc]}
							list[$rc]=$temp
							j=$rc
						else
							break
						fi
					fi
				else
					if [ ${list[$lc]} -gt ${list[$j]} ]
					then
						temp=${list[$j]}
						list[$j]=${list[$lc]}
						list[$lc]=$temp
						j=$lc
					else
						break
					fi
				fi
			else
				break
			fi	
		done
	done
}

if [ $# -gt 0 ]
then
	list=($@)
	n=$#
	heapify
	destroy_heap
	echo ${list[*]}
else
	echo "ERROR : Arguments missing"
fi
