#include <iostream>

using namespace std;

class Test
{
	int i;
public:
	Test(){}
	Test(int);
	int get_i();
	void set_i(int);
friend	Test operator++(Test&);
friend	Test operator++(Test&,int);
};
Test::Test(int i)
{
	Test::i=i;
}
int Test::get_i()
{
	return Test::i;
}
void Test::set_i(int i)
{
	Test::i=i;
}
Test operator++(Test &x)
{
	x.i++;
	return x;
}
Test operator++(Test &x,int i)
{
	Test y=x;
	x.i++;
	return y;
}
main()
{
	Test ob1=10,ob2,ob3;
	ob2=ob1++;
	cout<<"oi1 "<<ob1.get_i()<<endl;
	cout<<"ob2 "<<ob2.get_i()<<endl;
	ob3=++ob1;
	cout<<"ob1 "<<ob1.get_i()<<endl;
	cout<<"ob3 "<<ob3.get_i()<<endl;
}
