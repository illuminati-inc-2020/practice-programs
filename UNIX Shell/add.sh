# Aim : Write shell script that will add two nos, which are supplied as command line argument, and if this two nos are not given show error and its usage
   
#! /bin/bash

if [ $# -ne 2 ]; then
	echo "Error : Arguments missing"
	echo "Format : add [no1] [no2]"
else
	let x=$1+$2;
	echo "$x"
fi