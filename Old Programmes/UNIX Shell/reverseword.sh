awk '
BEGIN{
	FS=" "
}
{
	for(i=1;i<=NF;i++)
	{
		l=split($i,r,"")
		for(j=l;j>=0;j--)
			printf r[j]
		printf " "
	}
	printf "\n"
}
' $1
