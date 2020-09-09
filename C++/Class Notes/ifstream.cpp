#include <fstream>
#include <iostream>

using namespace std;

main()
{
	ifstream in("x");
	if(in==false)
	{
		cout<<"Read error";
		return 0;
	}
	for(int i=0;!in.eof();i++)
	{
		int a;
		in.read((char*)&a,sizeof(int));
		cout<<a<<" ";
		in.close();
	}
	in.close();
}
