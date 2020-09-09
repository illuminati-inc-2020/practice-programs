#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 21

struct word
{
	char word[20];
	char category[20];
	short flag;
	short letters;
}
words[MAX]={	{"tiger","animal",0,5},
		{"raven","bird",0,5},
		{"princeton","university",0,9},
		{"abahoman","bengali cinema",0,8},
		{"lagaan","hindi cinema",0,6},
		{"nigeria","country",0,7},
		{"visuvias","volcanic mountain",0,8},
		{"logitech","electronics company",0,8},
		{"hangman","pen & paper game",0,7},
		{"netscape","internet browser",0,8},
		{"tungabhadra","river of india ",0,11},
		{"solaris","OS",0,7},
		{"agastya","indian monk",0,7},
		{"maxwell","scientist",0,7},
		{"bhopal","city of india",0,6},
		{"counterstrike","multiplayer pc game",0,13},
		{"icehockey","outdoor game",0,9},
		{"ajayjadeja","indian cricketer",0,10},
		{"rosemarry","flower",0,9},
		{"wordsworth","poet",0,10},
		{"transistor","electronics",0,8}};

void menu(void);
void play(void);
void printhangman(int);
void save(char[],int,int,int);
int _rand(int);
void highscore(void);

int main()
{
	int j=1;
	FILE *fp;
	while(1)
	{
		menu();
		play();
	}
}

void menu()
{
	while(1)
	{
		system("clear");
		printf("\e[35;1m\n\n\tHANGMAN");
		printf("\n\n\n\n\t\t\e[33;1m1. \e[32;1mNew game\n\n\t\t\e[33;1m2. \e[32;1mHigh scores\n\n\t\t\e[33;1m3. \e[32;1mInstructions\n\n\t\t\e[33;1m4. \e[32;1mExit\n\n\t\e[33;1mEnter your choice_\e[37;1m");
		int choice;
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				return;
			case 2:
				highscore();
				break;
			case 3:
				break;
			case 4:
				exit(EXIT_SUCCESS);
			default:
				break;
		}
	}
}

void play()
{
	int i,j,k,l,hints,flag,wrong,right,attempts=0,success=0,score=0,temp;
	char a[26],*name=(char*)calloc(sizeof(char),3);
	FILE *fp;

	/* Set random sequence generator */

	if(fp=fopen("temp.xxx","rb"))
	{
		fread(&j,sizeof(int),1,fp);
		fclose(fp);
		j=_rand(j);
		fp=fopen("temp.xxx","wb");
		fwrite(&j,sizeof(int),1,fp);
	}
	else
		j=10;
	fclose(fp);

	/* Start Play */		

	for(attempts=0;;attempts++,j=_rand(j))
	{
		fp=fopen("temp.xxx","wb");
		fwrite(&j,sizeof(int),1,fp);
		fclose(fp);
		j=(j<0)?j*-1:j;
		hints=wrong=right=0;
		for(i=0;i<26;i++)
		{
			system("clear");

		/* Print Scores, Attempts, Hangman etc. */

			printf("\n\n\e[34;1mHANGMAN\n-----------------\n\n");
			printf("\n\e[32;1mTotal number of attempts :\e[37;1m %d",attempts);
			printf("\n\e[32;1mNumber of successful attempts :\e[37;1m %d",success);
			printf("\n\e[31;1mScore : \e[37;1m%d",score);
			printf("\n\n\n\e[31;1mCategory : \e[33;1m%s",words[j].category);
			printf("\n\e[32;1mTurn : \e[37;1m%d",i+1);
			printf("\n\e[32;1mLetters tried : \e[33;1m");
			for(k=0;k<i;k++)
				printf("%c,",a[k]);
			printf("\n\e[32;1mWrong letters : \e[37;1m%d \e[32;1m( \e[37;1m%d \e[32;1mremaining )",wrong,8-wrong);
			printf("\n\e[32;1mRight letters : \e[37;1m%d",right);
			printf("\n\n\e[31;1mWord : \e[36;1m");
			for(k=0;words[j].word[k]!='\0';k++)
			{
				flag=0;
				for(l=0;l<i;l++)
					if(words[j].word[k] == a[l])
					{
						flag=1;
						break;
					}
				if(flag==1)
					putchar(words[j].word[k]);
				else
					putchar('_');
				putchar(' ');
			}
			printhangman(wrong);
			if(wrong==8)
			{
				printf("\n\n\e[36;1mThe word is \"%s\"\n",words[j].word);
				sleep(3);
				break;	
			}
	
		/* Taking Input Charcter */

			printf("\n\nEnter a letter between 'A'-'Z' or 'a'-'z'\nOr '0' for back to main menu");
			printf("\n\n\e[33;1mEnter letter_ \e[37;1m");
			a[i]=tolower(getchar());

		/* Quiting options */

			switch(a[i])
			{
				case '0':  //Quit to main menu
					system("clear");
					printf("\n\n1. Save score and quit\n2. Quit\n3. Continue\n\tEnter youir choice _ ");
					scanf("%d",&temp);
					switch(temp)
					{
						case 1:		//Save score & quit
							printf("\nEnter name : ");
							scanf("%s",name);
							name[0]=toupper(name[0]);
							name[1]=toupper(name[1]);
							name[2]=toupper(name[2]);
							name[3]='\0';
							printf("\n\tPlayer Name : %s\n\tScore : %d\n\tTotal Number ofAttempts : %d\n\tNumber of Successful Attempts : %d\n\n\t\t\t...Saved",name,score,attempts,success);
							printf("\n\n\n");
							getchar();getchar();
							save(name,score,attempts,success);
						case 2:		//Only quit
							return;
						default:	//Continue
							break;
					}
					break;
				default:
					break;
			}

		/* Discard repeatative character */

			flag=0;
			for(k=0;k<i;k++)
				if(a[i]==a[k])
					flag=1;
			if(flag==1 || (a[i]<'A' || (a[i]>'Z' && a[i]<'a') || a[i]>'z'))
			{
				i--;
				continue;
			}
			fflush(stdin);

		/* Check if given letter is present in word */

			flag=0;
			for(k=0;words[j].word[k]!='\0';k++)
			{
				if(a[i]==words[j].word[k])
				{
					flag=1;
					right++;
					score+=5;
				}
			}
			if(flag==0)
			{
				score-=5;
				wrong++;
			}

		/* Check if Word is Complete */

			if(right==words[j].letters)
			{
				score+=50;
				success++;
				break;
			}
		}
	}
}

