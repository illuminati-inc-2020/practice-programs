/*
formatted I/O
1. by setting or unsetting format flags (By using ios members)
2. Using I/O manipulator (iomanip header file)
(SCHIELDT page 512-513,522-523)
*/


#include <iostream>

using namespace std;

main()
{
	cout.setf(ios::left);
	cout.width(50);
	cout.fill('~');
	cout.precision(6);
	cout<<01.23456789<<endl;
	cout.setf(ios::hex,ios::basefield);
	cout<<100<<endl;
}
