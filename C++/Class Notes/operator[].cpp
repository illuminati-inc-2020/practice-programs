#include <iostream>

using namespace std;

class Array {
	int size;
	int *buf;
public:
	Array(int);
	int getSize();
	int& operator[](int);
};
Array::Array(int size) {
	if(size>0) {
		try{
			Array::buf=new int[size];
			for(int i=0; i<size; i++)
				Array::buf[i]=0;
			Array::size=size;
		}catch(bad_alloc e) {
			cerr<<"Error : 'bad_alloc' exception during Array allocation"<<endl;
		}
	}
	else
		throw size;//Invalid array size exception
}
int Array::getSize() {
	return Array::size;
}
int& Array::operator[](int index) {
	if(index>=0 && index<Array::size)
		return Array::buf[index];
	else
		throw index;//Invalid array index exception
}

main()
{
	Array a(10);
	try{
		a[0]=1;
		a[1]=2;
		a[2]=3;
		a[20]=500;
	}catch(int index) {
		cout<<"invalid index "<<index<<endl;
	}
	for(int i=0; i<a.getSize(); i++)
		cout<<a[i]<<",";
	cout<<endl;
}
