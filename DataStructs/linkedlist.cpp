
#include <iostream>
#include "linked_list.h"
/*
template<typename T>
class node {
	node *next;
	T* data;

	node(node *n, T* d)
	: next(n), data(d) { }

	friend class linked_list;
	friend class linked_list::iterator;
};
*/
linked_list::iterator::iterator(node *n) : current(n) { }


/*
	The Iterator
*/

bool linked_list::iterator::operator!=(const iterator& i) const {
	return this->current != i.current;
}

T* linked_list::iterator::operator*() const {
	return this->current->data;
}

linked_list::iterator& linked_list::iterator::operator++() {
	this->current = this->current->next;
}

linked_list::iterator linked_list::begin() {
	return linked_list::iterator(this->head);
}

linked_list::iterator linked_list::end() {
	return linked_list::iterator(nullptr);
}

/*
	The Linked List MemberFunctions
*/
// Contructors
linked_list::linked_list(void (*a) (node*))
: head(nullptr), clear(a)
{ }

linked_list::linked_list() {
    this->clear_;
    std::cout << "LinkedList created..." << std::endl;
}
// Destructor
linked_list::~linked_list() {
	node *e = this->head;
	while( e != nullptr) {
		clear(e->data)
		node *temp = e;
		e = e->next;
		delete temp;
	}
}

void linked_list::clear_() {
    this->size = 0;
    this->head = nullptr;
}

// Order by smallest Value first
linked_list& linked_list::insert( node* e ) {
	if ( head == nullptr || e->data < head->data )
		head = new entry(head, e);
		return *this;

	} else {
		node *i = head;
		while (i->next != nullptr && i->next->data < e->data) {
			i = i->next;
		}
		i->next = new node(i->next, e);
		return *this;
	}
}


