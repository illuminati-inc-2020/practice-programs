#include <iostream>

using namespace std;

main()
{
	int x=1,y=0,z;
	try{
		z=x/y;
	}
	catch(...)
	{
		cout<<"Exception"<<endl;
	}
}
