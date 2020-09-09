# Any base to any base convertion
#!/bin/bash

if [ $# -ne 3 ]; then
	echo "argument missing"
	echo "change_base [number] [ibase] [obase]"
else
	num=$1
	ibase=$2
	obase=$3

	# Calculating decimal
	dec=0
	pow=1;
	for (( i=${#num}-1 ; i>=0 ; i-- ))
	do
		dig=${num:$i:1}
		case $dig in
			A) dig=10;;
			B) dig=11;;
			C) dig=12;;
			D) dig=13;;
			E) dig=14;;
			F) dig=15;;
		esac
		if [ $dig -ge $ibase ]; then
			echo "invalid input"
			exit;
		fi
		let "dec=dec+($dig*$pow)"
		let "pow=$pow*$ibase"
	done
	
	# Calculating obase
	num=""
	for (( ; dec>0 ; ))
	do
		let "dig=$dec%$obase"
		case $dig in
			10) dig=A;;
			11) dig=B;;
			12) dig=C;;
			13) dig=D;;
			14) dig=E;;
			15) dig=F;;
		esac
		let "dec=$dec/$obase"
		num=$dig$num
	done
	echo $num
fi
