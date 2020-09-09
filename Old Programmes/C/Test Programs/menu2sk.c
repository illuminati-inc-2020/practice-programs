#include<stdio.h>

typedef struct options
{
	char *name;
	void (*f)();
}
opt;

list *X;

int main()
{
	void ins(),del(),src(),disp(),save(),load(),quit();
	opt option[]={{"insert",&ins},{"delete",&del},{"search",&src},{"display",&disp},{"save",&save},{"load",&load}};
	
}
	
int ins()
{
	void ins_end(),ins_beg();
	opt option[]={{"insert",&ins},{"delete",&del},{"search",&src},{"display",&disp},{"save",&save},{"load",&load}};
}

void menu(char*header,char*tailer,char len,opt op[])
{
	puts(header);
	int i;
	for(i=0;i<len;i++)
	{
		printf("\n%d. %s",i+1,op[i].name);
	}
	int choice;
	printf("Enter ur choice_");
	scanf("%d",choice);
	
}

ins_end()
{
}
ins_beg()
{
}