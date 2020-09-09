#include <iostream>

using namespace std;

template <class X>
class Test
{
	X i;
public :
	Test(){}
	Test(X);
	X get_i();
	Test<X> operator+(Test<X> x);
};

template<class X> 
Test<X>::Test(X i)
{
	Test<X>::i=i;
}
template<class X> 
X Test<X>::get_i()
{
	return Test<X>::i;
}
template<class X> 
Test<X> Test<X>::operator+(Test<X> x)
{
	Test<X> y;
	y.i=Test<X>::i+x.i;
	return y; 
}

template<class X>
X add(X x, X y)
{
	return x+y;
}

main()
{
	Test<int> ai,bi=10,ci=20;
	ai=bi+ci;	
	cout<<ai.get_i()<<endl;
	Test<float> af,bf=10.11,cf=20.22;
	af=bf+cf;	
	cout<<af.get_i()<<endl;
	Test<string> as,bs=(string)"rakesh",cs=(string)"malik";
	as=bs+cs;	
	cout<<as.get_i()<<endl;
	add(10,20);
}
