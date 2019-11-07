/*
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures
 * Date: 9/29/2019
*/

#include <string>
#include <iostream>
#include "BST.h"

using namespace std;

string ToLower(string str);

int main()
{
	BST bst = BST();

	while (true)
	{
		string str1, str2;
		cin >> str1;
		str1 = ToLower(str1);

		if (!str1.empty())
		{
			if (str1 == "insert")
			{
				cin >> str2;
				bst.Insert(str2);
			}
			else if (str1 == "delete")
			{
				cin >> str2;
				bst.Delete(str2);
			}
			else if (str1 == "search")
			{
				cin >> str2;
				bst.Search(str2);
			}
			else if (str1 == "min")
				bst.Min();
			else if (str1 == "max")
				bst.Max();
			else if (str1 == "next")
			{
				cin >> str2;
				bst.Next(str2);
			}
			else if (str1 == "prev")
			{
				cin >> str2;
				bst.Prev(str2);
			}
			else if (str1 == "list")
				bst.List();
			else if (str1 == "help")
			{
				cout << "insert <string> : inserts a new item into the tree" << endl;
				cout << "delete <string> : deletes an item from the tree" << endl;
				cout << "search <string> : searches for an item in tree and displays the number of them" << endl;
				cout << "min             : outputs the minimum item in the tree" << endl;
				cout << "max             : outputs the maximum item in the tree" << endl;
				cout << "next <string>   : outputs the specified item's successor" << endl;
				cout << "prev <string>   : Outputs the specified item's predecessor" << endl;
				cout << "list            : traverses and outputs all items in the tree" << endl;
				cout << "help            : displays this list of available commands" << endl;
				cout << "exit <string>   : exits the program" << endl;
			}
			else if (str1 == "exit")
			{
				return 0;
			}
		}
	}

	return -1;
}

string ToLower(string str)
{
	string tempStr;
	for (char c : str)
		tempStr += tolower(c);
	return tempStr;
}