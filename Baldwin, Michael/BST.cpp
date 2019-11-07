/*
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures
 * Date: 9/29/2019
*/

#include <iostream>
#include "BST.h"

using namespace std;

/*
 * Inserts a string into the BST. If the string already exists, then it will icnrement it's count.
 * Parameter<str> This is the string to insert into the tree
*/
void BST::Insert(string str)
{
	//If the tree is empty, then we add this node as the root
	if (IsEmpty())
	{
		Node* newNode = new Node(str, 1, NULL);
		root = newNode;
		cout << newNode->ToString() << endl;
		return;
	}

	//First, we search if the node already exists, if so, we can skip all this and just increment
	Node* current = Find(str);
	if (current != NULL) //A node already exists
	{
		current->count++;
		cout << current->ToString() << endl;
	}
	else //No node exists yet for this value
	{
		current = root;
		while (current != NULL)
		{
			if (str < current->name) //If less than, move to the left subtree
			{
				if (current->left == NULL) //No node to the left, add a new one
				{
					Node* newNode = new Node(str, 1, current);
					current->left = newNode;
					cout << newNode->ToString() << endl;
					return;
				}
				else //Keep moving through the tree
					current = current->left;
			}
			else if (str > current->name) //Else If greater than, move to the right subtree
			{
				if (current->right == NULL) //No node to the right, add a new one
				{
					Node* newNode = new Node(str, 1, current);
					current->right = newNode;
					cout << newNode->ToString() << endl;
					return;
				}
				else //Keep it moving
					current = current->right;
			}
		}
	}
}

/*
 * Deletes an entry (string) from this tree, if it exists.
 * This function will take care of transplanting the affected subtree's back together.
 * Parameter<str> The string to search for and delete
*/
void BST::Delete(string str)
{
	//First thing is search of the node is even in the tree, if not, we can skip all this nonsense
	Node* current = Find(str);
	if (current == NULL)
		cout << str << " -1" << endl;
	else if (current != NULL && current->count > 1)
	{
		current->count--;
		cout << current->ToString() << endl;
	}
	else //if(current == NULL && current->count == 1)
	{
		/* Three cases to handle with deletion:
		 * 1) Node is a leaf: in that case just delete the node, fix it's parents ref to the deleted child
		 * 2) Node has one child: Set this nodes child as the child of the parent, delete this node
		 * 3) Node has two children: Nodes successor replaces it, original right subtree becomes the successors right subtree now, same with the left subtree.
		 *
		 * We're just gonna use Transplant for most of it though
		*/

		if (current->left == NULL)
			Transplant(current, current->right);
		else if (current->right == NULL)
			Transplant(current, current->left);
		else
		{
			Node* successor = FindSuccessor(current);
			if (successor->parent != current)
			{
				Transplant(successor, successor->right);
				successor->right = current->right;
				successor->right->parent = successor;
			}
			Transplant(current, successor);
			successor->left = current->left;
			successor->left->parent = successor;
		}

		cout << current->name << " 0" << endl;
		delete current;
		current = NULL;
	}
}

/*
 * Searchs in the entire tree for a string and prints to console if found (or if not found)
 * Parameter<str> The string to search for
*/
void BST::Search(string str)
{
	Node* node = Find(str);
	if (node != NULL)
		cout << node->ToString() << endl;
	else
		cout << str << " 0" << endl;
}

/*
 * Finds and prints to console the minimum "node" in this tree.
 * Parameter<str> The string to search for
*/
void BST::Min()
{
	if (IsEmpty())
		cout << endl;
	else
		cout << FindMinimum(root)->name << endl;
}

/*
 * Finds and prints to console the maximum "node" in this tree.
 * Parameter<str> The string to search for
*/
void BST::Max()
{
	if (IsEmpty())
		cout << endl;
	else
		cout << FindMaximum(root)->name << endl;
}

/*
 * Finds the succesor to the inputed string
 * Parameter<str> The string that we use to search for it's successor from
 */
