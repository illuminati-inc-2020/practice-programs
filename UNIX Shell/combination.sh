#! /bin/bash

comb ()
{
	x=${*:3}
	if [ ${#1} -lt $2 ]; then
		for i in $x
		do
			param="$1$i"
			comb $param $2 $x
		done
	else
		echo "$1"
	fi
}

comb "" ${*:1:1} ${*:2}
