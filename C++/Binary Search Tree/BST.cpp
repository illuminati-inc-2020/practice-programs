#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

template <class DT> class Node {
public:
	DT data;
	Node<DT> *left, *right;
	Node(DT, Node<DT>*, Node<DT>*);
};
template <class DT> Node<DT>::Node(DT data, Node<DT> *left=NULL, Node<DT> *right=NULL) {
	Node::data=data;
	Node::left=left;
	Node::right=right;
}
template <class DT> void traverseInorder(Node<DT> **t) {
	if(*t!=NULL) {
		traverseInorder(&(*t)->left);
		cout<<(*t)->data<<" ";
		traverseInorder(&(*t)->right);
	}
}
template <class DT> void traversePostorder(Node<DT> **t) {
	if(*t!=NULL) {
		traversePostorder(&(*t)->left);
		traversePostorder(&(*t)->right);
		cout<<(*t)->data<<" ";
	}
}
template <class DT> void traversePreorder(Node<DT> **t) {
	if(*t!=NULL) {
		cout<<(*t)->data<<" ";
		traversePreorder(&(*t)->left);
		traversePreorder(&(*t)->right);
	}
}
template <class DT> void clear(Node<DT> **t) {
	if(*t!=NULL) {
		clear(&(*t)->left);
		clear(&(*t)->right);
		delete *t;
	}
}
template <class DT> void copyTree(Node<DT> **t2, Node<DT> **t1) {
	if(*t1!=NULL) {
		*t2=new Node<DT>((*t1)->data);
		copyTree(&(*t2)->left, &(*t2)->left);
		copyTree(&(*t2)->right, &(*t2)->right);
	}
}

template <class DT> class BST {
	Node<DT> **root;
public:
	BST();
	BST(const BST&);
	~BST();
	void insert(DT);
	void remove(DT);
	bool isEmpty();
	void traverseInorder();
	void traversePreorder();
	void traversePostorder();
};
template <class DT> BST<DT>::BST() {
	root=new Node<DT>*;
	*root=NULL;
}
template <class DT> BST<DT>::BST(const BST &b) {
	BST::root=new Node<DT>*;
	copyTree(BST::root, b.root);
}
template <class DT> bool BST<DT>::isEmpty() {
	return *root==NULL;
}
template <class DT> BST<DT>::~BST() {
	clear(BST::root);
	delete root;
}
template <class DT> void BST<DT>::insert(DT data) {
	Node<DT> **temp=BST::root;
	while(*temp!=NULL) {
		if(data < (*temp)->data)
			temp=&(*temp)->left;
		else if(data > (*temp)->data)
			temp=&(*temp)->right;
		else 
			return;
	}
	*temp=new Node<DT>(data);
}
template <class DT> void BST<DT>::remove(DT data) {
	Node<DT> **temp=BST::root;
	while(*temp!=NULL) {
		if(data < (*temp)->data)
			temp=&(*temp)->left;
		else if(data > (*temp)->data)
			temp=&(*temp)->right;
		else {
			Node<DT> *oldnode=*temp;
			Node<DT> *left=(*temp)->left;
			*temp=(*temp)->right;
			while(*temp!=NULL)
				temp=&(*temp)->left;
			*temp=left;
			delete oldnode;
			return;
		}
	}
}
template <class DT> void BST<DT>::traverseInorder() {
	::traverseInorder(BST::root);
	cout<<endl;
}
template <class DT> void BST<DT>::traversePostorder() {
	::traversePostorder(BST::root);
	cout<<endl;
}
template <class DT> void BST<DT>::traversePreorder() {
	::traversePreorder(BST::root);
	cout<<endl;
}

main() {
	BST<char> tree;
	int choice=1;
	char e;
	char msg[50]="";
	while(choice) {
		system("cls");
		cout<<"BINARY SEARCH TREE"<<endl
			<<endl
			<<"1.Insert"<<endl
		    <<"2.Delete"<<endl
		    <<"3.Calculate height"<<endl
		    <<"0.Exit"<<endl
			<<endl;
		if(tree.isEmpty())
			cout<<"Tree is empty"<<endl;
		else {
			cout<<endl
				<<"Inorder : ";
			tree.traverseInorder();
			cout<<"Preorder : ";
			tree.traversePreorder();
			cout<<"Postorder : ";
			tree.traversePostorder();
			cout<<endl;
		}
		cout<<endl
			<<msg<<endl
			<<endl
			<<"Enter your choice_";
		cin>>choice;
		cout<<endl;
		switch(choice) {
		case 0:
			return 0;
		case 1:
			cout<<"Enter a character : ";
			cin>>e;
			try{
				tree.insert(e);
				sprintf(msg, "%c Inserted", e);
			} catch (NodeAlreadyExistsException ex) {
				sprintf(msg, "Node already exists");
			}
			break;
		case 2:
			cout<<"Enter an integer : ";
			cin>>e;
			try {
				tree.remove(e);
				sprintf(msg, "%c deleted", e);
			}catch(NodeNotFoundException ex) {
				sprintf(msg, "Node not found");
			}
			break;
		case 3:
			try {
				sprintf(msg, "Height = %d", tree.height());
			} catch(...) {
				sprintf(msg, "Height = 0");
			}
			break;
		default:
			sprintf(msg, "Wrong choice");
		}
	}

}
