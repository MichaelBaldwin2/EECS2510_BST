/*
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures
 * Date: 9/29/2019
*/

#pragma once

#include <string>

using namespace std;

class BST
{
public:
	void Insert(string str);
	void Delete(string str);
	void Search(string str);
	void Min();
	void Max();
	void Next(string str);
	void Prev(string str);
	void List();

private:

	struct Node
	{
		Node* parent;
		Node* left;
		Node* right;
		string name;
		int count;

		Node(string name, int count, Node* parent)
		{
			this->name = name;
			this->count = count;
			this->parent = parent;
			left = NULL;
			right = NULL;
		}

		bool IsRoot() { return parent == NULL; }
		bool IsLeaf() { return left == NULL && right == NULL; }
		string ToString() { return name + " " + to_string(count); };
	};

	Node* root;
	bool IsEmpty() { return root == NULL; };
	Node* Find(string str);
	void Traverse(Node* node);
	Node* FindSuccessor(Node* node);
	Node* FindPredecessor(Node* node);
	Node* FindMinimum(Node* node);
	Node* FindMaximum(Node* node);
	void Transplant(Node* u, Node* v);
};