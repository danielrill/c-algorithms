#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iterator>
#include <iostream>
#include <memory>

template <typename T>
class Linked_List;

class iterator;

template <typename T>
class Node final
{

	friend class Linked_List<T>;
	friend class iterator;

protected:
public:
	Node<T> *next;
	T data;

	Node(Node<T> *n, T d)
		: next(n), data(d) {}

	Node(T d)
		: next(nullptr), data(d) {}

};

template <typename T>
class Linked_List final
{
	
	Linked_List(const Linked_List &) = delete;
	Linked_List &operator=(const Linked_List &) = delete;
	Linked_List(Linked_List &&) = delete;
	Linked_List &operator=(Linked_List &&) = delete;

private:
	Node<T> *head;
	int size;
	void (*clear)(Node<T> *);

public:
	explicit Linked_List(void (*)(Node<T> *))
		: head(nullptr), clear()
	{
		size = 0;
		std::cout << "LinkedList created..." << std::endl;
	}

	Linked_List()
	{

		this->clear_();
		std::cout << "LinkedList created..." << std::endl;
	}

	// Still a bit messy
	// Needs a quick fix
    Linked_List(std::initializer_list<T> items)
    : head(nullptr)
	{
		if(items.size() == 0)
			return;

		auto it = items.begin();
		for (head = new Node<T>(*it); it != items.end(); it++) {
			Node<T> *n = new Node<T>(*it);
			Node<T> *curr;
			for(curr = head; curr->next && curr->next->data <*it; curr = curr->next)
				continue;
			if(*it < curr->data) {
				n->next = curr;
				head = n;
			} else {
				n->next = curr->next;
				curr->next = n;
			}
		}
	}

