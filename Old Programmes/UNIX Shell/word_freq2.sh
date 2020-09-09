cat $1|sed 's/ /\n/g;s/\t/\n/g'|tr -s '\n'|sort|uniq -c
