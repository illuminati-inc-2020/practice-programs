#include <stdio.h>
#include <wn.h>

main()
{
	int i,ps;
	char s[100],*pos[]={"NOUN","VERV","ADJECTIVE","ADVERV"};
	printf("%d",bit(ADV));
	printf("Give word: ");
	gets(s);
	wninit();
	ps=in_wn(s,ALL_POS);
	for(i=NOUN;i<=ADV;i++)
	{
		if(!(ps&bit(i)))continue;
		SynsetPtr ssptr=findtheinfo_ds(s,i,SIMPTR,ALLSENSES);
		printf("===============> %s\n",pos[i-1]);
		while(ssptr!=NULL)
		{
			puts(ssptr->defn);
			ssptr=ssptr->nextss;
		}
		puts("-------------------------------------");
	}
}
