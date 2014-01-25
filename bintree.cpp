/* @file bintree.cpp
@author Jeffrey Thompson and Lisa Peterman
CSS 343 Lab 2
*/

#include "bintree.h"

//-----------------------------------------------------------------------------
// Constructor
// Sets the head of the list to NULL
BinTree::BinTree() {
	root = NULL;
}

//-------------------------- Copy Constructor ---------------------------------
// Copy constructor for class List
// Copies all elements from a list to this list
BinTree::BinTree(const BinTree& toCopy) {

	*this = toCopy; // uses overloaded operator=
}

//---------------------------- Destructor -------------------------------------
// ~List
// Overloaded destructor for list class
BinTree::~BinTree() {
	// makeEmpty is called to clear the list
	makeEmpty();
}

//-----------------------------------------------------------------------------
// operator=
// default assignment operator
BinTree& BinTree::operator=(const BinTree& toCopy) {
	// checking for self assignment 
	if (&toCopy != this) {
		return *this;
	}
	makeEmpty();
	copyHelper(root, toCopy.root);
	return *this;
}

//-----------------------------------------------------------------------------
// copyHelper
// Copies source tree data into this tree.
void BinTree::copyHelper(Node* root, const BinTree& toCopy) {
	if (toCopy.isEmpty()){
		root = NULL;
	}
	else {
		root = new Node;
		root->data = toCopy->data;
		copyHelper (root->left, toCopy.root->left);
		copyHelper(root->right, toCopy.root->right);
	}
}

	
//-----------------------------------------------------------------------------
// operator==
// Checks to see if two lists are holding identical objects
// returns true if they are
bool BinTree::operator==(const BinTree& toCompare) const {
	return (root == 0 && toCompare.root == 0)
		|| (root != 0 && toCompare.root != 0 && *root == *toCompare.root);
}

//-----------------------------------------------------------------------------
// operator!=
// Checks to see if one list is not equal to another list
// returns true if the two lists are not equal
bool BinTree::operator!= (const BinTree& right) const {
	return !(*this == right);
}

//-----------------------------------------------------------------------------
// insert 
// insert an item into list; operator< of the T class
// has the responsibility for the sorting criteria
bool BinTree::insert(NodeData* dataptr) {

	// allocate memory for new Node to be added
	Node* ptr = new Node;
	ptr->data = dataptr;
	dataptr = NULL;
	ptr->left = ptr->right = NULL;

	// in empty list, inserted item becomes root
	if (isEmpty()) {
		root = ptr;
	}
	else {
		Node* current = root;		// branch walking variable
		bool inserted = false;		// traversal loop condition

		while (!inserted) {
			// compare new item to each node to determine branch path
			if (*ptr->data < *current->data) {
				if (current->left == NULL) {
					current->left = ptr;
					inserted = true;
				}
				else
					current = current->left;
			}
			else if (*ptr->data > *current->data) {
				if (current->right == NULL) {
					current->right = ptr;
					inserted = true;
				}
				else
					current = current->right;
			}
			else {
				// if item is a duplicate, deallocate the memory reserved
				// and return that the item was not inserted
				delete ptr;
				ptr = NULL;
				return false;
			}
		}
	}
	return true;
}

//------------------------------------------------------------------------------
// operator<<
ostream& operator<<(ostream& output, BinTree& toPrint) {
	toPrint.publicHelper(output);
	return output;
}

//------------------------------------------------------------------------------
// publicHelper
// Helps output operator
ostream& BinTree::publicHelper(ostream & output) {
	return outputHelper(output, root);
}

//------------------------------------------------------------------------------
// outputHelper
// Helps output operator
ostream& BinTree::outputHelper(ostream& output, Node* root) {
	if (root != NULL) {
		outputHelper(output, root->left);
		output << root->data;
		outputHelper(output, root->right);
	}
	return output;
}

