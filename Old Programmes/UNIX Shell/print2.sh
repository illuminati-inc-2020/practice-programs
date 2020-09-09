# Assignment no. : 3.a
# Aim            : Write a shell script to insert symbol << at the start of each line and >> symbol at the end of each line of a text file.

#! /bin/bash

if [ $# -ne 1 ]; then
	echo "Error : Arguments misssing"
	echo "Format : printall [filename]"
else
	awk '
	{
		print "<<"$0">>";
	}' $1>temp.tmp
	cp temp.tmp $1
	rm temp.tmp
fi
