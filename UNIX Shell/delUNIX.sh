# Assignment no. : 9.a
# Aim            : Write a shell script to delete all lines in a text file containing string "UNIX". 

#! /bin/bash

if [ $# -ne 1 ]; then
	echo "Error : Arguments misssing"
	echo "Format : print [filename]"
else
	grep -v "UNIX" $1>__tmp_000.tmp
	cp __tmp_000.tmp $1
fi