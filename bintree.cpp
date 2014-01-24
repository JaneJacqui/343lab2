#include "bintree.h"

//-----------------------------------------------------------------------------
// Constructor
// Sets the head of the list to NULL
BinTree::BinTree() {
   root = NULL;
}

/*/-------------------------- Copy Constructor ---------------------------------
// Copy constructor for class List
// Copies all elements from a list to this list
BinTree::BinTree(const BinTree& toCopy) {

	if (&toCopy != this) {
		head = NULL;
		// create list-walking Node pointers
		Node* current = toCopy.root;
		Node* next = current->left;
		// create temp pointer to generate new copy list
		Node* ptr = new Node;
		head = ptr;
		// walk through valid list creating and copying data to new list
		while(current != NULL)	{

			ptr->data = new T(*current->data);
			// be prepared to break at end of list
			if (current->next != NULL) {
				ptr->next = new Node;
				current = next;
				if (next->next != NULL) {
					next = next->next;
				}
				ptr = ptr->next;
			} else {
				ptr->next = NULL;
				break;
			}
		}
	}
}
*/
//---------------------------- Destructor -------------------------------------
// ~List
// Overloaded destructor for list class
BinTree::~BinTree() {
	// makeEmpty is called to clear the list
	makeEmpty();
}

/*/-----------------------------------------------------------------------------
// operator=
// default assignment operator
BinTree& BinTree::operator=(const BinTree& right) {
	// checking for self assignment case
	if (&right != this) {
		makeEmpty();
		// create list-walking Node pointers
		Node* current = right.head;
		Node* next = current->next;
		// create temp pointer to generate new copy list
		Node* ptr= new Node;
		head = ptr;
		// walk through valid list creating and copying data to new list
		while(current != NULL)	{
			ptr->data = new T(*current->data);
			// be prepared to break at end of list
			if (current->next != NULL) {
				ptr->next = new Node;
				current = next;
				if (next->next != NULL) {
					next = next->next;
				}
				ptr = ptr->next;
			} else {
				ptr->next = NULL;
				break;
			}
		}
		return *this;
	} else {
		return *this;
	}
}
*/
//-----------------------------------------------------------------------------
// operator==
// Checks to see if two lists are holding identical objects
// returns true if they are
bool BinTree::operator==(const BinTree& toCompare) const
{
    return (root == 0 && toCompare.root == 0)
        || (root != 0 && toCompare.root != 0 && *root == *toCompare.root);
}

//-----------------------------------------------------------------------------
// operator!=
// Checks to see if one list is not equal to another list
// returns true if the two lists are not equal
bool BinTree::operator!= (const BinTree& right) const {
	if(*this == right) {
		return false;
	} else {
		return true;
	}
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
	} else {
		Node* current = root;		// branch walking variable
		bool inserted = false;		// traversal loop condition

		while (!inserted) {
			// compare new item to each node to determine branch path
			if (*ptr->data < *current->data) {
				if (current->left == NULL) {
					current->left = ptr;
					inserted = true;
				} else
					current = current->left;
			} else if (*ptr->data > *current->data) {
				if (current->right == NULL) {
					current->right = ptr;
					inserted = true;
				}
				else
					current = current->right;
			} else {
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
/*
//------------------------------------------------------------------------------
// operator<<
ostream& operator<<(ostream& output, BinTree& toPrint) {
	toPrint.dumpInorder(output);
	return output;
}

//------------------------------------------------------------------------------
// outputHelper
ostream& dumpInorder(ostream& output) {
	return outputHelper(output);
}

ostream& outputHelper(ostream& output, Node* root) {

}
*/

//-----------------------------------------------------------------------------
// retrieve
// Looks for the first parameter in the list and if it's there sets the second
// parameter to the object. returns true if toRetrieve is found.
bool BinTree::retrieve(const NodeData toRetrieve, NodeData*& toSet) const {

	// the value cannot be found in an empty list
	if (isEmpty()) {
		return false;
	} else {

		Node* current = root;		// branch walking variable
		bool found = false;			// traversal loop condition

		while (!found) {
			// compare the passed item to each node to navigate path
			if (toRetrieve < *current->data) {
				// item not found if it isn't right where it should be
				if (current->left == NULL) {
					return false;
				} else
					current = current->left;
			} else if (toRetrieve > *current->data) {
				if (current->right == NULL) {
					return false;
				}
				else
					current = current->right;
			} else {
				// on find, set passed pointer and exit loop
				toSet = current->data;
				found = true;
			}
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// isEmpty 
// check to see if List is empty as defined by a NULL head
bool BinTree::isEmpty() const {
	return (root == NULL);
}

//-----------------------------------------------------------------------------
// makeEmpty
// Empties a list by setting it to NULL
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

void BinTree::sideways(Node* current, int level) const {
   if (current != NULL) {
      level++;
      sideways(current->right, level);

      // indent for readability, 4 spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "    ";
      }

      cout << *current->data << endl;        // display information of object
      sideways(current->left, level);
   }
}
