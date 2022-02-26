#ifndef NODE_H
#define NODE_H

#include "linked_list.h"

template<typename T>
class node {
	node *next;
	T* data;

	node(node *n, T* d)
	: next(n), data(d) { }

	friend class linked_list;
	friend class linked_list::iterator;
};

#endif
