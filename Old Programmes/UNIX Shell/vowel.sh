temp=`cat $1|tr -c -d '[aeiou]'`
echo ${#temp}

