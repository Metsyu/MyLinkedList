/*
 *
 * Author: Joseph Maldonado
 * ID#: 010880953
 *
 * This file contains the implementation of the LinkedList class.
 * The description of each method is given at the beginning of each method.
 *
 */

#include "LinkedList.h"

//Default Constructor
LinkedList :: LinkedList()
{
	head = tail = NULL;
}

//Copy Constructor
LinkedList :: LinkedList(const LinkedList& orig)
{
	Node * current = head;
	Node * currentOrig = orig.head;
	while (currentOrig != NULL)
	{
		current -> next = new Node;
		current -> elem = currentOrig -> elem;
		currentOrig = currentOrig -> next;
		current = current -> next;
	}
}

//Destructor
LinkedList :: ~LinkedList()
{
	Node * current = head;
	while (current != NULL)
	{
		Node * next = current->next;
		delete current;
		current = next;
	}
	head = NULL;
	tail = NULL;
}

//Returns whether the list container is empty (size is 0)
bool LinkedList :: empty() const
{
	if (head == NULL)
		return true;
	else
		return false;
}

//Removes all elements from the list container, leaving the container with size 0
void LinkedList :: clear()
{
	Node * current = head;
	while (current != NULL)
	{
		Node * next = current -> next;
		delete current;
		current = next;
	}
	head = NULL;
	tail = head;
}

//Returns a reference to the last element in the list container
LinkedList :: reference LinkedList :: back()
{
	return tail -> elem;
}

//Returns a const_reference to the last element in the list container
LinkedList :: const_reference LinkedList :: back() const
{
	return tail -> elem;
}

//Returns a reference to the first element in the list container
LinkedList :: reference LinkedList :: front()
{
	return head -> elem;
}

//Returns a const_reference to the first element in the list container
LinkedList :: const_reference LinkedList :: front() const
{
	return head -> elem;
}

//Assigns new contents to the container, replacing its current contents,
//and modifying its size accordingly
LinkedList& LinkedList :: operator=(const LinkedList& l)
{
	if (this != &l)
	{
		this -> clear();
		for (Node * current = l.head; current != NULL; current = current -> next)
			this -> push_back(current -> elem);
	}
	return * this;
}

//Removes the last element in the list container, reducing its size by 1
void LinkedList :: pop_back()
{
	if (tail -> prev == NULL)
		clear();
	else
	{
		tail = tail -> prev;
		delete tail -> next;
		tail -> next = NULL;
	}
}

//Removes the first element in the list container, reducing its size by 1
void LinkedList :: pop_front()
{
	if (head -> next == NULL)
		clear();
	else
	{
		head = head -> next;
		delete head -> prev;
		head -> prev = NULL;
	}
}

//Adds a new element at the ned of the list container, after its current element,
//increasing its size by 1
void LinkedList :: push_back(const element_type& x)
{
	Node * temp = new Node;
	temp -> elem = x;
	temp -> prev = tail;
	temp -> next = NULL;
	
	if (head == NULL)
		head = temp;
	else
		tail -> next = temp;
	tail = temp;
}

//Inserts a new element at the beginning of the list, right before its current first element,
//increasing its size by 1
void LinkedList :: push_front(const element_type& x)
{
	Node * temp = head;
	head -> prev = new Node;
	head = head -> prev;
	head -> elem = x;
	head -> prev = NULL;
	head -> next = temp;
}

//Sorts the elements in the list, altering their positions within the container
void LinkedList :: sort()
{
	Node * current = head;
	element_type temp;
	if (head == NULL)
		return;
	else
	{
		while (current != NULL)
		{
			Node * compare = current -> next;
			while (compare != NULL)
			{
				if (compare -> elem < current -> elem)
				{
					temp = compare -> elem;
					compare -> elem = current -> elem;
					current -> elem = temp;
				}
				compare = compare -> next;
			}
			current = current -> next;
		}
	}
}

//Constructor that initializes the linked list with n nodes,
//with elem value from 0 to n-1
LinkedList :: LinkedList(unsigned int n)
{
	Node * current = new Node;
	current -> elem = 0;
	head = tail = current;
	Node * previous = current;
	current = current -> next = new Node;
	current -> prev = previous;
	
	for (unsigned int i = 1; i < n; i++)
	{
		current -> elem = i;
		tail = current;
		previous = current;
		current = current -> next = new Node;
		current -> prev = previous;
	}
	head -> prev = NULL;
	tail -> next = NULL;
}

//Prints the linked list in the forwards direction
void LinkedList :: check() const
{
	Node* current = head;
	
	if (current == NULL)
		cout << "It is an empty list!" << endl;
	
	int i = 0;
	while (current != NULL)
	{
		cout << "Node " << i
			 << "\tElem: " << '\t' << current->elem
			 << "\tAddress: " << current
			 << "\tNext Address: " << current->next << endl;
		current = current->next;
		i++;
	}
	
	cout << "----------------------------------------------------------------------" << endl;
}

//Prints the linked list in the backwards direction
void LinkedList :: rcheck() const
{
	Node* current = tail;
	
	if (current == NULL)
		cout << "It is an empty list!" << endl;
	
	int i = 0;
	while (current != NULL)
	{
		cout << "Node " << i
		     << "\tElem: " << '\t' << current->elem
		     << "\tAddress: " << current
		     << "\tNext Address: " << current->next
		     << "\tPrev Address: " << current->prev << endl;
		current = current->prev;
		i++;
	}
	
	cout << "----------------------------------------------------------------------" << endl;
}

//Inserts a node with a value specified by x, after the node specified by pos.
//The first node has position 0. If the number of nodes the in the list is less than pos,
//the node is inserted at the end.
void LinkedList :: insert(unsigned int pos, const element_type& x)
{
	unsigned int tempPos = 0;
	for (Node * current = head; current != NULL; current = current -> next)
		tempPos++;
	
	if (tempPos < pos)
		push_back(x);
	
	tempPos = 0;
	Node * current = head;
	Node * temp = new Node;
	temp -> elem = x;
	while (current -> next != NULL)
	{
		tempPos++;
		if (tempPos > pos)
		{
			goto NEXT;
		}
		current = current -> next;
	}
	NEXT:
	temp -> next = current -> next;
	current -> next -> prev = temp;
	current -> next = temp;
	temp -> prev = current;
}

//Removes the node specified by pos. If the number of nodes in the list is less than pos,
//the node at the end, if any exists, is removed.
void LinkedList :: erase(unsigned int pos)
{
	unsigned int tempPos = 0;
	for (Node * current = head; current != NULL; current = current -> next)
		tempPos++;
	
	if (tempPos < pos)
		pop_back();
	
	tempPos = 0;
	Node * current = head;
	while (current -> next != NULL)
	{
		tempPos++;
		if (tempPos > pos)
		{
			goto NEXT;
		}
		current = current -> next;
	}
	NEXT:
	current -> prev -> next = current -> next;
	current -> next -> prev = current -> prev;
	delete current;
}