#include <iostream>

using namespace std;

//Generalized
template <class X,class Y>
X add(X x,Y y)
{
	return x+(X)y;
}

//Specialized
string add(string x,string y)
{
	return x+" "+y;
}

main()
{
	int ix=10,iy=20;
	float fx=22.22,fy=33.33;
	string sx="Rakesh",sy="Malik";
	cout<<add(ix,fy)<<endl
	    <<add(fx,iy)<<endl
	    <<add(sx,sy)<<endl;
}
