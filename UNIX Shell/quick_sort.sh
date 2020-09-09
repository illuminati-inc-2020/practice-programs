#! /bin/bash

partition ()
{
	local pivot=$1
	for (( i=lb+1,j=ub ; pivot<j ; ))
	do
		if [ ${list[$i]} -le ${list[$pivot]} ]
		then
			local temp=${list[$i]}
			list[$i]=${list[$pivot]}
			list[$pivot]=$temp
			let "i=i+1"
			let "pivot=pivot+1"
		else
			local temp=${list[$i]}
			list[$i]=${list[$j]}
			list[$j]=$temp
			let "j=j-1"
		fi
	done
	return $pivot
}

quick_sort ()
{
	if [ $1 -lt $2 ]
	then
		partition $1 $2
		local pivot=$?
		let "ub1=$pivot-1"
		quick_sort $1 $ub1
		let "lb2=$pivot+1"
		quick_sort $lb2 $2
	fi
}

if [ $# -eq 0 ]
then
	echo "Arguments Missing"
else
	i=0
	for num in $*
	do
		list[$i]=$num
		let "i=i+1"
	done
	let "ub=$#-1"
	quick_sort 0 $ub
	for (( i=0 ; i<=$ub ; i++ ))
	do
		output="$output ${list[$i]}"
	done
	echo $output
fi
