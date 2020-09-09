#include <fstream>
#include <iostream>

using namespace std;

main()
{
	ofstream out("x");
	if(out==false)
	{
		cout<<"Write error";
		return 0;
	}
	out<<1<<" "<<2<<" "<<3;
	out.close();
}