	// Copy constructor 
/*
	Linked_List(const Linked_List &list)
	{
		std::cout << " *** COPY *** " << std::endl;
		if (list.head == nullptr)
			return;

		head = list.head;
		Node<T> *current = head;
		size = 1;

		Node<T> *listCurrent = list.head->next;
		while (listCurrent != nullptr)
		{
			current->next = listCurrent->next;
			listCurrent = listCurrent->next;
			current = current->next;
			size++;
		}
		
	}
	*/
	~Linked_List()
	{
		while (head)
		{
			//clear(e);
			Node<T> *tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	void clear_()
	{
		this->size = 0;
		this->head = nullptr;
	}

	int get_size() {
		return this->size;
	}

	Linked_List &insert(Node<T> *e)
	{
		if (head == nullptr || e->data < head->data)
		{
			head = new Node<T>(head, e->data);
			size++;
			return *this;
		}
		else
		{
			Node<T> *i = head;
			while (i->next != nullptr && i->next->data < e->data)
			{
				i = i->next;
			}
			i->next = new Node<T>(i->next, e->data);
			size++;
			return *this;
		}
	}

	Node<T> *search_node(T value)
	{
		Node<T> *e = head;
		while (e->next != nullptr)
		{
			if (e->data == value)
			{
				std::cout << value << " has been found" << std::endl;
				return e;
			}
			e = e->next;
		}
		std::cout << value << " not found" << std::endl;
		return nullptr;
	}

	Node<T>* erase_idx( int idx ) {

		Node<T> *temp = head;
		Node<T> *e;
		int count = 0;

		// Condition checks
		if (this->size == 0) {
			std::cout << "List ist Empty ... " << std::endl;
		}

		if ( idx > size || idx < 0) {
			std::cout << "Invalid Index: OUT OF BOUNDS" << std::endl;
		}

		// First object
		if ( idx == 0) {
			e = head;
			head = head->next;
			std::cout << e->data << " has been removed at idx " << idx << std::endl;
			delete e;
			
			this->size--;
			return head;
		}
		// Last object
		if (idx == this->size) {
			while(count < this->size-2) {
				temp = temp->next;
				count+=1;
			}

			e = temp->next;
			temp->next = nullptr;
			std::cout << e->data << " has been removed at idx " << idx << std::endl;

			delete(e);
			this->size--;
			return head;
		}
		
		// Everything else
		while ( count < idx -1) {
			temp = temp->next;
			count +=1;
		}

		e = temp->next;
		temp->next = temp->next->next;
		std::cout << e->data << " has been removed at idx " << idx << std::endl;
		delete e;
		size--;

		return head;

	}

	void remove( T data) {
		if (this->size == 0) {
			std::cout << "List ist Empty ... " << std::endl;
		}

		if (this->head->data == data) {
			Node<T> *current = head;
			this->head = this->head->next;
			std::cout << data << " has been removed ..." << std::endl;
			delete current;
			this->size--;
		} else {
			Node<T> *prev = this->head;
			Node<T> *current = head->next;

			while(current != nullptr) {
				if(current -> data == data) {
					break;
				} else {
					prev = current;
					current = current->next;
				}
			}

			if(current == nullptr) {
				std::cout << "Value " << data << " not found in the List ..." << std::endl;
			} else {
				prev->next = current->next;
				std::cout << data << " has been removed ..." << std::endl;
				delete current;
				this->size--;
			}
		}
	}


	void add(T value)
	{
		if (head == nullptr || value < head->data)
		{
			head = new Node<T>(head, value);
			std::cout << "Allocated new Node Addr: " << head << std::endl;
			size++;
		}
		else
		{

			Node<T> *p = head;
			while (p->next != nullptr && p->next->data < value)
			{
				p = p->next;
			}
			p->next = new Node<T>(p->next, value);
			std::cout << "Allocated new Node Addr: " << p->next << std::endl;
			size++;
		}
	}

	Node<T> *get(int idx) const
	{
		Node<T> *temp = head;
		Node<T> *e;
		int count = 0;

		// Condition checks
		if (this->size == 0) {
			std::cout << "List ist Empty ... " << std::endl;
		}

		if ( idx > size || idx < 0) {
			std::cout << "Invalid Index: OUT OF BOUNDS" << std::endl;
		}

		// First object
		if ( idx == 0) {
			return head;
		}
		// Last object
		if (idx == this->size) {
			while(count < this->size-2) {
				temp = temp->next;
				count+=1;
			}

			e = temp->next;
			return e;
		}
		
		// Everything else
		while ( count < idx -1) {
			temp = temp->next;
			count +=1;
		}

		e = temp->next;
		return e;
	}

	Node<T> get_last() const
	{
		Node<T> *p = head;
		for (int i = 0; i < size-1; i++)
		{
			p = p->next;
		}
		return *p;
	}

	int get_size() const
	{
		return this->size;
	}

	Node<T> *operator[](int idx) const {
		return this->get(idx);
	}

	void operator+=(T value)
	{
		this->add(value);
	}

	void operator-=(T value)
	{
		this->remove(value);
	}

	friend std::ostream &operator<<(std::ostream &os, Linked_List &list)
	{
		os << "{ ";
		auto *e = list.head;
		while (e != nullptr)
		{
			os << e->data << ", ";
			e = e->next;
		}
		os << "}, size=" << list.size;
		return os;
	}

	class iterator final
	{
	protected:
		// Node<T> *current;
		explicit iterator(Node<T> *n)
			: current(n) {}

		iterator(Linked_List<T> *list)
			: current(list->head) {}

		iterator() 
			: current(nullptr) {}

	public:
		Node<T> *current;
		Linked_List<T> *list;

		bool operator!=(const iterator &i) const
		{
			return this->current != i.current;
		}

		T *operator*() const
		{
			return &this->current->data;
		}

		iterator &operator++()
		{
			if (this->current != nullptr) {
				this->current = this->current->next;
			}
			return *this;
		}

		iterator &operator++(int)
		{
			iterator temp = *this;
			++*this;
			return temp;
		}

		friend class Linked_List<T>;
	};

	iterator begin() 
	{
		return iterator(this->head);
	}
	iterator end() 
	{
		return iterator();
	}
};

#endif
