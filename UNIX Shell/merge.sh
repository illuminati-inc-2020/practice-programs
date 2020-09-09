#!/bin/bash

merge()
{
	for (( i=0,j=0,k=0 ; i<n1&&j<n2 ; k++ ))
	do
		if [ ${a1[$i]} -le ${a2[$j]} ]
		then
			a[$k]=${a1[$i]}
			((i++))
		else
			a[$k]=${a2[$j]}
			((j++))
		fi	
	done
	for (( ; i<n1 ; k++,i++ ))
	do
		a[$k]=${a1[$i]}
	done
	for (( ; j<n2 ; k++,j++ ))
	do
		a[$k]=${a2[$j]}
	done
}

read -p "Enter number of elements in a1 : " n1
for (( i=0 ; i<n1 ; i++ ))
do
	read -p "a1[$i] = " a1[i]
done
read -p "Enter number of elements in a2 : " n2
for (( i=0 ; i<n2 ; i++ ))
do
	read -p "a2[$i] = " a2[i]
done

merge

for (( i=0 ; i<k ; i++ ))
do
	echo -n "${a[$i]} "
done
echo
