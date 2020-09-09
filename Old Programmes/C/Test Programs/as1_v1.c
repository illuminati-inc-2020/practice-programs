#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"menu.h"
#include"linkedlist.h"

list *X;		//Linked list
char opened=0;		//Flag, indicates a file is opened when set to nonzero
char filename[20];	//Name of opened file

void ins_menu(void),del_menu(void),disp_menu(void),search_menu(void),save(void),load(void);

int main()		//MAIN MENU
{
	X=createlist(X);
	menu("LINKED LIST","Quit",6,"Insert","Delete","Display","Search","Save","Load",&ins_menu,&del_menu,&disp_menu,&search_menu,&save,&load);
}

void ins_menu(void)		//INSERT MENU
{
	void ins_beg(void),ins_end(void),ins_any(void);
	menu("LINKED LIST\n\n>Insert","Back to main menu",3,"At beginning","At end","At any point",&ins_beg,&ins_end,&ins_any);
}
void del_menu(void)		//DELETE MENU
{
	void del_beg(void),del_end(void),del_any(void);
	menu("LINKED LIST\n\n>delete","Back to main menu",3,"At beginning","At end","At any point",&del_beg,&del_end,&del_any);
}
void disp_menu(void)		//DISPLAY MENU
{
	void full_disp(void),part_disp(void);
	menu("LINKED LIST\n\n>Display","Back to main menu",2,"Full","Partially",&full_disp,&part_disp);
}
void search_menu(void)		//SEARCH MENU
{
	void src_data(void),src_pos(void);
	menu("LINKED LIST\n\n>Search","Back to main menu",2,"By data","By position",&src_data,&src_pos);
}

void save(void)			//SAVE LINKED LIST INTO A NEW FILE
{
	node *temp;
	FILE *fp;
	printf("Enter a file name : ");
	scanf("%s",filename);
	fp=fopen(filename,"wb");
	if(fp==NULL || ferror(fp))
	{
		fprintf(stderr,"\nFile write error");
		return;
	}
	for(temp=*(X->head);temp;temp=temp->next)
		fwrite(&(temp->data),sizeof(int),1,fp);
	fclose(fp);
	printf("Linked list saved to file \"%s\"\n",filename);
	sleep(3);
}
void load(void)			//LOAD LINKED LIST FROM A FILE
{
	int temp;
	FILE *fp;
	char tempname[20];
	printf("Enter a file name : ");
	scanf("%s",tempname);
	fp=fopen(tempname,"rb");
	if(fp==NULL || ferror(fp))
	{
		fprintf(stderr,"\nFile read error");
		sleep(2);
		return;
	}
	bzero(filename,20);
	strcpy(filename,tempname);
	while(X->len)
		del(X,X->len);
	while(!feof(fp))
	{
		fread(&temp,sizeof(int),1,fp);
		ins(X,temp,X->len);
	}
	del(X,X->len);										/* ??? */
	opened=1;
	fclose(fp);
	printf("Linked list loaded from file \"%s\"\n",filename);
	sleep(3);
}

void ins_beg(void)		//Insert at beginning
{
	int data;
	printf("Enter an integer data : ");
	scanf("%d",&data);
	ins(X,data,0);
}
void ins_end(void)		//Insert at end
{
	int data;
	printf("Enter an integer data : ");
	scanf("%d",&data);
	ins(X,data,X->len);
}
void ins_any(void)		//Insert at any point
{
	int data,index;
	printf("Enter an integer data : ");
	scanf("%d",&data);
	printf("Enter the index : ");
	scanf("%d",&index);
	if(index<0 || index>X->len)
	{
		fprintf(stderr,"Wrong index entered");
		sleep(2);
		return;
	}
	ins(X,data,index);
}

void del_beg(void)		//Delete at beginning
{
	del(X,0);
}
void del_end(void)		//Delete at end
{
	del(X,X->len);
}
void del_any(void)		//Delete at any point
{
	int index;
	printf("Enter the index : ");
	scanf("%d",&index);
	if(index<1 || index>X->len)
	{
		fprintf(stderr,"Wrong index entered");
		return;
	}
	del(X,index);
}

void full_disp(void)		//Display full linked list
{
	print(*X,1,X->len);
	getchar();
	getchar();
	fflush(stdin);
}
void part_disp(void)		//Display linked list partly
{
	int lb,ub;
	printf("Enter lower bound : ");
	scanf("%d",&lb);
	printf("Enter upper bound : ");
	scanf("%d",&ub);
	print(*X,lb,ub);
	getchar();
	getchar();
	fflush(stdin);
}

void src_data(void)		//Search a data in linked list
{
	int data;
	printf("Enter an integer data to be searched : ");
	scanf("%d",&data);
	linear_search(*X,data);
	getchar();
	getchar();
	fflush(stdin);
}
void src_pos(void)		// Search data in linked list by position
{
	node *temp;
	int pos,i;
	printf("Enter an index to be searched : ");
	scanf("%d",&pos);
	for(temp=*(X->head),i=1;temp && i<pos;temp=temp->next,i++);
	if(i==pos)
		printf("Index %d found with data %d",pos,temp->data);
	else
		printf("Data not found");
	getchar();
	getchar();
	fflush(stdin);
}
