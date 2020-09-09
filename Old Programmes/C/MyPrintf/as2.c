/*	ASSIGNMENT 2
 *	Author : Rakesh Malik
 *	Date : 19.09.2010
 *	B.Sc. Computer Science 2nd Year
 *	Printf function without using header stdio.h
 */
#include<stdlib.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdarg.h>
#include<ctype.h>
#include"myctype.h"
#include<string.h>

void Putchar(char);
int Puts(const char*);
int Printf(const char*,...);

int main()
{
	int i=-12345;
	long long int lli=1234567891234564321LL;
	float f=123.499;
	double d=123456789.123456789;
	unsigned int ui=111222333;
	long long unsigned int llui=9998887776665550LLU;
	char* s="Hello World";
	char c='c';

	Printf("================================================\n");
	Printf("%30s\n","OUTPUT");
	Printf("================================================\n");
	Printf("int\t\t\t%d\n\t\t\t%.10d\n\t\t\t:%20.15d:\n",i,i,-i);
	Printf("long long int\t\t%lld\n",lli);
	Printf("unsigned int\t\t%u\n\t\t\t%u\n",ui,&i);
	Printf("long long unsigned int\t%llu\n",llui);
	Printf("------------------------------------------------\n");
	Printf("float\t\t\t%f\n\t\t\t%.2f\n",f,f);
	Printf("double\t\t\t%lf\n\t\t\t:%-30.15lf:\n",d,d);
	Printf("------------------------------------------------\n");
	Printf("string\t\t\t:%s:\n\t\t\t:%15.7s:\n",s,s);
	Printf("\t\t\t:%-*.*s:\n",20,10,"HAVE A NICE DAY");
	Printf("------------------------------------------------\n");
	Printf("char\t\t\t%c\n\t\t\t:%5c:\n",c,c);
	Printf("------------------------------------------------\n");
}

int Printf(const char* fmt,...)
{
	char* adjust(char*,char*,char,int,int);
				//adjust() function adjusts a string by the left adjustment,field width,maximum characters
	int j=0;		//'j' counts charcters printed
	char left_adj;		//'left adj' flag indicates left adjustment is to be done for variable
	int field_width;	//'field width' holds field width for a variablewhen printing
	int max_chars;		/*'max_chars' holds : 
				 * 	number of charcters to be printed for a string from left
				 *	number of digits to be printed after decimal point
				 *	number of digits to be printed for an integer adjusted by preceeding 0s */
	char *buffer1=(char*)calloc(1,100),*buffer2=(char*)calloc(1,100);
				//buffers are used to transfer string to or from functions
	va_list arg;
	va_start(arg,fmt);
	while(*fmt)
	{
		left_adj=0;
		field_width=max_chars=-1;	//'field_width' or 'max_chars' = -1 denotes default string adjustment
		if(*fmt=='%')
		{
			fmt++;
							//Reading left/right adjustment flag
			if(*fmt=='-')
			{
				left_adj=1;
				fmt++;
			}
							//Reading minimum field width:
			if(*fmt=='*')					//Variable
			{
				field_width=va_arg(arg,int);
				fmt++;
			}
			else						//Constant
				if(isdigit(*fmt))
				{
					field_width=0;
					while(isdigit(*fmt))
					{
						field_width*=10;
						field_width+=*fmt-'0';
						fmt++;
					}
				}
							//Reading number of maximum characters:
			if(*fmt=='.')
			{
				fmt++;
				if(*fmt=='*')				//Variable
				{
					max_chars=va_arg(arg,int);
					fmt++;
				}
				else					//Constant
				{
					if(isdigit(*fmt))
					{
						max_chars=0;
						while(isdigit(*fmt))
						{
							max_chars*=10;
							max_chars+=*fmt-'0';
							fmt++;
						}
						}
				}
			}
							//Printing Variables
			switch(*fmt)
			{
				case 'c':				//Character
					buffer1[0]=va_arg(arg,int);
					buffer1[1]='\0';
					j+=Puts(adjust(	buffer1,
							buffer2,
							left_adj,field_width,-1));
					j++;
					break;
				case 'd':				//Decimal Integer
				case 'i':				
					j+=Puts(adjust(	itoa(	buffer1,
								va_arg(arg,int),
								max_chars),
							buffer2,
							left_adj,field_width,-1));
					break;
				case 'f':				//Float
					j+=Puts(adjust(	ftoa(	buffer1,
								va_arg(arg,double),
								(max_chars>=0)?max_chars:6),
							buffer2,
							left_adj,field_width,-1));
					break;
				case 's':				//String
					j+=Puts(adjust(	va_arg(arg,char*),
							buffer1,
							left_adj,field_width,max_chars));
					break;
				case 'u':				//Unsigned int
					j+=Puts(adjust(	itoa(	buffer1,
								va_arg(arg,unsigned int),
								max_chars),
							buffer2,
							left_adj,field_width,-1));
					break;
				case 'l':			//Long...
					fmt++;
					switch(*fmt)
					{
						case 'i':			//Long int
						case 'd':
							j+=Puts(adjust(	itoa(	buffer1,
										va_arg(arg,int),
										max_chars),
									buffer2,
									left_adj,field_width,-1));
							break;
						case 'u':			//Long unsigned int
							j+=Puts(adjust(	itoa(	buffer1,
										va_arg(arg,long unsigned int),
										max_chars),
									buffer2,
									left_adj,field_width,-1));
							break;
						case 'f':			//Double
							j+=Puts(adjust(	ftoa(	buffer1,
										va_arg(arg,double),
										(max_chars>=0)?max_chars:6),
									buffer2,
									left_adj,field_width,-1));
							break;
						case 'l':			//Long long...
							fmt++;
							switch(*fmt)
							{
								case 'i':		//Long long int
								case 'd':
									j+=Puts(adjust(	itoa(	buffer1,
												va_arg(arg,long long int),
												max_chars),
											buffer2,
											left_adj,field_width,-1));
									break;
								case 'u':		//Long long unsigned int 
									j+=Puts(adjust(	llutoa(	buffer1,
												va_arg(arg,long long unsigned int),
												max_chars),
											buffer2,
											left_adj,field_width,-1));
									break;
								default:
									putchar(*fmt);
									j++;
									break;
							}
							break;
						default:
							putchar(*fmt);
							j++;
							break;
					}
					break;
				default:
					Putchar(*fmt);
					j++;
					break;
			}
		}
		else					//Printing constant characters
		{
			Putchar(*fmt);
			j++;
		}
		fmt++;
	}
	va_end(arg);
	free(buffer1);
	free(buffer2);
	return j;
}

void Putchar(char c)
{
	char s[1];
	s[0]=c;
	write(1,s,1);
}

int Puts(const char *s)
{
	int i=0;
	while(s[i++]);
	write(1,s,--i);
	return i;
}

char* adjust(char* s,char* d,char left_adj,int field_width,int max_chars)
{
	int i,j,len=strlen(s);
	max_chars=(len>max_chars && max_chars>=0)?max_chars:len;
	field_width=(len<field_width && field_width>=0)?field_width:len;
	d[field_width]='\0';
	for(i=0,j=0;i<field_width;i++)
		d[i]=(!left_adj) ? ((i<field_width-max_chars)?' ':s[j++]) : ((i>=max_chars)?' ':s[j++]);
	return d;
}
