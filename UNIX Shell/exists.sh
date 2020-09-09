# Assignment no.   : 2
# Aim              : Write a shell script that will be able to take any no. of filename as arguments and checks whether a file exists and has size greater than 0.

#! /bin/bash

if [ $# -lt 1 ]; then
	echo "Error : Argument missing";
	echo "Format : exists [file1] [file2] ...";
else
	for filename in $*
	do
		if [ ! -e $filename ]; then
			echo "$filename : does not exist";
		elif [ ! -s $filename ]; then
			echo "$filename : zero size";
		else
			if [ -d $filename ]; then
				echo "$filename : directory";
			elif [ -f $filename ]; then
				echo "$filename : regular file";
			elif [ -h $filename ]; then
				echo "$filename : symbolic link";
			fi
		fi
	done
fi