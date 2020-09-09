# Assingment no.     : 5a
# Aim                : To evaluate a valid postfix expression with operators +,-,*,/ and $(exponentiation).

#! /bin/bash

if [ $# -eq 0 ]; then
	echo "Error : Argument missing"
else
	top=-1
	for token in $*
	do
		case $token in
			"-"|"+"|"*"|"/")
				temp=${stack[$top]}
				top=`expr $top - 1`
				let "stack[$top]=${stack[$top]}$token$temp"
				;;
			"$")
				temp=${stack[$top]}
				top=`expr $top - 1`
				let "stack[$top]=`echo "${stack[$top]} ^ $temp"|bc`"
				;;
			*)
				top=`expr $top + 1`
			       	let "stack[$top]=$token"
				;;
		esac
	done
	echo "${stack[0]}"
fi
