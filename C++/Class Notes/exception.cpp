#include <iostream>

using namespace std;

void fnc()
{
	int x;
	cin>>x;
	if(x==1)
		throw 10;
	else if(x==2)
		throw 10.0;
	else if(x==3)
		throw "abc";
}

main()
{
	try
	{
		fnc();
	}
	catch(int i)
	{
		cout<<i<<"int exception"<<endl;
	}
	catch(double i)
	{
		cout<<i<<"double exception"<<endl;
	}
	catch(...)
	{
		cout<<"uncaught exception"<<endl;
	}
}
