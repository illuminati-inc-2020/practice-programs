#include<stdio.h>

void least_square(double[],double[],int);
void solve_linear_eq_2(double,double,double,double,double,double,double*,double*);
void solve_linear_eq_3(double,double,double,double,double,double,double,double,double,double,double,double,double*,double*,double*);

int main()
{
	int n,i;
	double x[100],y[100];
	printf("LEAST SQUARE METHOD FOR CURVE FITTING :\n\n");
	printf("Enter number of data : ");
	scanf("%d",&n);
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("Enter value of x%d : ",i+1);
		scanf("%lf",&x[i]);
		printf("Enter value of y%d : ",i+1);
		scanf("%lf",&y[i]);
	}
	printf("\n\n x :\t");
	for(i=0;i<n;i++)
		printf("%g\t",x[i]);
	printf("\n y :\t");
	for(i=0;i<n;i++)
		printf("%g\t",y[i]);
	least_square(x,y,n);
}

void least_square(double x[],double y[],int n)
{
	double s1=0,s2=0,s3=0,s4=0,s01=0,s11=0,s21=0,a,b,c;
	int i;
	for(i=0;i<n;i++)
	{
		s1+=x[i];
		s2+=x[i]*x[i];
		s3+=x[i]*x[i]*x[i];
		s4+=x[i]*x[i]*x[i]*x[i];
		s01+=y[i];
		s11+=x[i]*y[i];
		s21+=x[i]*x[i]*y[i];
	}
	printf("\n\ns1=%g\ns2=%g\ns3=%g\ns4=%g\ns01=%g\ns11=%g\ns21=%g",s1,s2,s3,s4,s01,s11,s21);
	solve_linear_eq_2(n,s1,-s01,
			  s1,s2,-s11,
			  &a,&b);
	printf("\n\nThe linear curve to the data is :\n\tf(x)=(%g)+(%g)x",a,b);
	solve_linear_eq_3(n,s1,s2,-s01,
			  s1,s2,s3,-s11,
			  s2,s3,s4,-s21,
			  &a,&b,&c);
	printf("\n\nThe quardratic curve to the data is :\n\tf(x)=(%g)+(%g)x+(%g)x2",a,b,c);
}

void solve_linear_eq_2(	double a1,double b1,double c1,
			double a2,double b2,double c2,
			double *x,double *y)
/* Solves 2 linear equations of form :
		a1*x+b1*y+c1=0     ... (1)
		a2*x+b2*y+c2=0	   ... (2) */
{
	*x=-(c1*b2-c2*b1)/(a1*b2-a2*b1);
	*y= (c1*a2-c2*a1)/(a1*b2-a2*b1);
}

void solve_linear_eq_3(	double a1,double b1,double c1,double d1,
			double a2,double b2,double c2,double d2,
			double a3,double b3,double c3,double d3,
			double *x,double *y,double *z)
/* Solves 2 linear equations of form :
		a1*x+b1*y+c1*z+d1=0     ... (1)
		a2*x+b2*y+c2*z+d2=0     ... (2)
		a3*x+b3*y+c3*z+d3=0	... (3) */
{
	solve_linear_eq_2(b2*a1/a2-b1,c2*a1/a2-c1,d2*a1/a2-d1,
			  b3*a1/a3-b1,c3*a1/a3-c1,d3*a1/a3-d1,
			  y,z);
	*x=-(b2**y+c2**z+d2)/a2;
}