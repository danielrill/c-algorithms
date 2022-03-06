/*
	Not complete as of <06.03.2022>
	Author: Daniel Rill
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iterator>
#include <iostream>


template <typename T>
class Linked_List;

class iterator;

template <typename T>
class Node final
{

	friend class Linked_List<T>;
	friend class iterator;

	//Node<T>(const T& d) : next(nullptr), data(d) { }
	//Node<T>(T&& d) : next(nullptr), data(std::forward<T>(d)) { }

protected:
public:
	Node<T> *next;
	T data;

	Node(Node<T> *n, T d)
		: next(n), data(d) {}

	Node(T d)
		: next(nullptr), data(d) {}

	friend std::ostream &operator<<(std::ostream &os, Node &node)
	{
		Node<T> e = node;
		os << " {" ;
		os << e.data << ", " << e.next << " }";
		return os;
	}
};



template <typename T>
class Linked_List final
{
	// No Move-Semantics 
	Linked_List(Linked_List &&) = delete;
	Linked_List &operator=(Linked_List &&) = delete;

private:
	Node<T> *head;
	int size;
	void (*clear)(Node<T> *);

public:

	/*
		Three different constructors
	*/
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

	// TODO: Sort the Entries during init
    Linked_List(std::initializer_list<T> items)
    //: head(nullptr)
	{
		if(items.size() != 0)
		{	
            auto it = items.begin();
            head = new Node<T>(*it); // first item
            size++; 
            Node<T>* current = head;
            ++it;
            for (; it != items.end(); ++it)
            {
				
				//for(current = head; current->next && current->next->data <*it; current = current->next)
				//	continue;

				current->next = new Node<T>(*it);
                current = current->next;
                size++;

            }
		}
	}

	
/* First approach doesnt work as expected, 2nd does not sort 

auto it = items.begin();
head = new Node<T>(*it);
for (; it != items.end(); ++it) {
	Node<T> *n = new Node<T>(*it);
	this->size++;
	Node<T> *curr;
	std::cout << n << ", " << curr << " , " << *it << std::endl;
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

auto it = listOfItems.begin();
head = std::make_unique<Node>(*it);
size++; // added first item
Node* current = head.get();
++it;
for (; it != listOfItems.end(); ++it)
{
    current->next = std::make_unique<Node>(*it);
    current = current->next.get();
    size++;
}
*/
/*
	Copy-Semantics
*/

	Linked_List(const Linked_List &list)
	: head(nullptr), size(0)
	{
		std::cout << " *** COPY *** " << std::endl;

		Node<T> **current = &head;

		for(Node<T> *e = list.head; e; e = e->next)
		{
			(*current) = new Node<T>(e->data);
			current = &(*current)->next;
			size++;
		}	
	}
	Linked_List<T>& operator=(Linked_List const& list)
	{
		Linked_List<T> temp(list);
		temp.swap(*this);
		return *this;
	}

	void swap(Linked_List<T>& other)
	{
		using std::swap;
		swap(head,  other.head);
    	swap(size,    other.size);
	}
	/*
		Destructor
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

	/*
		Clear the list 
		used in constructor
	*/
	void clear_()
	{
		this->size = 0;
		this->head = nullptr;
	}

	/*
		return the size of the List
	*/
	int get_size() {
		return this->size;
	}

	/*
		insert a Node 
		Returns a new List
	*/
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

	/*
		Search a specific Value
		stops at first occurence
	*/

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

	/*
		Erase a Node at a given index
		return Type probably should be changed
	*/
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

	/*
		Remove a given value
		stops at first occurence
	*/

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

	/*
		add a Node with given Value in a sorted manner
	*/
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

	/*
		get the data of a given Node
	*/

	T* get_data(Node<T> *n) const {
		return n->data;
	}

	/*
		return a Node at a given index
	*/
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

	/*
		returns the last Node
	*/
	Node<T> *get_last() const
	{
		Node<T> *p = head;
		for (int i = 0; i < size-1; i++)
		{
			p = p->next;
		}
		return p;
	}

	/*
		returns the int size of the List
		probably better with size_t
	*/
	int get_size() const
	{
		return this->size;
	}

	/*
		not really usefull
	*/
	Node<T> *operator[](int idx) const {
		return this->get(idx);
	}

	/*
		add a value by simply += operator
	*/
	void operator+=(T value)
	{
		this->add(value);
	}
	/*
		remove a value by simply -= operator
	*/
	void operator-=(T value)
	{
		this->remove(value);
	}

	/*
		prints the List at a given width
		probably usefull to give thw width as param
	*/
	void print_list() const
	{
		if (this->get_size() != 0)
		{
			int count = 0;
			Node<T> *current = head;
			while (current != nullptr) {
				if(count % 20 != 0) 
				{
					std::cout << current->data << ", ";
					current = current->next;
					count++;
				} else {
					std::cout << '\n' << current->data << ", ";
					current = current->next;
					count++;
				}
			}
			std::cout << "( " << this->get_size() << " Entries in the List )"<< std::endl;
		}
	}

	/*
		returns an output stream
	*/
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

	/*
		The nested iterator class
	*/
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

		T &operator->() const
		{
			return this->current->data;
		}

		iterator &operator++()
		{
			if (this->current != nullptr) {
				this->current = this->current->next;
			}
			return *this;
		}
		/*
			sometimes useful 
		*/
		iterator &operator++(int)
		{
			auto temp = *this;
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

#endif // Linked_List
