# Assignment no. : 10
# Aim            : Write a shell script to count the number of words,spaces,characters, and vowels in a body of text. Also indicate repeated words if any in the text.

#! /bin/bash

if [ $# -ne 1 ]; then
	echo "Error : Arguments misssing"
	echo "Format : wc [filename]"
else
	echo "Number of words : `cat $1|wc -w`"
	echo "Number of characters : `cat $1|wc -c`"
	awk 'BEGIN{
			FS="";
			space=0
			vowel=0;
		}
		{
			for(i=1;i<=NF;i++)
			{
				if(tolower($i) ~ /a|e|i|o|u/)
					vowel++;
				if($i ~ / /)
					space++;
			}
		}
		END{
			print "Number of spaces :",space;
			print "Number of vowels :",vowel;
		}' $1
	echo "Repeated words : "
	cat $1|sed 's/ /\n/g;s/\t/\n/g'|tr -s ' '|sort|uniq -d
fi
