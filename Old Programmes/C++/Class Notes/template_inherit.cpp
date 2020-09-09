#include <iostream>

using namespace std;

template <class Type>
class Base
{
	Type i;
public:
	Base(){}
	Base(Type);
	Type get_i();
};
template<class Type> 
Base<Type>::Base(Type i)
{
	Base<Type>::i=i;
}
template<class Type> 
Type Base<Type>::get_i()
{
	return Base<Type>::i;
}

template<class Type>
class Derived1:public Base<Type>
{
public:
	Derived1(Type);
};
template <class Type>
Derived1<Type>::Derived1(Type i):Base<Type>(i){}

class Derived2:public Base<int>
{
public:
	Derived2(int);
};
Derived2::Derived2(int i):Base<int>(i){}

main()
{
	Derived1<int> a=20;
	cout<<a.get_i()<<endl;
	Derived2 b=30;
	cout<<b.get_i()<<endl;
}
