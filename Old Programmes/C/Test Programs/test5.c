#include<stdio.h>
struct ch
{
	char a[3];
};
struct str
{
	struct ch v;
	short m;
};
int main()
{
	printf("\n%d\n\n",sizeof(struct str));
}
