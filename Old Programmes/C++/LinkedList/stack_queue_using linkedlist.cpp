#include <iostream>
#include "../myexception.h"

using namespace std;
using namespace exception;

class IndexOutOfBoundsException:public Exception {
public :
	IndexOutOfBoundsException():Exception(100, "Linked list index out of bounds"){}
};
class StackUnderflowException:public Exception {
public :
	StackUnderflowException():Exception(200, "Stack underflow"){}
};
class QueueEmptyException:public Exception {
public :
	QueueEmptyException():Exception(300, "Queue empty"){}
};

template<class DT> class Node {
	DT data;
	Node *next;
public:
	Node(DT, Node*);
	DT& getData();
	Node* getNext();
	void setNext(Node*);
};
template<class DT> Node<DT>::Node(DT data, Node* next=NULL) {
	Node<DT>::data=data;
	Node<DT>::next=next;
}
template<class DT> DT& Node<DT>::getData() {
	return Node<DT>::data;
}
template<class DT> Node<DT>* Node<DT>::getNext() {
	return Node<DT>::next;
}
template<class DT> void Node<DT>::setNext(Node<DT>* next) {
	Node<DT>::next=next;
}

template<class DT> class LinkedList {
	int length;
	Node<DT> *head;
public:
	LinkedList();
	int getLength();
	Node<DT>* getHead();
	LinkedList<DT>& insert(DT, int);
	LinkedList(LinkedList<DT>&);
	DT remove(int);
	DT& operator[](int);
	void clear();
	~LinkedList();
	void reverse();
};
template<class DT> LinkedList<DT>::LinkedList() {
	LinkedList<DT>::length=0;
	LinkedList<DT>::head=NULL;
}
template<class DT> int LinkedList<DT>::getLength() {
	return LinkedList<DT>::length;
}
template<class DT> Node<DT>* LinkedList<DT>::getHead() {
	return LinkedList<DT>::head;
}
template<class DT> LinkedList<DT>& LinkedList<DT>::insert(DT data,int index) {
	if(index<0 || index>LinkedList<DT>::length)
		throw IndexOutOfBoundsException();
	Node<DT> *temp=LinkedList<DT>::head;
	if(index==0)
		LinkedList<DT>::head=new Node<DT>(data, LinkedList<DT>::head);
	else {
		for(int i=0;i<index-1;i++)
			temp=temp->getNext();
		Node<DT> *newnode=new Node<DT>(data, temp->getNext());
		temp->setNext(newnode);
	}
	LinkedList::length++;
	return *this;
}
template<class DT> LinkedList<DT>::LinkedList(LinkedList<DT> &l) {
	LinkedList<DT>::length=0;
	LinkedList<DT>::head=NULL;
	for(int i=0;i<l.length;i++) {
		LinkedList::insert(l[i], LinkedList::length);
	}
}
template<class DT> DT LinkedList<DT>::remove(int index) {
	DT data;
	if(index<0 || index>=LinkedList<DT>::length)
		throw IndexOutOfBoundsException();
	if(index==0) {
		Node<DT> *temp=LinkedList<DT>::head->getNext();
		data=head->getData();
		delete LinkedList<DT>::head;
		LinkedList<DT>::head=temp;
	}
	else {
		Node<DT> *temp=LinkedList<DT>::head;
		for(int i=0;i<index-1;i++)
			temp=temp->getNext();
		Node<DT> *oldnode=temp->getNext();
		temp->setNext(oldnode->getNext());
		data=oldnode->getData();
		delete oldnode;
	}
	LinkedList<DT>::length--;
	return data;
}
template<class DT> DT& LinkedList<DT>::operator[](int index) {
	if(index<0 || index>=LinkedList<DT>::length)
		throw IndexOutOfBoundsException();
	Node<DT> *temp=LinkedList<DT>::head;
	for(int i=0;i<index;i++)
		temp=temp->getNext();
	return temp->getData();
}
template<class DT> void LinkedList<DT>::clear() {
	while(LinkedList::length>0)
		LinkedList::remove(0);
}
template<class DT> LinkedList<DT>::~LinkedList() {
	LinkedList::clear();
}
template<class DT> void LinkedList<DT>::reverse() {
	LinkedList<DT> l;
	while(LinkedList::getLength()>0)
		l.insert(LinkedList::remove(0), 0);
	while(l.getLength()>0)
		LinkedList::insert(l.remove(0), LinkedList::getLength());
}
template<class DT> ostream& operator<<(ostream &os, LinkedList<DT> l) {
	os<<"{";
	for(Node<int> *temp=l.getHead();temp!=NULL;temp=temp->getNext()) {
		os<<temp->getData();
		if(temp->getNext()!=NULL)
			os<<",";
	}
	os<<"}";
	return os;
}

template<class DT> class Stack:public LinkedList<DT> {
public:
	Stack& push(DT);
	DT pop();
	bool isUnderflowed();
	void clear();
};
template<class DT> Stack<DT>& Stack<DT>::push(DT data) {
	Stack<DT>::insert(data, Stack<DT>::getLength());
	return *this;
}
template<class DT> DT Stack<DT>::pop() {
	if(Stack<DT>::getLength()==0)
		throw StackUnderflowException();
	DT temp=(*this)[Stack<DT>::getLength()-1];
	Stack<DT>::remove(Stack<DT>::getLength()-1);
	return temp;
}
template<class DT> bool Stack<DT>::isUnderflowed() {
	return Stack<DT>::getLength()==0;
}
template<class DT> void Stack<DT>::clear() {
	while(Stack<DT>::getLength()>0)
		Stack<DT>::remove(0);
}

template<class DT> class Queue:public LinkedList<DT> {
public:
	Queue& enqueue(DT);
	DT dequeue();
	bool isEmpty();
	void clear();
};
template<class DT> Queue<DT>& Queue<DT>::enqueue(DT data) {
	Queue<DT>::insert(data, Queue<DT>::getLength());
	return *this;
}
template<class DT> DT Queue<DT>::dequeue() {
	if(Queue<DT>::getLength()==0)
		throw QueueEmptyException();
	DT temp=(*this)[0];
	Queue<DT>::remove(0);
	return temp;
}
template<class DT> bool Queue<DT>::isEmpty() {
	return Queue<DT>::getLength()==0;
}
template<class DT> void Queue<DT>::clear() {
	while(Queue<DT>::getLength()>0)
		Queue<DT>::remove(0);
}

main() {
	cout<<"LinkedList"<<endl;
	LinkedList<int> l;
	l.insert(1,0);
	l.insert(2,1);
	l.insert(3,1);
	l.insert(4,0);
	cout<<l<<endl;
	l.remove(1);
	cout<<l<<endl;
	cout<<"Stack"<<endl;
	Stack<int> s;
	s.push(1).push(2).push(3);
	cout<<s<<endl;
	cout<<s.pop()<<endl;
	cout<<s<<endl;
	cout<<"Queue"<<endl;
	Queue<int> q;
	q.enqueue(1).enqueue(2).enqueue(3);
	cout<<q<<endl;
	cout<<q.dequeue()<<endl;
	cout<<q<<endl;
}
