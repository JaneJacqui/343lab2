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
/*/-----------------------------------------------------------------------------
// operator==
// Checks to see if two lists are holding identical objects
// returns true if they are
bool BinTree::operator== (const BinTree& right) const {
	Node* current1 = head;
	Node* current2 = right.head;
 
	// Check to see if both lists are NULL
	if(current1 == NULL && current2 == NULL) {
		return true;
	}
	// Walks through and compares each object
	while((current1->next != NULL) && (current2->next != NULL)) {
		if(*current1->data != *current2->data) {
			return false;
		}
		// move so that next elements in ech list can be compared
		current1 = current1->next;
		current2 = current2->next;
	}
	if(*current1->data != *current2->data) {
		return false;
	}
	if((current1->next == NULL && current2->next != NULL) || 
	   (current1->next != NULL && current2->next == NULL)) {
		return false;
	} else {
		// both lists contain the same objects
		return true;
	}
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
*/
//-----------------------------------------------------------------------------
// insert 
// insert an item into list; operator< of the T class
// has the responsibility for the sorting criteria
bool BinTree::insert(NodeData* dataptr) {
   
	Node* ptr = new Node;     // exception is thrown if memory is not allocated
   ptr->data = dataptr;
   dataptr = NULL;
   ptr->left = ptr->right = NULL;
   if (isEmpty()) {
      root = ptr;
   }
   else {
      Node* current = root;
      bool inserted = false;

      // if item is less than current item, insert in left subtree,
      // otherwise insert in right subtree
      while (!inserted) {
         if (*ptr->data < *current->data) {
            if (current->left == NULL) {              // at leaf, insert left
               current->left = ptr;
               inserted = true;
            }
            else
               current = current->left;               // one step left
         }
         else {
            if (current->right == NULL) {             // at leaf, insert right
               current->right = ptr;
               inserted = true;
            }
            else
               current = current->right;              // one step right
         }
      }
   }
   return true;
}

/*/-----------------------------------------------------------------------------
// retrieve
// Looks for the first parameter in the list and if it's there sets the second
// parameter to the object. returns true if toRetrieve is found.
bool BinTree::retrieve(const NodeData toRetrieve, NodeData*& toSet) const {
	Node* prev = head;
	// Head case check
	if (isEmpty()) {
		toSet = NULL;
		return false;
	} else if (*prev->data == toRetrieve) {
		toSet = prev->data;
		return true;
	}
	Node* current = head->next;
	// Walks through the list to see if it finds the first parameter
	while ((current != NULL) && (*prev->data != toRetrieve)) {
		prev = current;
		current = current->next;
	}
	if (*prev->data == toRetrieve) {
		toSet = prev->data;
		return true;
	} else {
		toSet = NULL;
	}
	// object is not in the list
	return false;
}
*/
//-----------------------------------------------------------------------------
// isEmpty 
// check to see if List is empty as defined by a NULL head
bool BinTree::isEmpty() const {
	return (root == NULL);
}

/*/-----------------------------------------------------------------------------
// makeEmpty
// Empties a list by setting it to NULL
void BinTree::makeEmpty() {
	if (!isEmpty()) {
		Node* current = head;
		// deletes all elements of the list until it reaches the end
		while (current != NULL){
			Node* next = current->next;
			delete current->data;
			delete current;
			current = next;
		}
	}
	// nulls the head pointer 
	head = NULL;
}
*/
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
