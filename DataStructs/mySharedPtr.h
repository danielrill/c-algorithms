#ifndef MYSHAREDPTR_H
#define MYSHAREDPTR_H

template<typename T>
class mySharedPtr final {

	private:
		T 	*p;
		int *n;

	public:
		mySharedPtr()
		: p(nullptr), n(nullptr)
		{ }
		
		explicit mySharedPtr( T* q)
		: p(q) , n(new int{1})
		{ }

		~mySharedPtr()
		{
			if (this->n && --*this->n == 0) // CountDown till 0
			{
				delete this->p;
				delete this->n;
			}
		}

		mySharedPtr(const mySharedPtr& v)
		: p(v.p) , n(v.n)
		{
			if(this->n)
			{
				++*this->n;
			}
		}

		mySharedPtr& operator=(const mySharedPtr& v)
		{
			if(this != &v)
			{
				if (this->n && --*this->n == 0)
				{
					delete this->p;
					delete this->n;
				}
				this->p = v.p;
				this->n = v.n;

				if (this->n)
				{
					++*this->n;
				}
			}
			return *this;
		}

		mySharedPtr(mySharedPtr&& v)
		: p(v.p) , n(v.n)
		{
			v.p = nullptr;
			v.n = nullptr;
		}

		mySharedPtr& operator=(mySharedPtr&& v)
		{
			if (this != &v)
			{
				if(this->n && --*this->n == 0)
				{
					delete this->p;
					delete this->n;
				}

				this->p = v.p;
				this->n = v.n;
				v.p = nullptr;
				v.n = nullptr;
			}
			return *this;
		}


		T* get() const {
			return this->p;
		}

		int use_count() const {
			return this->n ? *this->n : 0;
		}

		operator bool() {
			return this->p != nullptr;
		}

		T& operator*() const {
			return *this->p;
		}

		T* operator->() const {
			return this->p;
		}
};

template<typename T>
bool operator==(const mySharedPtr<T>& u, const mySharedPtr<T>& v)
{
	return u.get() == v.get();
}

template<typename T>
bool operator!=(const mySharedPtr<T>& u, const mySharedPtr<T>& v)
{
	return u.get() != v.get();
}

#endif
