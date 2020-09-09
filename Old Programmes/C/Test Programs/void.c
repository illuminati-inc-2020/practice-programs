# include<stdio.h>

int main()
{
   int choice;
   int i=0,j,b[5];
   char c[5];
   float t[5];
   void *a[5];
   while(i<5)
   	{
   	 printf("press 1. enter integer 2.enter character 3.float");
  	 scanf("%d",&choice);
  	 switch(choice)
   	{
		case 1:
		   printf("enter the number");
	   	   scanf("%d",&b[i]);
		   a[i]=&b[i];
	   	   break;
		case 2:
		   printf("enter the character");
		   scanf("%c",&c[i]);
		   scanf("%c",&c[i]);
		   a[i]=&c[i];
		   break;
       	        case 3:
		   printf("enter the float");
		   scanf("%f",&t[i]);
		   a[i]=&t[i];
		   break;

   	  }
 	i++;	 
        }
  for(i=0;i<5;i++)
  {
			if(a[i]==&c[i])
		  		 printf("%c\n",c[i]);
			if(a[i]==&b[i])
		  		 printf("%d\n",b[i]);
			if(a[i]==&t[i])
		   		printf("%f\n",t[i]);
  }


				
		

}

