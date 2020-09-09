#include <iostream>
#include <iomanip>

using namespace std;

main()
{
	cout<<hex<<100<<endl;
	cout<<setw(20)<<setfill('~')<<left<<dec<<100<<endl;
	bool x=true;
	cout<<boolalpha<<x<<endl;
}
