#ifndef LINKED_LIST_H
#define LNKED_LIST_H

#include <iterator>


class linked_list final {
	linked_list(const linked_list&) = delete;
	linked_list& operator=(const linked_list&) = delete;
	linked_list(linked_list&&) = delete;
	linked_list& operator=(linked_list&&) = delete;


private:
	class entry;
	entry *head;
	int size;
	void (*clear) (entry*);

public:
	explicit linked_list(void (*) (entry*));
	
	linked_list();

	~linked_list();
	
	void clear_();

	linked_list& insert(entry*);

	class iterator final {
	private:
		entry *current;
		explicit iterator(entry*);

	public:
		bool operator!=(const iterator&) const;
		entry* operator*() const;
		iterator& operator++();

		friend class linked_list;
	};

	iterator begin();
	iterator end();
};

#endif
