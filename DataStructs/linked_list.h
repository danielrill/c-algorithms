#ifndef LINKED_LIST_H
#define LNKED_LIST_H

#include <iterator>


class linked_list final {
	linked_list(const linked_list&) = delete;
	linked_list& operator=(const linked_list&) = delete;
	linked_list(linked_list&&) = delete;
	linked_list& operator=(linked_list&&) = delete;


private:
	class node;
	node *head;
	int size;
	void (*clear) (node*);

public:
	explicit linked_list(void (*) (node*));
	
	linked_list();

	~linked_list();
	
	void clear_();

	linked_list& insert(node*);

	class iterator final {
	private:
		node *current;
		explicit iterator(node*);

	public:
		bool operator!=(const iterator&) const;
		node* operator*() const;
		iterator& operator++();

		friend class linked_list;
	};

	iterator begin();
	iterator end();
};

#endif
