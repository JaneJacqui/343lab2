//CLASS		bintree.h
//AUTHOR	Jeffrey Thompson and Lisa Peterman
//VERSION	1/13/2014

#include <iostream>
#include <fstream>
#include "nodedata.h"

using namespace std;
//-----------------------------------------------------------------------------
// Binary Search Tree: 
//
// Other features include:
//				-- 
//
// Assumptions:
//	-- 
//-----------------------------------------------------------------------------


class BinTree { // you add class/method comments and assumptions 
 
	friend ostream & operator<<(ostream &, const NodeData &);

public: 
	BinTree(); // constructor 
	BinTree(const BinTree &); // copy constructor 
	~BinTree(); // destructor, calls makeEmpty 
	bool isEmpty() const; // true if tree is empty, otherwise false 
	void makeEmpty(); // make the tree empty so isEmpty returns true 
	BinTree& operator=(const BinTree &); 
	bool operator==(const BinTree &) const; 
	bool operator!=(const BinTree &) const; 
	bool insert(NodeData*); 
	bool retrieve(const NodeData, NodeData*&) const; 
	void displaySideways() const; // provided, displays the tree sideways 
 

private: 

	struct Node { 
		NodeData* data; // pointer to data object 
		Node* left; // left subtree pointer
		Node* right; // right subtree pointer

		ostream& operator<<(ostream& output) {
			output << data;
			return output;
		}

	}; 

	Node* root; // root of the tree 
 
	// utility functions 
	void inorderHelper() const; 
	void sideways(Node*, int) const; // provided, helper for displaySideways() 

}; 
