/*	Author	:	RAKESH MALIK
 *	Date	:	03.11.2010 - 04.11.2010
 *	Subject	:	Various operations using date
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct {
	int dd,mm,yyyy;
} date;

char d[7][10]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
char m[12][10]={"January","February","March","April","May","June","July","August","September","October","November","December"};

char isleapyear(int y);    		 	/* Returns 1 if an year is leapyear else 0 */
void copy_date(date *s,date d);			/* Copies date s to date d */
void incr_date(date *d);    	  		/* Increments a date by 1 day */
char comp_date(date d1,date d2);		/* Returns -1 if d1<d2
						 * 	    0 if d1=d2
						 *	    1 if d1>d2 */
char getdate(date *d); 				/* Reads a date from STDIN in dd:mm:yyyy format
			 			 * Returns 1 on success and 0 on failure */
void putdate(date d);				/* Prints a date in "1st January, 2010" form */
char day(date dd);    				/* Returns the day a given date */
long long int diff(date d1,date d2);		/* Retuns differance between d1 & d2 in days */

int main()
{
	date d1,d2,temp;
	int dm,dw;
	int x,choice=1;
	printf("\nEnter a date1 (dd:mm:yyyy) : ");
	while(!getdate(&d1))
		printf("\nEnter a valid date : ");
	printf("%s",d[day(d1)]);
	printf("\nEnter a date2 (dd:mm:yyyy) : ");
	while(!getdate(&d2))
		printf("\nEnter a valid date : ");
	printf("%s",d[day(d2)]);
	if(comp_date(d1,d2)>0)
	{
		copy_date(&temp,d1);
		copy_date(&d1,d2);
		copy_date(&d2,temp);
	}
	printf("\nDifferance is : %d days",diff(d1,d2));
	printf("\nEnter a day of month (1-31) : ");
	scanf("%d",&dm);
	printf("\nEnter a day of week (1-7 for Sunday-Saturday) : ");
	scanf("%d",&dw);
	for(d1;comp_date(d1,d2)<=0;incr_date(&d1))
		if(d1.dd==dm && day(d1)==dw-1)
		{
			putdate(d1);
			printf(" %s\n",d[day(d1)]);
		}
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

char day(date dd)
{
	date temp,init={1,1,1};
	short x=1;
	for(copy_date(&temp,init);comp_date(dd,temp)!=0;incr_date(&temp))
		x=(x+1)%7;
	return x;
}

long long int diff(date d1,date d2)
{
	date temp;
	int x=0;
	for(copy_date(&temp,d1);comp_date(temp,d2)!=0;incr_date(&temp))	x++;
	return x;
}
