/* Author		:	Rakesh Malik
 * Date 		:	30/07/2011
 * Subject		:	NFA to DFA
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

enum logic{FALSE,TRUE};

typedef struct NFA
{
	int nstates;
	int nsymbols;
	char *alpha;
	char ***state_table;
	char *final;
}NFA;
typedef struct DFA
{
	int nstates;
	int nsymbols;
	char *alpha;
	int **state_table;
	char *final;
}DFA;

NFA* getNFA(const char *);
void printNFA(NFA *);
DFA* NFAtoDFA(NFA *);
void printDFA(DFA *);

int main(int argc,char *argv[])
{
	NFA *nfa;
	DFA *dfa;
	nfa=getNFA(argv[1]);
	printNFA(nfa);
	dfa=NFAtoDFA(nfa);
	printDFA(dfa);
}

void printNFA(NFA *nfa)
{
	int i,j,k;
	for(i=0;i<nfa->nsymbols;i++)
		printf("\t%c",nfa->alpha[i]);
	printf("\n>");
	for(i=0;i<nfa->nstates;i++)
	{
		printf("q%d",i);
		if(nfa->final[i]==1)
			printf("*");
		for(j=0;j<nfa->nsymbols;j++)
		{
			printf("\t{");
			for(k=0;k<nfa->nstates;k++)
				if(nfa->state_table[i][j][k]==1)
					printf("q%d ",k);
			printf("}");
		}
		printf("\n ");
	}
}

void printDFA(DFA *dfa)
{
	int i,j,k;
	for(i=0;i<dfa->nsymbols;i++)
		printf("\t%c",dfa->alpha[i]);
	printf("\n>");
	for(i=0;i<dfa->nstates;i++)
	{
		printf("q%d",i);
		if(dfa->final[i]==1)
			printf("*");
		for(j=0;j<dfa->nsymbols;j++)
			printf("\tq%d",dfa->state_table[i][j]);
		printf("\n ");
	}
}

NFA* getNFA(const char *fname)
{
	int i,j,k;
	char c,buf[10];
	NFA *nfa=(NFA*)malloc(sizeof(NFA));
	FILE *fp;
	if((fp=fopen(fname,"r"))==NULL)
	{
		fprintf(stderr,"ERROR : File read error\n");
		exit(0);
	}
	for(nfa->nsymbols=0;(c=getc(fp))!='\n';)
		if(!isspace(c))	
			nfa->nsymbols++;
	for(nfa->nstates=0;(c=getc(fp))!=EOF;nfa->nstates++)
		while((c=getc(fp))!=EOF && c!='\n');
	rewind(fp);
	nfa->alpha=(char*)calloc(sizeof(char),nfa->nsymbols);
	nfa->state_table=(char***)calloc(sizeof(char**),nfa->nstates);
	for(i=0;i<nfa->nstates;i++)
	{
		nfa->state_table[i]=(char**)calloc(sizeof(char*),nfa->nsymbols);
		for(j=0;j<nfa->nsymbols;j++)
			nfa->state_table[i][j]=(char*)calloc(sizeof(char),nfa->nstates);
	}
	nfa->final=(char*)calloc(sizeof(char),nfa->nstates);
	for(i=0;i<nfa->nsymbols;)
		if(!isspace(c=getc(fp)))
			nfa->alpha[i++]=c;
	while(getc(fp)!='\n');
	for(i=0;i<nfa->nstates;i++)
		for(j=0;j<nfa->nsymbols;j++)
		{
			while((c=getc(fp))!='{')
				if(c=='*') nfa->final[i]=1;
			while(c!='}')
			{
				memset(buf,'\0',10);
				for(k=0;isdigit(c=getc(fp));k++)
					buf[k]=c;
				if(k>0) nfa->state_table[i][j][atoi(buf)]=1;
			}
		}
	fclose(fp);
	return nfa;
}

DFA* NFAtoDFA(NFA *nfa)
{
	int i,j,k,l,new_state,null_set,x,y;
	DFA *dfa;
	char **state_map;
	dfa=(DFA*)malloc(sizeof(DFA));
	dfa->nsymbols=nfa->nsymbols;
	dfa->alpha=(char*)calloc(sizeof(char),dfa->nsymbols);
	dfa->state_table=(int**)calloc(sizeof(int*),pow(2,nfa->nstates));
	for(i=0;i<pow(2,nfa->nstates);i++)
		dfa->state_table[i]=(int*)calloc(sizeof(int),dfa->nsymbols);
	dfa->final=(char*)calloc(sizeof(char),pow(2,nfa->nstates));
	for(i=0;i<nfa->nsymbols;i++)
		dfa->alpha[i]=nfa->alpha[i];
	state_map=(char**)calloc(sizeof(char*),pow(2,nfa->nstates));
	for(i=0;i<pow(2,nfa->nstates);i++)
		state_map[i]=(char*)calloc(sizeof(char),nfa->nstates);
	state_map[0][0]=1;				/* Initialized with Q0->[q0] */
	dfa->nstates=1;					/* dfa has a single state Q0 */
	for(l=0;l<dfa->nstates;l++)			/* loop for evaluating state Ql in dfa */		
	{
		null_set=TRUE;
		for(i=0;i<nfa->nstates;i++)
		{
			if(state_map[l][i]==1)			/* qi belongs to Ql */
			{
				null_set=FALSE;
				for(j=0;j<nfa->nsymbols;j++)		
				{
					new_state=TRUE;
					for(k=0;k<nfa->nstates;k++)
					{
						dfa->state_table[l][j]=dfa->nstates;
						state_map[dfa->nstates][k] |= nfa->state_table[i][j][k];
					}
					for(k=0;k<dfa->nstates;k++)
						if(memcmp(state_map[dfa->nstates],state_map[k],nfa->nstates)==0)
						{
							memset(state_map[dfa->nstates],0,nfa->nstates);
							dfa->state_table[l][j]=k;
							new_state=FALSE;
							break;
						}
					if(new_state)
					{
						for(k=0;k<nfa->nstates;k++)
							if(state_map[dfa->nstates][k]==1 && nfa->final[k]==1)
							{
								dfa->final[dfa->nstates]=1;
								break;
							}
						dfa->nstates++;
					}
				}
					for(x=0;x<dfa->nstates;x++)
					{
						printf("q%d = [",x);
						for(y=0;y<nfa->nstates;y++)
							if(state_map[x][y]==1)
								printf("q%d ",y);
						printf("]\n");
					}
					printf("\n");
			}
		}
		if(null_set)
			for(j=0;j<nfa->nsymbols;j++)
				dfa->state_table[l][j]=l;
	}
	printf("\nstate map table\n");
	for(i=0;i<dfa->nstates;i++)
	{
		printf("q%d = [",i);
		for(j=0;j<nfa->nstates;j++)
			if(state_map[i][j]==1)
				printf("q%d ",j);
		printf("]\n");
	}
	for(i=0;i<pow(2,nfa->nstates);i++)
		free(state_map[i]);
	free(state_map);
	return dfa;
}
