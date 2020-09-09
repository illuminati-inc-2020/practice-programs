#! /bin/bash

if [ $# -lt 1 ]
then
	read -p "Enter filename : " file
else
	file=$1
fi
choice=1
while [ $choice -ne 0 ]
do
	clear
	echo "1. Insert"
	echo "2. Delete"
	echo "3. Print"
	echo "4. Sort by name"
	echo "5. Sort by roll"
	echo "0. Exit"
	read -p "Enter your choice_" choice
	echo 
	case $choice in
		"1")	read -p "Name : " name
			read -p "Roll : " roll
			read -p "Marks : " marks
			echo "$name:$roll:$marks">>$file
			;;
		"2")	read -p "Name : " name
			grep -v "^$name:[^:]*:[^:]*$" $file>$file.tmp
			cp $file.tmp $file
			rm $file.tmp
			;;
		"3")	cat $file|sed "s/:/\t/g"
			echo
			read -p "press any key..."
			;;
		"4")	sort -t ":" -k 1 $file>$file.tmp
			cp $file.tmp $file
			rm $file.tmp
			;;
		"5")	sort -n -t ":" -k 2 $file>$file.tmp
			cp $file.tmp $file
			rm $file.tmp
			;;
		"0")	;;
		*)
			echo "wrong choice"
			;;
	esac
done
