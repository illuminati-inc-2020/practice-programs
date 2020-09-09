#!/bin/bash

for z in `last|grep "still logged in"|tr -s " "|cut -d " " -f 1,6|tr " " "%"`
do
	z=(`echo $z|tr "%" " "`)
	x=`date -d ${z[1]} +%s`
	y=`date +%s`
	sec=`expr $y - $x`
	echo ${z[0]} `expr $sec / 3600`:`expr \( $sec / 60 \) % 60`:`expr $sec % 60`
done
