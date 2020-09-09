# Assingment no.     : 5b
# Aim                : To evaluate a valid infix expression with operators +,-,*,/ and $ and also containing parenthesis types (),{},[].

#! /bin/bash

if [ $# -eq 0 ]; then
	echo "Error : Argument missing"
else
	# Infix to Postfix conversion
	top=-1
	for token in $*
	do
		case $token in
		"+"|"-")
			for (( ; top>-1 ; ))
			do
				case ${stack[$top]} in	
				"+"|"-"|"*"|"/"|"$")
					postfix="$postfix ${stack[$top]}"
					top=`expr $top - 1`
					;;
				*)	break
					;;
				esac
			done
			top=`expr $top + 1`
			stack[$top]=$token
			;;
		"*"|"/")
			for (( ; top>-1 ; ))
			do
				case ${stack[$top]} in	
				"*"|"/"|"$")	
					postfix="$postfix ${stack[$top]}"
					top=`expr $top - 1`
					;;
				*)	break
					;;
				esac
			done
			top=`expr $top + 1`
			stack[$top]=$token
			;;
		"$")	for (( ; top>-1 ; ))
			do
				case ${stack[$top]} in	
				"$")	postfix="$postfix ${stack[$top]}"
					top=`expr $top - 1`
					;;
				*)	break
					;;
				esac
			done
			top=`expr $top + 1`
			stack[$top]=$token
			;;
		"("|"{"|"[")
			top=`expr $top + 1`
			stack[$top]=$token
			;;
		")")	for (( ; top>-1 ; ))
			do
				token=${stack[$top]}
				top=`expr $top - 1`
				case $token in	
				"(")	break
					;;
				*)	postfix="$postfix $token"
					;;
				esac

			done
			;;
		"}")	for (( ; top>-1 ; ))
			do
				token=${stack[$top]}
				top=`expr $top - 1`
				case $token in	
				"{")	break
					;;
				*)	postfix="$postfix $token"
					;;
				esac
			done
			;;
		"]")	for (( ; top>-1 ; ))
			do
				token=${stack[$top]}
				top=`expr $top - 1`
				case $token in	
				"[")	break
					;;
				*)	postfix="$postfix $token"
					;;
				esac
			done
			;;
		*)	postfix="$postfix $token"
			;;
		esac
	done
	for (( ; top>-1 ; ))
	do
		postfix="$postfix ${stack[$top]}"
		top=`expr $top - 1`
	done

	# Evaluating Prefix
	top=-1
	for token in $postfix
	do
		case $token in
			"-"|"+"|"*"|"/")
				temp=${stack[$top]}
				top=`expr $top - 1`
				stack[$top]=`expr ${stack[$top]} $token $temp`
				;;
			"$")
				temp=${stack[$top]}
				top=`expr $top - 1`
				stack[$top]=`echo "${stack[$top]} ^ $temp"|bc`
				;;
			*)
				top=`expr $top + 1`
			       	stack[$top]=$token
				;;
		esac
	done
	echo "${stack[0]}"
fi