void printhangman(int state)
{
	printf("\e[31;1m");
	switch(state)
	{
		case 0:
			printf("\n\n\n\n\n\n\n\n\n");
			break;
		case 1:
			printf("\n\n\n\n\n\n\n\n\n\t=========");
			break;
		case 2:
			printf("\n\n\t |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t=========");
			break;
		case 3:
			printf("\n\t _____\n\t |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t=========");
			break;
		case 4:
			printf("\n\t _____\n\t |   |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t=========");
			break;
		case 5:
			printf("\n\t _____\n\t |   |\n\t |  ( )\n\t |\n\t |\n\t |\n\t |\n\t |\n\t=========");
			break;
		case 6:
			printf("\n\t _____\n\t |   |\n\t |  ( )\n\t |   |\n\t |   |\n\t |   |\n\t |\n\t |\n\t=========");
			break;
		case 7:
			printf("\n\t _____\n\t |   |\n\t |  ( )\n\t |   |\n\t |  /|\\\n\t |   |\n\t |\n\t |\n\t=========");
			break;
		case 8:
			printf("\n\t _____\n\t |   |\n\t |  ( )\n\t |   |\n\t |  /|\\\n\t |   |\n\t |  / \\\n\t |\n\t=========");
			break;
	}
}

void save(char *name,int score,int attempts,int success)
{
	FILE *fp;
	fp=fopen("highscore","ab");
	fwrite(name,sizeof(char),3,fp);
	fwrite(&score,sizeof(int),1,fp);
	fwrite(&attempts,sizeof(int),1,fp);
	fwrite(&success,sizeof(int),1,fp);
	fclose(fp);
}

void highscore(void)
{
	FILE *fp;
	int tempi,i=0;
	char *tempc=(char*)malloc(3);
	system("clear");
	printf("\e[31;1m\n\n\t\tPlayer\t\t\e[32;1m     \t\tTotal   \tSuccessful");
	printf("\e[31;1m\n\t\tName  \t\t\e[32;1mScore\t\tAttempts\tAttempts\n\n");
	fp=fopen("highscore","rb");
	while(!feof(fp))
	{
		fread(tempc,sizeof(char),3,fp);
		fread(&tempi,sizeof(int),1,fp);
		printf("\t\t\e[31;1m%c%c%c\t\t\e[37;1m%d\t\t",tempc[0],tempc[1],tempc[2],tempi);
		fread(&tempi,sizeof(int),1,fp);
		printf("%d\t\t",tempi);
		fread(&tempi,sizeof(int),1,fp);
		printf("%d\t\n",tempi);
		tempc[0]=tempc[1]=tempc[2]='X';
		tempi=0;
		i++;
		if(i%15==0 && i!=0)
		{
			printf("Press Enter for more");
			getchar();
			getchar();
			fflush(stdin);
		}
	}
	printf("\n\n\n\t\t\t\t\t\t\tPress enter to exit highscores _ ");
	getchar();
	getchar();
}

int _rand(int n)
{
	return (n*n*rand()+n*rand()+rand())%MAX;
}
