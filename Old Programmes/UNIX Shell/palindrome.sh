#!/bin/bash

temp=$*
while [ ! "$temp" = "" ]
do
	rev=${temp:0:1}$rev
	temp=${temp:1}
done
if [ "$*" = "$rev" ]
then
	echo "Palindrome"
else
	echo "Not Palindrome"
fi
