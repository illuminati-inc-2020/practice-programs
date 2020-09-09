/**
 * Author			:	Rakesh Malik
 * Date				:	24/07/2012
 * Subject			:	Generic Queue Class
 * Assignment no.	:	
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "..\myexception.h"
#include <iomanip>

using namespace std;
using namespace exception;

template <class DT> class Queue {
	DT *buf;
	int rear;
	int length;
public:
	Queue(const Queue<DT>&);
	Queue(int);
	~Queue();
	bool isFull();
	bool isEmpty();
	void enqueue(DT);
	DT dequeue();
	int getLength();
	int getNumberOfElements();
	void display();
	void clear();
};
template <class DT> Queue<DT>::Queue(const Queue<DT>& q) {
	Queue::length=q.length;
	Queue::front=q.front;
	Queue::rear=q.rear;
	Queue::buf=new DT[q.length];
	for(int i=0;i<q.length;i++)
		Queue::buf[i]=q.buf[i];
}
template <class DT> Queue<DT>::Queue(int length=0) {
	if(length>=0)
	{
		Queue::length=length;
		Queue::buf=new DT[length];
	}
	else
	{
		Queue::length=0;
		Queue::buf=new DT[0];
	}
	Queue::rear=-1;
}
template <class DT> Queue<DT>::~Queue() {
	delete Queue::buf;
}
template <class DT> bool Queue<DT>::isFull() {
	return Queue::rear==Queue::length-1;
}
template <class DT> bool Queue<DT>::isEmpty() {
	return Queue::rear==-1;
}
template <class DT> void Queue<DT>::enqueue(DT e) {
	if(!Queue::isFull()){
		Queue::rear++;
		Queue::buf[Queue::rear]=e;
	}
	else
		throw QueueFullException();
}
template <class DT> DT Queue<DT>::dequeue() {
	if(!Queue::isEmpty())
	{
		int e=Queue::buf[0];
		for(int i=0; i<Queue::rear; i++)
			Queue::buf[i]=Queue::buf[i+1];
		Queue::rear--;
		return e;
	}
	else
		throw QueueEmptyException();
}
template <class DT> int Queue<DT>::getLength() {
	return Queue::length;
}
template <class DT> int Queue<DT>::getNumberOfElements() {
	return Queue::rear+1;
}
template <class DT> void Queue<DT>::clear() {
	Queue::rear=-1;
}
template <class DT> void Queue<DT>::display() {
	for(int i=0; i<=length; i++)
		cout<<"------";
	cout<<"-"<<endl;
	for(int i=0; i<=rear; i++)
		cout<<"|"<<setw(5)<<buf[i]<<" ";
	for(int i=rear+1; i<length; i++)
		cout<<"|      ";
	cout<<"|"<<endl;
	for(int i=0; i<=length; i++)
		cout<<"------";
	cout<<"-"<<endl;
}
main() {
	Queue<int> q(5);
	int choice=1,e;
	char msg[50]="";
	while(choice) {
		system("cls");
		cout<<"Queue"<<endl
			<<endl
			<<"1.Insert"<<endl
		    <<"2.Delete"<<endl
		    <<"0.Exit"<<endl
			<<endl;
		q.display();
		cout<<msg<<endl
			<<endl
			<<"Enter your choice_";
		cin>>choice;
		cout<<endl;
		switch(choice) {
		case 0:
			return 0;
		case 1:
			if(q.isFull())
				sprintf(msg, "Queue is full");
			else {
				cout<<"Enter an element : ";
				cin>>e;
				q.enqueue(e);
				sprintf(msg, "%d Inserted", e);
			}
			break;
		case 2:
			try {
				sprintf(msg, "%d Deleted", q.dequeue());
			}catch(QueueEmptyException ex) {
				sprintf(msg, "Queue is empty");
			}
			break;
		default:
			sprintf(msg, "Wrong choice");
		}
	}
}
