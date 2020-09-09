#!/bin/bash

if [ $# -eq 1 ]
then
	temp=`cat $1`
	echo "`grep -c "" $1` `sed 's/ /\n/g;s/\t/\n/g' $1|tr -s '\n'|grep -c ""` ${#temp}  $1"
else
	case $1 in
		"-l")	echo `grep -c "" $2` $2
			;;
		"-w")	echo `sed 's/ /\n/g;s/\t/\n/g' $2|tr -s '\n'|grep -c ""` $2
			;;
		"-c")	temp=`cat $2`
			echo ${#temp} $2
			;;
	esac
fi

