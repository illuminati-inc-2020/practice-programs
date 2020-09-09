#include <iostream>

using namespace std;

template <typename T> void swapValue(T &x, T &y) {
	T z=x;
	x=y;
	y=z;
}

double knapsack(int n, int w[], int v[], int W, double x[]) {
	for(int i=0; i<n; i++)
		x[i]=0.0;
	double r[n], value=0.0;
	for(int i=0; i<n; i++)
		r[i]=(double)v[i]/(double)w[i];
	for(int i=0; i<n-1; i++)
		for(int j=0; j<n-i-1; j++)
			if(r[j]<r[j+1]) {
				swapValue(r[j], r[j+1]);
				swapValue(v[j], v[j+1]);
				swapValue(w[j], w[j+1]);
			}
	for(int i=0; i<n; i++) {
		if(w[i]<=W) {
			x[i]=1.0;
			W-=w[i];
			value+=v[i];
		} else {
			x[i]=(double)W/(double)w[i];
			value+=x[i]*(double)v[i];
			break;
		}
	}	
	return value;
}

int main() {
	int n;
	cout<<"Enter number of elements : ";
	cin>>n;
	int w[n], v[n], W;
	double x[n], value;
	cout<<"Enter values : ";
	for(int i=0; i<n; i++)
		cin>>v[i];
	cout<<"Enter weights : ";
	for(int i=0; i<n; i++)
		cin>>w[i];
	cout<<"Enter capacity of sack : ";
	cin>>W;
	value=knapsack(n, w, v, W, x);
	cout<<endl
		<<"After sorting..."<<endl
		<<"Value vector : \t";
	for(int i=0; i<n; i++)
		cout<<"\t"<<v[i];
	cout<<endl
		<<"Weight vector : ";
	for(int i=0; i<n; i++)
		cout<<"\t"<<w[i];
	cout<<endl
		<<endl
		<<"Ouput vector : \t";
	for(int i=0; i<n; i++)
		cout<<"\t"<<x[i];
	cout<<endl
		<<"Total value = "<<value<<endl;
}