
#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <iostream>

#define MAX_SIZE 16

template<typename T >
class Binary_Heap final 
{

    private:

    T elements[MAX_SIZE+1];
    size_t size;


    size_t getParent(size_t e) const    { return e/2;   }
    size_t getLeftChild(size_t e) const { return 2*e;   }
    size_t getRightChild(size_t e) const{ return 2*e +1;}
    size_t getRoot() const { return 1; }

    bool isRoot(size_t e) const { return e == 1 ; }
    bool isLastElement(size_t e) const { return e == size; }
    bool compare(T const& lhs, T const& rhs) { return lhs < rhs; }

    // TODO implement both
    void downheap(T element)
    {
        T x = elements[element];
    }

    void upheap(T element)
    {
        T x = elements[element];
    }

    public:

    Binary_Heap() : size(0) { }

    void build_heap(T a[]) 
    {
        std::copy(a, 0, a, 0, a.size);
        for ( int i = a/2-1; i>=0 ; i--)
            downheap(i);
    }

    T getMin() const 
    {
        if(size!=0)
            return elements[1];
    }

    size_t getSize() const
    {
        return this->size;
    }

    void insert(T const& element)
    {
        size_t current = ++size;
        size_t parent = getParent(current);
        while(!isRoot(current) && compare(element, elements[parent]))
        {
            elements[current] = elements[parent];
            current = parent;
            parent = getParent(current);
            
        }
        elements[current] = element;
    }

    void deleteMin()
    {
        size_t current = getRoot();
        size_t child = getLeftChild(current);

        if(child <= size)
        {
            do 
            {
                child += (!isLastElement(child) && compare(elements[child+1], elements[child]));
                elements[current] = elements[child];
                current = child;
                child = getLeftChild(current);

            } while (child <= size);
        }
        T element = elements[size--];

        size_t parent = getParent(current);
        while(!isRoot() && compare(element, elements[parent]))
        {
            elements[current] = elements[parent];
            current = parent;
            parent = getParent(current);
        }
        elements[current] = element;
    }

    void deleteMax()
    {
        T x = elements[0];
        elements[0] = elements[--size];
        downheap(0);
        return x;
    }
    
    // Something doesnt add up
    void print_heap() 
    {
        for (size_t i = this->getRoot(); i < size; i++) {
            std::cout<< this->elements[i] << ", ";
        }
        std::cout<<std::endl;
    }

};

#endif