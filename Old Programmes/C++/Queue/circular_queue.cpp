/**
 * Author			:	Rakesh Malik
 * Date				:	24/07/2012
 * Subject			:	Generic Circular Queue Class
 * Assignment no.	:	
 */

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include "..\myexception.h"

using namespace std;
using namespace exception;

template <class DT> class CircularQueue {
	DT *buf;
	int front,rear;
	int length;
public:
	CircularQueue(const CircularQueue<DT>&);
	CircularQueue(int);
	~CircularQueue();
	bool isFull();
	bool isEmpty();
	void enqueue(DT);
	DT dequeue();
	int getLength();
	int getNumberOfElements();
	void display();
	void clear();
};
template <class DT> CircularQueue<DT>::CircularQueue(const CircularQueue<DT>& q) {
	CircularQueue::length=q.length;
	CircularQueue::front=q.front;
	CircularQueue::rear=q.rear;
	CircularQueue::buf=new DT[q.length];
	for(int i=0;i<q.length;i++)
		CircularQueue::buf[i]=q.buf[i];
}
template <class DT> CircularQueue<DT>::CircularQueue(int length=0) {
	if(length>=0)
	{
		CircularQueue::length=length;
		CircularQueue::buf=new DT[length];
	}
	else
	{
		CircularQueue::length=0;
		CircularQueue::buf=new DT[0];
	}
	CircularQueue::front=-1;
	CircularQueue::rear=-1;
}
template <class DT> CircularQueue<DT>::~CircularQueue() {
	delete CircularQueue::buf;
}
template <class DT> bool CircularQueue<DT>::isFull() {
	return CircularQueue::rear!=-1 && CircularQueue::rear%CircularQueue::length==(CircularQueue::front+CircularQueue::length)%CircularQueue::length;
}
template <class DT> bool CircularQueue<DT>::isEmpty() {
	return CircularQueue::rear==-1 && CircularQueue::front==-1;
}
template <class DT> void CircularQueue<DT>::enqueue(DT e) {
	if(!CircularQueue::isFull()){
		CircularQueue::rear=(CircularQueue::rear+1)%CircularQueue::length;
		CircularQueue::buf[CircularQueue::rear]=e;
	}
	else
		throw QueueFullException();
}
template <class DT> DT CircularQueue<DT>::dequeue() {
	if(!CircularQueue::isEmpty())
	{
		CircularQueue::front=(CircularQueue::front+1)%CircularQueue::length;
		DT e=CircularQueue::buf[CircularQueue::front];
		if(CircularQueue::front==CircularQueue::rear)
		{
			CircularQueue::front=-1;
			CircularQueue::rear=-1;
		}
		return e;
	}
	else
		throw QueueEmptyException();
}
template <class DT> int CircularQueue<DT>::getLength() {
	return CircularQueue::length;
}
template <class DT> int CircularQueue<DT>::getNumberOfElements() {
	return CircularQueue::front-CircularQueue::rear;
}
template <class DT> void CircularQueue<DT>::clear() {
	CircularQueue::front=-1;
	CircularQueue::rear=-1;
}
template <class DT> void CircularQueue<DT>::display() {
for(int i=0; i<=length; i++)
		cout<<"------";
	cout<<"-"<<endl;
	if(front<rear || front==-1) {
		for(int i=0; i<=front; i++)
			cout<<"|      ";
		for(int i=front+1; i<=rear; i++)
			cout<<"|"<<setw(5)<<buf[i]<<" ";
		for(int i=rear+1; i<length; i++)
			cout<<"|      ";
	} else {
		for(int i=0; i<=rear; i++)
			cout<<"|"<<setw(5)<<buf[i]<<" ";
		for(int i=rear+1; i<=front; i++)
			cout<<"|      ";
		for(int i=front+1; i<length; i++)
			cout<<"|"<<setw(5)<<buf[i]<<" ";
	}
	cout<<"|"<<endl;
	for(int i=0; i<=length; i++)
		cout<<"------";
	cout<<"-"<<endl;
}
main() {
	CircularQueue<int> q(5);
	int choice=1,e;
	char msg[50]="";
	while(choice) {
		system("cls");
		cout<<"Circular Queue"<<endl
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
				sprintf(msg, "Circular Queue is full");
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
				sprintf(msg, "Circular Queue is empty");
			}
			break;
		default:
			sprintf(msg, "Wrong choice");
		}
	}
}
