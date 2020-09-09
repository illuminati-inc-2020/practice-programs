#!/bin/bash

key=$1
for i in ${*:2}
do
	if [ $i -eq $key ] 
	then
		echo found
		exit
	fi
done
echo not found
