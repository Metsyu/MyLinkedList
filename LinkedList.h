#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

typedef int element_type;

class LinkedList
{
public:
	typedef element_type& reference;
	typedef const element_type& const_reference;
	LinkedList();
	LinkedList(const LinkedList& orig);
	~LinkedList();
	bool empty() const;
	void clear();
	reference back();
	const_reference back() const;
	reference front();
	const_reference front() const;
	LinkedList& operator=(const LinkedList& l);
	void pop_back();
	void pop_front();
	void push_back(const element_type& x);
	void push_front(const element_type& x);
	void sort();
	explicit LinkedList(unsigned int n);
	void check() const;
	void rcheck() const;
	void insert(unsigned int pos, const element_type& x);
	void erase(unsigned int pos);


private:
	struct Node
	{
		element_type elem;
		Node * next;
		Node * prev;
	};
	Node * head;
	Node * tail;
};

#endif /* LINKEDLIST_H */
