/*	Author	:	RAKESH MALIK
 *	Date	:	03.11.2010 - 04.11.2010
 *	Subject	:	Various operations using date
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

typedef struct {
	int dd,mm,yyyy;
} date;

char isleapyear(int y);     	/* Returns 1 if an year is leapyear else 0 */
void copy_date(date *s,date d);		/* Copies date s to date d */
void incr_date(date *d);    	  	/* Increments a date by 1 day */
void decr_date(date *d);      		/* Decrements a date by 1 day */
char comp_date(date d1,date d2);	/* Returns -1 if d1<d2
					 * 	    0 if d1=d2
					 *	    1 if d1>d2 */
char getdate(date *d); 	/* Reads a date from STDIN in dd:mm:yyyy format
			 * Returns 1 on success and 0 on failure */
void putdate(date d);	/* Prints a date in "1st January, 2010" form */
char* day(date dd);     /* Returns the day string of a given date */
long long int diff(date d1,date d2,date *d3);
		/* Retuns differance between d1 & d2 in days and
		 * places differance in year:month:day in d3 */

int main()
{
	date d1,d2,d3,temp;
	int x,choice=1;
	clrscr();
	for(x=0;x==0;)
	{
		printf("\n\nEnter a date (dd:mm:yyyy) : ");
		x=getdate(&d1);
	}
	while(choice)
	{
		clrscr();
		printf("\nDate :\t");
		putdate(d1);
		printf("\nDay  :\t%s",day(d1));
		printf("\n\n\t1.  Change date");
		printf("\n\t2.  Calculate differance with another date");
		printf("\n\t0.  Quit");
		printf("\n\n\t\tEnter your choice_");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("\n\nEnter new date (dd:mm:yyyy) : ");
				if(getdate(&d2))
				{
					copy_date(&d1,d2);
					printf("\n\nDate changed, Press any key_");
				}
				break;
			case 2:
				printf("\n\nEnter another date (dd:mm:yyyy) : ");
				if(getdate(&d2))
				{
					printf("\nDate :\t");
					putdate(d2);
					printf("\nDay  :\t%s",day(d2));
					printf("\n\nDifferrance :\t%lld day(s)",(comp_date(d1,d2)<=0)?diff(d1,d2,&d3):diff(d2,d1,&d3));
					printf(" or %d year(s) %d month(s) %d day(s)",d3.yyyy,d3.mm,d3.dd);
				}
				break;
			case 0:
				printf("\n\nPress any key to quit_");
				break;
			default:
				fprintf(stderr,"\nWrong choice!");
				break;
		}
		getch();
	}
	return 0;
}

char getdate(date *d)
{
	char invalid_date(date);
		/* Returns 1 if a date is invalid, else 0 */
	char invalid_string(char*);
		/* Returns 1 if a input string is invalid, else 0 */
	char *i=calloc(1,15),*_i=i;
	scanf("%s",i);
	if(invalid_string(i))
	{
		fprintf(stderr,"invalid input pattern!\n");
		return 0;
	}
	else
	{
		for(d->dd=d->mm=d->yyyy=0;isdigit(*i);i++)
		{
			d->dd*=10;
			d->dd+=*i-'0';
		}
		for(i++;isdigit(*i);i++)
		{
			d->mm*=10;
			d->mm+=*i-'0';
		}
		for(i++;isdigit(*i);i++)
		{
			d->yyyy*=10;
			d->yyyy+=*i-'0';
		}
	}
	free(_i);
	if(invalid_date(*d) )
	{
		fprintf(stderr,"invalid date!\n");
		return 0;
	}
	return 1;
}
char invalid_date(date d)
{
	char diny[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	char dily[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	if(d.yyyy<=0 || d.mm>12 || d.mm<=0 || d.dd<=0) return 1;
	else if(isleapyear(d.yyyy) && d.dd>dily[d.mm-1]) return 1;
	else if(!isleapyear(d.yyyy) && d.dd>diny[d.mm-1]) return 1;
	else return 0;
}
char invalid_string(char *s)
{
	char temp;
	if(!isdigit(*s)) return 1;
	while(isdigit(*s)) s++;
	if(*s!=':' && *s!='/' && *s!='.') return 1;
	temp=*s;
	for(s++;isdigit(*s);s++);
	if(*s!=temp) return 1;
	for(s++;isdigit(*s);s++);
	if(*s!='\0') return 1;
	return 0;
}

void putdate(date d)
{
	char *m[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	printf("%d",d.dd);
	if(d.dd==1 || d.dd==21 || d.dd==31) printf("st");
	else if(d.dd==2 || d.dd==22) printf("nd");
	else if(d.dd==3 || d.dd==23) printf("rd");
	else printf("th");
	printf(" %s, %4.4d",m[d.mm-1],d.yyyy);
}

char comp_date(date d1,date d2)
{
	if(d1.yyyy>d2.yyyy) return 1;
	else if(d1.yyyy<d2.yyyy) return -1;
	else if(d1.mm>d2.mm) return 1;
	else if(d1.mm<d2.mm) return -1;
	else if(d1.dd>d2.dd) return 1;
	else if(d1.dd<d2.dd) return -1;
	else return 0;
}

void copy_date(date *d,date s)
{
	d->dd=s.dd;
	d->mm=s.mm;
	d->yyyy=s.yyyy;
}

char isleapyear(int y)
{
	return y%4?0:y%100?1:y%400?0:1;
}

void incr_date(date *d)
{
	char diny[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	char dily[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	if(isleapyear(d->yyyy))
		if(d->dd<dily[d->mm-1])	d->dd++;
		else
		{
			d->dd=1;
			if(d->mm<12) d->mm++;
			else
			{
				d->mm=1;
				d->yyyy++;
			}
		}
	else
		if(d->dd<diny[d->mm-1]) d->dd++;
		else
		{
			d->dd=1;
			if(d->mm<12) d->mm++;
			else
			{
				d->mm=1;
				d->yyyy++;
			}
		}
}

void decr_date(date *d)
{
	char diny[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	char dily[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	if(isleapyear(d->yyyy))
		if(d->dd>1) d->dd--;
		else
		{
			if(d->mm>1) d->mm--;
			else
			{
				d->mm=12;
				d->yyyy--;
			}
			d->dd=dily[d->mm-1];
		}
	else
		if(d->dd>1) d->dd--;
		else
		{
			if(d->mm>1) d->mm--;
			else
			{
				d->mm=12;
				d->yyyy--;
			}
			d->dd=diny[d->mm-1];
		}
}

char* day(date dd)
{
	char *d[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	date temp,init={1,1,1};
	short x=1;
	for(copy_date(&temp,init);comp_date(dd,temp)!=0;incr_date(&temp))
		x=(x+1)%7;
	return d[x];
}

long long int diff(date d1,date d2,date *d3)
{
	long long int _x,x=0L;
	char i,days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	date temp;
	d3->dd=d3->mm=d3->yyyy=0;
	for(copy_date(&temp,d1);comp_date(temp,d2)!=0;incr_date(&temp))	x++;
	for(i=d1.mm-1,_x=x;_x>=days[i];i=(i+1)%12)
	{
		_x-=(i==1 && isleapyear(d1.yyyy+d3->yyyy))?29:days[i];
		d3->mm++;
		if(d3->mm==12)
		{
			d3->mm=0;
			d3->yyyy++;
		}
	}
	d3->dd=_x;
	return x;
}