//-----------------------------------------------------------------------------
// retrieve
// Looks for the first parameter in the list and if it's there sets the second
// parameter to the object. returns true if toRetrieve is found.
bool BinTree::retrieve(const NodeData toRetrieve, NodeData*& toSet) const {

	// the value cannot be found in an empty list
	if (isEmpty()) {
		return false;
	}
	else {

		Node* current = root;		// branch walking variable
		bool found = false;			// traversal loop condition

		while (!found) {
			// compare the passed item to each node to navigate path
			if (toRetrieve < *current->data) {
				// item not found if it isn't right where it should be
				if (current->left == NULL) {
					return false;
				}
				else
					current = current->left;
			}
			else if (toRetrieve > *current->data) {
				if (current->right == NULL) {
					return false;
				}
				else
					current = current->right;
			}
			else {
				// on find, set passed pointer and exit loop
				toSet = current->data;
				found = true;
			}
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// getHeight
// Locates the BinTree height of target data. Nonexistent data returns as 0.
int BinTree::getHeight(const NodeData& target) const {
	return heightHelper(target, root, 1);
}

//-----------------------------------------------------------------------------
// heightHelper
//Rrecursively searches given tree for target data and returns height if found, 
// 0 otherwise.
int BinTree::heightHelper(const NodeData& target, const Node* current, int level) const {

	if (current == NULL) {  // is a leaf
		return 0;
	}
	if (*current->data == target) { 
		return level;
	}

	int childLevel = 0; // walks down all possible children to find target

	// search left children
	childLevel = heightHelper(target, current->left, level + 1);

	if (childLevel != 0) { // target exists in this branch
		return childLevel;
	}

	// searches right children
	childLevel = heightHelper(target, current->right, level + 1);

	return childLevel;		
}

//-----------------------------------------------------------------------------
// bstreeToArray
// Fills an array of NodeData* by using an inorder traversal of the tree. It 
// leaves the tree empty.
void BinTree::bstreeToArray(NodeData* toFill[]) {
	Node* current = root; // pointer to walk through tree

	inorderHelper(current, toFill, 0);
}

//-----------------------------------------------------------------------------
// inorderHelper
// Helps fill an array in order from a binary search tree.
int BinTree::inorderHelper(Node* root, NodeData* toFill[], int element) const {
	//if (current != NULL) {
	//	element++;
	//	inorderHelper(current->right, toFill, element++);
	//	toFill[element] = *current->data;
	//	*current->data = NULL;
	//	inorderHelper(current->left, toFill, element++);
	//}

		if (root->left != NULL) {
			element = inorderHelper(root->left, toFill, element++);
		}
		toFill[element++] = root->data;
		delete root->data;
		if (root->right != NULL) {
			element = inorderHelper(root->right, toFill, element);
		}
		return element; // return the last position filled in by this invocation
}

//-----------------------------------------------------------------------------
// arrayToBSTree
// Builds a balanced BinTree from a sorted array of NodeData* leaving the 
// array filled with NULLs.
void BinTree::arrayToBSTree(NodeData* toCopy[]){
	makeEmpty();       // clear array if needed
	int current = 0;   // walks through array
	int high = 0;      // tracks largest element

	// determines highest element in array (up to 100)
	while (toCopy[current] != NULL && current <= 99) {
		high = current;
		current++;
	}

	root = treeHelper(toCopy, 0, high, root); 
}

//-----------------------------------------------------------------------------
// treeHelper
// Recursively constructs BinTree out of provided array.
BinTree::Node* BinTree::treeHelper(NodeData *toCopy[], int low, int high, Node* treeRoot) {
	int mid = (low + high) / 2;   // calculates place to split tree
	
	treeRoot = new Node; 

	// initialize children and data of new Node
	treeRoot->left = NULL;
	treeRoot->right = NULL;
	treeRoot->data = NULL;

	// lower of split subtrees
	if (low < mid) {
		treeRoot->left = treeHelper(toCopy, low, mid - 1, treeRoot->left);
	}

	treeRoot->data = toCopy[mid]; // copy data
	toCopy[mid] = NULL;  // erase data in array once copied

	// upper of split subtrees
	if (mid < high) {
		treeRoot->right = treeHelper(toCopy, mid + 1, high, treeRoot->right);
	}

	return treeRoot;
}


//-----------------------------------------------------------------------------
// isEmpty 
// Checks to see if BinTree is empty as defined by a NULL root.
bool BinTree::isEmpty() const {
	return (root == NULL);
}

//-----------------------------------------------------------------------------
// makeEmpty
// Empties a BinTree.
void BinTree::makeEmpty() {
	if (!isEmpty()) {
		delete root;
	}
	// nulls the head pointer 
	root = NULL;
}

//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------------------------------------------------------
// sideways
// Recursively outputs members of a binary tree in a sideways formation.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}
