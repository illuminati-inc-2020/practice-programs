#include <iostream>

using namespace std;

template <class X>
X add(X x,X y)
{
	return x+y;
}

main()
{
	int ix=10,iy=20;
	float fx=22.22,fy=33.33;
	string sx="Rakesh",sy="Malik";
	cout<<add(ix,iy)<<endl;
	cout<<add(fx,fy)<<endl;
	cout<<add(sx,sy)<<endl;
}
