/**
 * Author			:	Rakesh Malik
 * Date				:	24/07/2012
 * Sublect			:	Generic Stack Class
 * Assignment no.	:	
 */

#include <iostream>
#include "../myexception.h"
#include <cstdlib>
#include <iomanip>
#include <cstdio>

using namespace std;
using namespace exception;

template <class DT> class Stack {
	DT *buf;
	int top;
	int length;
public:
	Stack(const Stack<DT>&);
	Stack(int);
	~Stack();
	bool isOverflowed();
	bool isUnderflowed();
	void push(DT);
	DT pop();
	int getLength();
	int getNumberOfElements();
	void clear();
	void display();
};
template <class DT> Stack<DT>::Stack(const Stack<DT>& s) {
	Stack::length=s.length;
	Stack::top=s.top;
	Stack::buf=new DT[s.length];
	for(int i=0;i<=s.top;i++)
		Stack::buf[i]=s.buf[i];
}
template <class DT> Stack<DT>::Stack(int length=0) {
	if(length>=0) {
		Stack::length=length;
		try {
			Stack::buf=new DT[length];
		}catch(bad_alloc) {
			cerr<<"Error : 'bad_alloc' exception during Stack allocation"<<endl;
		}
	}else {
		Stack::length=0;
		try {
			Stack::buf=new DT[0];
		}catch(bad_alloc) {
			cerr<<"Error : 'bad_alloc' exception during Stack allocation"<<endl;
		}
	}
	Stack::top=-1;
}
template <class DT> Stack<DT>::~Stack() {
	delete Stack::buf;
	Stack::length=0;
	Stack::top=-1;
}
template <class DT> bool Stack<DT>::isOverflowed() {
	return Stack::top>=Stack::length-1;
}
template <class DT> bool Stack<DT>::isUnderflowed() {
	return Stack::top<0;
}
template <class DT> void Stack<DT>::push(DT e) {
	if(!Stack::isOverflowed())
		Stack::buf[++Stack::top]=e;
	else
		throw StackOverflowException();
}
template <class DT> DT Stack<DT>::pop() {
	if(!Stack::isUnderflowed())
		return Stack::buf[Stack::top--];
	else
		throw StackUnderflowException();
}
template <class DT> int Stack<DT>::getLength() {
	return Stack::length;
}
template <class DT> int Stack<DT>::getNumberOfElements() {
	return Stack::top+1;
}
template <class DT> void Stack<DT>::clear() {
	top=-1;
}
template <class DT> void Stack<DT>::display() {
	for(int i=0; i<=length; i++)
		cout<<"------";
	cout<<"-"<<endl;
	for(int i=0; i<=top; i++)
		cout<<"|"<<setw(5)<<buf[i]<<" ";
	for(int i=top+1; i<length; i++)
		cout<<"|      ";
	cout<<"|"<<endl;
	for(int i=0; i<=length; i++)
		cout<<"------";
	cout<<"-"<<endl;
}

main() {
	Stack<int> s(5);
	int choice=1,e;
	char msg[50]="";
	while(choice) {
		system("cls");
		cout<<"STACK"<<endl
			<<endl
			<<"1.Push"<<endl
		    <<"2.Pop"<<endl
		    <<"0.Exit"<<endl
			<<endl;
		s.display();
		cout<<msg<<endl
			<<endl
			<<"Enter your choice_";
		cin>>choice;
		cout<<endl;
		switch(choice) {
		case 0:
			return 0;
		case 1:
			if(s.isOverflowed())
				sprintf(msg, "Stack is overflowing");
			else {
				cout<<"Enter an element : ";
				cin>>e;
				s.push(e);
				sprintf(msg, "%d Pushed", e);
			}
			break;
		case 2:
			try {
				sprintf(msg, "%d Popped", s.pop());
			}catch(StackUnderflowException ex) {
				sprintf(msg, "Stack is underflowing");
			}
			break;
		default:
			sprintf(msg, "Wrong choice");
		}
	}
}
