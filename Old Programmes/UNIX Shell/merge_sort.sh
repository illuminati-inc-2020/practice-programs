# Assignment no. : 7
# Aim            : Write a shell script to perform merge sort on an array of numbers.

#! /bin/bash

merge ()
{
	k=0
	for (( i=$1,j=$3 ; i<=$2&&j<=$4 ; k++ ))
	do
		if [ ${list[$i]} -lt ${list[$j]} ]
		then
			temp[$k]=${list[$i]}
			let "i=$i+1"
		else
			temp[$k]=${list[$j]}
			let "j=$j+1"
		fi
	done
	for (( ; i<=$2 ; i++,k++ ))
	do
		temp[$k]=${list[$i]}
	done
	for (( ; j<=$4 ; j++,k++ ))
	do
		temp[$k]=${list[$j]}
	done
	for (( i=0,j=$1 ; j<=$4 ; i++,j++ ))
	do
		list[$j]=${temp[$i]}
	done
}

merge_sort ()
{
	if [ $1 -lt $2 ]
	then
		let "ub1=($1+$2)/2"
		let "lb2=$ub1+1"
		merge_sort $1 $ub1
		let "ub1=($1+$2)/2"
		let "lb2=$ub1+1"
		merge_sort $lb2 $2
		let "ub1=($1+$2)/2"
		let "lb2=$ub1+1"
		merge $1 $ub1 $lb2 $2
	fi
}

if [ $# -lt 1 ]
then
	echo "Error : Too few arguments"
	echo "Format : merge_sort [number1] [number2] [number3] ..."
else
	i=0
	for num in $*
	do
		list[$i]=$num
		let "i=$i+1"
	done
	lb=0
	let "ub=$#-1"
	merge_sort $lb $ub	
	for (( i=$lb ; i<=$ub ; i++ ))
	do
		output="$output ${list[$i]}"
	done
	echo $output
fi
