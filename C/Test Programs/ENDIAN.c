# include <stdio.h>
int main () 
{ 
	int i ;
	i = 0X1A2B3C4D ;
	printf("\n\nARCHITECTURE :\n\t");
	if ( ( char ) i == 0X1A ) 
		printf ( "Little ENDIAN\n" ) ;
	else if ( ( char ) i == 0X2B || ( char ) i == 0X3B ) 
		printf (  "Middle ENDIAN\n" ) ;
	else if ( ( char ) i == 0X4D ) 
		printf ( "Big ENDIAN\n" ) ;
	printf("\t%d bit\n\n",sizeof(int)*8);
} 
