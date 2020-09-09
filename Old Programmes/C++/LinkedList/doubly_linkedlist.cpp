#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "../myexception.h"

using namespace std;
using namespace exception;

template<class DT> class Node {
public:
	DT data;
	Node *next, *prev;
	Node(DT, Node*, Node*);
};
template<class DT> Node<DT>::Node(DT data, Node* next=NULL, Node* prev=NULL) {
	Node<DT>::data=data;
	Node<DT>::next=next;
	Node<DT>::prev=prev;
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
	void traverse();
	vector<int> search(DT);
};
template<class DT> LinkedList<DT>::LinkedList(int size=0) {
	try{
		LinkedList::head=new Node<DT>*;
		*(LinkedList::head)=NULL;
		for(int i=0;i<size; i++) {
			Node<DT> *temp=*(LinkedList::head);
			*(LinkedList::head)=new Node<DT>((DT)0, temp);
			LinkedList::length=0;
		}
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
		Node<DT>* newnode=new Node<DT>(data, *temp, (*temp)->prev);
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
	(*temp)->prev=delnode->prev;
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
template<class DT> void LinkedList<DT>::traverse() {
	for(int i=0; i<getLength(); i++)
		cout<<i<<" -> "<<get(i)<<endl;
}
template<class DT> ostream& operator<<(ostream& os, LinkedList<DT> l) {
	os<<"{";
	for(int i=0; i<l.getLength(); i++)
		os<<(i==0?"":",")<<l[i];
	os<<"}";
	return os;
}
template<class DT> vector<int> LinkedList<DT>::search(DT e) {
	vector<int> result;
	Node<DT> **temp=LinkedList::head;
	for(int i=0; *temp!=NULL; temp=&((*temp)->next), i++)
		if((*temp)->data==e)
			result.push_back(i);
	return result;
}

main() {
	LinkedList<int> l(5);
	int choice=1, e, idx;
	vector<int> search_result;
	while(choice) {
		system("cls");
		cout<<"DOUBLY LINKED LIST"<<endl
			<<endl
			<<"1.Insert at any index"<<endl
		    <<"2.Delete at any index"<<endl
		    <<"3.Delete a specific data"<<endl
		    <<"4.Search"<<endl
		    <<"5.Display"<<endl
		    <<"0.Exit"<<endl
		    <<"Enter your choice_";
		cin>>choice;
		cout<<endl;
		switch(choice) {
		case 0:
			break;
		case 1:
			cout<<"Enter an element : ";
			cin>>e;
			cout<<"Enter the index to be inserted at : ";
			cin>>idx;
			try {
				l.insert(idx, e);
			}catch(IndexOutOfBoundsException ex) {
				cout<<"Error : "<<ex.getMessage()<<endl;
			}
			break;
		case 2:
			cout<<"Enter the index : ";
			cin>>idx;
			try {
				l.remove(idx);
				cout<<"Deleted at index "<<idx<<endl;
			}catch(IndexOutOfBoundsException ex) {
				cout<<"Error : "<<ex.getMessage()<<endl;
			}catch(LinkedListEmptyException ex) {
				cout<<"Error : "<<ex.getMessage()<<endl;
			}
			break;
		case 3:
			cout<<"Enter an element : ";
			cin>>e;
			search_result=l.search(e);
			if(search_result.empty())
				cout<<"Not found"<<endl;
			else if(search_result.size()==1) {
				l.remove(search_result[0]);
				cout<<"Deleted  at index "<<search_result[0]<<endl;
			}
			else {
				cout<<"Match found at index ";
				for(int i=0; i<search_result.size(); i++)
					cout<<search_result[i]<<",";
				cout<<endl;
				cout<<"Do you want to remove all occurance (y=1/n=0) : "<<endl;
				cin>>choice;
				switch(choice) {
					case 1:
						for(int i=0; i<search_result.size(); i++)
							l.remove(search_result[i]-i);
						break;
					case 0:
						cout<<"Enter index : ";
						cin>>idx;
						if(l[idx]==e)
							l.remove(idx);
						else
							cout<<"Wrong index"<<endl;
						break;
				}
				choice=3;
			}
			break;
		case 4:
			cout<<"Enter an element : ";
			cin>>e;
			search_result=l.search(e);
			if(search_result.empty())
				cout<<"Not found"<<endl;
			else {
				cout<<"Match found at index ";
				for(int i=0; i<search_result.size(); i++)
					cout<<search_result[i]<<",";
				cout<<endl;
			}
			break;
		case 5:
			l.traverse();
			break;
		default:
			cerr<<"Wrong choice"<<endl;
		}
		cout<<endl
			<<"Press any key..."<<endl;
		getchar();
		getchar();
	}
}