#include <iostream>

using namespace std;

main()
{
	try
	{
		int m;
		cout<<"Give size of the array : ";
		cin>>m;
		int *a=new int[m];
		for(int i=0;i<m;i++)
		{
			cout<<"a["<<i<<"] = ";
			cin>>a[i];
		}
		cout<<"The array is : ";
		for(int i=0;i<m;i++)
			cout<<a[i]<<" ";
		delete a;
	}
	catch(bad_alloc e)
	{
		cout<<"Invalid size"<<endl;
	}
}
