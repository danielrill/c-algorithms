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

	~Linked_List()
	{
		Node<T> *e = this->head;
		while (e != nullptr)
		{
			// clear(e->data);
			Node<T> *tmp = e;
			e = e->next;
			delete tmp;
		}
	}

	void clear_()
	{
		this->size = 0;
		this->head = nullptr;
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
	bool remove(T value)
	{
		Node<T> *n = head;
		while (n->next != nullptr)
		{

			if (n->next->data == value)
			{

				auto *tmp = n->next;
				n->next = n->next->next;

				std::cout << tmp->data << " has been removed" << std::endl;
				delete n;
				size--;
				return true;
			}
		}
		return false;
	}

	T *search_idx(int idx)
	{
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

	T *get(int idx) const
	{
		if (idx < 0 || idx > size)
		{
			return nullptr;
		}
		Node<T> *p = head;
		for (int i = 0; i < idx; i++)
		{
			p = p->next;
		}
		return &p->data;
	}

	Node<T> *get_last() const
	{
		Node<T> *p = head;
		for (int i = 0; i < size; i++)
		{
			p = p->next;
		}
		return p;
	}

	int get_size() const
	{
		return this->size;
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
			this->current = this->current->next;
			return *this;
		}

		friend class Linked_List<T>;
	};

	iterator begin()
	{
		return iterator(this);
	}
	iterator end()
	{
		return iterator(this->get_last());
	}
};

#endif
