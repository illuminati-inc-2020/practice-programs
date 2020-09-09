/* Overloading (Polymorphism) */

#include <iostream>
#include <cstring>

using namespace std;

int add(int x,int y)
{
	return x+y;
}

char* add (char* s1,char* s2)
{
	char *t;
	t=new char[strlen(s1)+strlen(s2)+1];
	strcpy(t,s1);
	strcat(t,s2);
	return t;
}

main()
{
	int i=10,j=20;
	char *s1,*s2;
	s1=new char[100];
	s2=new char[100];
	strcpy(s1,"hello");
	strcpy(s2,"world");
	cout << add(i,j) << endl
	     << add(s1,s2) << endl;
	delete s1;
	delete s2;
}
