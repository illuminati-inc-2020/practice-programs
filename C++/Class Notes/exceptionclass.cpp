#include <iostream>

using namespace std;

class MyException
{
	int err_no;
	string msg;
public:
	MyException(int,string);
	int getErrorNumber();
	string getMessage();
};
MyException::MyException(int err_no,string msg)
{
	MyException::err_no=err_no;
	MyException::msg=msg;
}
int MyException::getErrorNumber()
{
	return MyException::err_no;
}
string MyException::getMessage()
{
	return MyException::msg;
}

class Overflow:public MyException
{
	public:
	       	Overflow():MyException(100,"Overflow Exception"){}
};
class Underflow:public MyException
{
	public:
	       	Underflow():MyException(200,"Underflow Exception"){}
};

void fnc()
{
	int i;
	cin>>i;
	switch(i)
	{
	case 1:
		throw Overflow();
	case 2:
		throw Underflow();
	}
}

main()
{
	try
	{
		fnc();
	}
	catch(Overflow e)
	{
		cout<<e.getErrorNumber()<<" : "<<e.getMessage()<<endl;
	}
	catch(Underflow e)
	{
		cout<<e.getErrorNumber()<<" : "<<e.getMessage()<<endl;
	}
}
