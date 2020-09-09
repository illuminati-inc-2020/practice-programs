#include <iostream>
#include <myexception>

using namespace std;
using namespace exception;

class IndexOutOfBoundsException:public Exception {
public :
	IndexOutOfBoundsException():Exception(100, "Linked list index out of bounds"){}
};
class LinkedListEmptyException:public Exception {
public :
	LinkedListEmptyException():Exception(101, "Linked list is empty"){}
};

template<class DT> class Node {
public:
	DT data;
	Node *next;
	Node(DT, Node*);
};
template<class DT> Node<DT>::Node(DT data, Node* next=NULL) {
	Node<DT>::data=data;
	Node<DT>::next=next;
}

template<class DT> class LinkedList {
	int length;
	Node<DT> **head;
public:
	LinkedList(int);
	LinkedList(const LinkedList<DT>&);
	~LinkedList();
	int getLength();
	void insert(int, DT);
	DT remove(int);
	DT& operator[](int);
	DT get(int);
	void set(int, DT);
	void clear();
};
template<class DT> LinkedList<DT>::LinkedList(int size=0) {
	try{
		LinkedList::head=new Node<DT>*;
		*(LinkedList::head)=NULL;
		for(int i=0;i<size; i++) {
			Node<DT> *temp=*(LinkedList::head);
			*(LinkedList::head)=new Node<DT>(NULL, temp);
		}
		LinkedList::length=size;
	} catch(bad_alloc) {
		cerr<<"ERROR : bad_alloc"<<endl;
	}
}
template<class DT> LinkedList<DT>::LinkedList(const LinkedList<DT>& l) {
	try{
		LinkedList::head=new Node<DT>*;
		*(LinkedList::head)=NULL;
		for(Node<DT> *temp1=*(l.head), **temp2=LinkedList::head; temp1!=NULL; temp1=temp1->next, temp2=&((*temp2)->next))
			*temp2=new Node<DT>(temp1->data);
		LinkedList::length=l.length;
	} catch(bad_alloc) {
		cerr<<"ERROR : bad_alloc"<<endl;
	}
}
template<class DT> LinkedList<DT>::~LinkedList() {
	for(Node<DT> **temp=LinkedList::head; *temp!=NULL;) {
		Node<DT> *delnode=*temp;
		*temp=(*temp)->next;
		delete delnode;
	}
	LinkedList::length=0;
	delete LinkedList::head;
}
template<class DT> int LinkedList<DT>::getLength() {
	return LinkedList::length;
}
template<class DT> void LinkedList<DT>::insert(int index, DT data) {
	if(index<0 || index>LinkedList::length)
		throw IndexOutOfBoundsException();
	Node<DT> **temp=LinkedList::head;
	for(int i=0; *temp!=NULL && i<index; temp=&((*temp)->next), i++);
	try{
		Node<DT>* newnode=new Node<DT>(data, *temp);
		*temp=newnode;
		LinkedList::length++;
	} catch(bad_alloc ex) {
		cerr<<"ERROR : bad_alloc"<<endl;
	}
}
template<class DT> DT LinkedList<DT>::remove(int index) {
	if(LinkedList::length==0)
		throw LinkedListEmptyException();
	if(index<0 || index>=LinkedList::length)
		throw IndexOutOfBoundsException();
	Node<DT> **temp=LinkedList::head;
	for(int i=0; *temp!=NULL && i<index; temp=&((*temp)->next), i++);
	Node<DT> *delnode=*temp;
	*temp=(*temp)->next;
	DT data=delnode->data;
	delete delnode;
	LinkedList::length--;
	return data;
}
template<class DT> DT& LinkedList<DT>::operator[](int index) {
	if(LinkedList::length==0)
		throw LinkedListEmptyException();
	if(index<0 || index>=LinkedList::length)
		throw IndexOutOfBoundsException();
	Node<DT> *temp=*LinkedList::head;
	for(int i=0; temp!=NULL && i<index; temp=temp->next, i++);
	return temp->data;
}
template<class DT> DT LinkedList<DT>::get(int index) {
	if(LinkedList::length==0)
		throw LinkedListEmptyException();
	if(index<0 || index>=LinkedList::length)
		throw IndexOutOfBoundsException();
	Node<DT> *temp=*LinkedList::head;
	for(int i=0; temp!=NULL && i<index; temp=temp->next, i++);
	return temp->data;
}
template<class DT> void LinkedList<DT>::set(int index, DT data) {
	if(LinkedList::length==0)
		throw LinkedListEmptyException();
	if(index<0 || index>=LinkedList::length)
		throw IndexOutOfBoundsException();
	Node<DT> *temp=*LinkedList::head;
	for(int i=0; temp!=NULL && i<index; temp=temp->next, i++);
	temp->data=data;
}
template<class DT> void LinkedList<DT>::clear() {
	if(LinkedList::length==0)
		throw LinkedListEmptyException();
	for(Node<DT> **temp=LinkedList::head; *temp!=NULL;) {
		Node<DT> *delnode=*temp;
		*temp=(*temp)->next;
		delete delnode;
	}
	LinkedList::length=0;
}

class Polynomial:public LinkedList<double> {
public:
	Polynomial(){}
	Polynomial(int order):LinkedList(order){}
	int order();
	Polynomial& operator()(double, int);
	Polynomial operator+(Polynomial p);
	Polynomial operator-(Polynomial p);
	Polynomial operator*(Polynomial p);
	friend ostream& operator<<(ostream&, Polynomial);
};
int Polynomial::order() {
	return Polynomial::getLength();
}
Polynomial& Polynomial::operator()(double coeff, int exp) {
	for(int i=Polynomial::getLength();i<=exp;i++)
		Polynomial::insert(i, 0);
	Polynomial::set(exp, coeff);
	return *this;
}
Polynomial Polynomial::operator+(Polynomial p1) {
	Polynomial p((Polynomial::getLength()>p1.getLength())?Polynomial::getLength():p1.getLength());
	for(int i=0;i<Polynomial::getLength();i++)
		p[i]=Polynomial::get(i);
	for(int i=0;i<p1.getLength();i++)
		p[i]+=p1[i];
	return p;
}
Polynomial Polynomial::operator-(Polynomial p1) {
	Polynomial p((Polynomial::getLength()>p1.getLength())?Polynomial::getLength():p1.getLength());
	for(int i=0;i<Polynomial::getLength();i++)
		p[i]=Polynomial::get(i);
	for(int i=0;i<p1.getLength();i++)
		p[i]-=p1[i];
	return p;
}
Polynomial Polynomial::operator*(Polynomial p1) {
	Polynomial p(Polynomial::getLength()+p1.getLength());
	for(int i=0;i<Polynomial::getLength();i++)
		for(int j=0;j<p1.getLength();j++)
			p[i+j]=Polynomial::get(i)*p1[j];
	return p;
}
ostream& operator<<(ostream& os, Polynomial p) {
	bool flag=false;
	for(int i=0;i<p.getLength();i++)
		if(p[i]!=0) {
			if(flag==true)
				cout<<" + ";
			cout<<p[i]<<"x"<<i;
			flag=true;
		}
	return os;
}

main() {
	Polynomial p1, p2;
	p1(3, 0)(2, 1)(-2, 2)(3, 3);
	cout<<"p1 = "<<p1<<endl;
	p2(1, 0)(-2, 1)(5, 4)(6, 2);
	cout<<"p2 = "<<p2<<endl;
	cout<<"p1+p2 = "<<(p1+p2)<<endl;
	cout<<"p1-p2 = "<<(p1-p2)<<endl;
	cout<<"p1*p2 = "<<(p1*p2)<<endl;
}