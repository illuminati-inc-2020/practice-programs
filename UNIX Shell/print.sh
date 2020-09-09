# Assignment no. : 3.b
# Aim            : Write a shell script to print a text file from line no. m to line no. n. 

#! /bin/bash

if [ $# -ne 3 ]; then
	echo "Error : Arguments misssing"
	echo "Format : print [filename] [line_number1] [line_number2]"
else
	awk -v m=$2 -v n=$3 '
	BEGIN{
		c=1
	}
	{
		if(c>=m&&c<=n)
			print $0;
		c++
	}' $1
fi
