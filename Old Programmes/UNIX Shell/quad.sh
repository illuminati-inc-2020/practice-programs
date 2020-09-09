# Assignment no : 6
# Aim           : Write a shell script to read 4 vertices (x,y) of a polygon an to find out whether the polygon is a square,rectangle or a parallelogram.

#! /bin/bash

if [ $# -ne 8 ]; then
	echo "Error : Argument missing"
	echo "Format : rect [x1] [y1] [x2] [y2] [x3] [y3] [x4] [y4]"
else
	x1=$1	y1=$2	x2=$3	y2=$4	x3=$5	y3=$6	x4=$7	y4=$8
	let "a12=($x1-$x2)*($x1-$x2)+($y1-$y2)*($y1-$y2)";
	let "a23=($x2-$x3)*($x2-$x3)+($y2-$y3)*($y2-$y3)";
	let "a34=($x3-$x4)*($x3-$x4)+($y3-$y4)*($y3-$y4)";
	let "a41=($x4-$x1)*($x4-$x1)+($y4-$y1)*($y4-$y1)";
	let "a13=($x1-$x3)*($x1-$x3)+($y1-$y3)*($y1-$y3)";
	let "a24=($x2-$x4)*($x2-$x4)+($y2-$y4)*($y2-$y4)";
	if [ $a12 -eq $a34 -a $a23 -eq $a41 ]; then
		if [ $a13 -eq $a24 ]; then
			if [ $a12 -eq $a23 -a $a34 -eq $a41 ]; then
				echo "Square";
			else
				echo "Rectangle"
			fi
		else
			if [ $a12 -eq $a23 -a $a34 -eq $a41 ]; then
				echo "Rhombus";
			else
				echo "Parallelogram"
			fi
		fi
	else
		echo "Unknown"
	fi
fi