void BST::Next(string str)
{
	Node* current = Find(str);
	if (current == NULL)
		cout << endl;
	else if (current != NULL)
	{
		BST::Node* successor = FindSuccessor(current);
		if (successor == NULL)
			cout << endl;
		else
			cout << successor->name << endl;
	}
}

/*
 * Finds the predecessor to the inputed string.
 * Parameter<str> The string that we use to search for it's predecessor from.
 */
void BST::Prev(string str)
{
	Node* current = Find(str);
	if (current == NULL)
		cout << endl;
	else if (current != NULL)
	{
		BST::Node* predecessor = FindPredecessor(current);
		if (predecessor == NULL)
			cout << endl;
		else
			cout << predecessor->name << endl;
	}
}

/*
 * Lists the entire tree in order to the console.
 */
void BST::List()
{
	if (IsEmpty())
		cout << endl;
	else
		Traverse(root);
}

//=======================================================\\
//EVERYTHING UNDER HERE IS PRIVATE FUNCTIONS!!!
//So, please, don't take points off for returning/parameter Node's.
//=======================================================\\

/*
 * Used for searching the tree when you want to get a node pointer back as opposed to just a string.
 * Parameter<str> The string to search for
 * Returns the node that contains the supplied string, or NULL if not found
*/
BST::Node* BST::Find(string str)
{
	Node* current = root;
	while (current != NULL) //'Current' will be NULL if 'root == NULL', which is intended!
	{
		if (current->name == str)
			return current;
		else if (str < current->name)
			current = current->left;
		else
			current = current->right;
	}
	return current;
}

/*
 * Traverses the tree (or subtree), calls Traversal on it's children, and prints out to console.
 * Parameter<node> The node to start the traversal from (in this subtree)
*/
void BST::Traverse(Node* node)
{
	if (node != NULL)
	{
		if (node->left != NULL)
			Traverse(node->left);
		cout << node->ToString() + "\n";
		if (node->right != NULL)
			Traverse(node->right);
	}
}

/*
 * Finds the successor node to a node in a subtree
 * Parameter<node> The node to start from (the subtree "root")
 * Returns the successor node in the subtree, or NULL if the tree is empty
*/
BST::Node* BST::FindSuccessor(Node* node)
{
	Node* current = node;
	if (current != NULL)
	{
		if (current->right != NULL) //First case, get the minimum node starting from this nodes right child.
			return FindMinimum(current);
		else //Right child is NULL, we've got to travel back up the tree boys!
		{
			Node* nextNode = current->parent;
			while (nextNode != NULL && current == nextNode->right)
			{
				current = nextNode;
				nextNode = nextNode->parent;
			}
			return nextNode;
		}
	}

	return NULL;
}

/*
 * Finds the predecessor node to a node in a subtree
 * Parameter<node> The node to start from (the subtree "root")
 * Returns the predecessor node in the subtree, or NULL if the tree is empty
*/
BST::Node* BST::FindPredecessor(Node* node)
{
	Node* current = node;
	if (current != NULL)
	{
		if (current->left != NULL) //First case, get the maximum node starting from this nodes left child.
			return FindMaximum(current);
		else //Left child is NULL, we've got to travel back up the tree boys!
		{
			Node* prevNode = current->parent;
			while (prevNode != NULL && current == prevNode->left)
			{
				current = prevNode;
				prevNode = prevNode->parent;
			}
			return prevNode;
		}
	}

	return NULL;
}

/*
 * Finds the maximum node in a subtree
 * Parameter<node> The node to start from (the subtree "root")
 * Returns the maximum node in the subtree, or NULL if none exist (node is a leaf)
*/
BST::Node* BST::FindMinimum(Node* node)
{
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

/*
 * Finds the minimum node in a subtree
 * Parameter<node> The node to start from (the subtree "root")
 * Returns the minimum node in the subtree, or NULL if none exist (node is a leaf)
*/
BST::Node* BST::FindMaximum(Node* node)
{
	Node* current = node;
	while (current->right != NULL)
		current = current->right;
	return current;
}

/*
 * Transplant agorithm presented in class and in the book.
*/
void BST::Transplant(Node* u, Node* v)
{
	if (u->parent == NULL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != NULL)
		v->parent = u->parent;
}