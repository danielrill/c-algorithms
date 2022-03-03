#ifndef TEST_CPP
#define TEST_CPP

#include "mySharedPtr.h"
#include "myArray.h"
#include "linked_list.h"
//#include "linked_list.cpp"
//#include "myList.h"
#include <iostream>
#include <string>

namespace
{

    void delete_node(Node<int> *n);
}

/*

template<typename T>
class node {
    node *next;
    T* data;

    node(node *n, T* d)
    : next(n), data(d) { }

    node(T val)
    : next(nullptr), data(val) { }

};
*/

void arrayTest()
{
    std::cout << "Testing Array Class ..." << '\n'
              << std::endl;
    myArray<int, 4> a = {10, 20, 33, 40};

    for (unsigned i = 0; i < a.size(); i++)
    {
        std::cout << i << ": " << a[i] << std::endl;
    }

    myArray<std::string, 5> b = {"This", "is", "a", "String", "Array"};
    for (unsigned i = 0; i < b.size(); i++)
    {
        std::cout << i << ": " << b[i] << std::endl;
    }
    std::cout << '\n'
              << "terminated Succesfully" << '\n'
              << std::endl;
}

void sharedPtrTest()
{
    std::cout << "Testing sharedPtr Class ..." << '\n'
              << std::endl;
    mySharedPtr<int> p{new int{123}}; // use count = 1

    auto q = p; // copy

    if (q == p)
    {
        std::cout << "*p = *q = *"
                  << q.get() << '(' << q.use_count() << ") = " << *q << '\n';

        mySharedPtr<int> r;
        if (r != q)
        {
            r = q; // use count++
            std::cout << "*p = *q = *r = *"
                      << r.get() << '(' << r.use_count() << ") = " << *r << '\n';
        }
    } // Destructor r: use_count--

    auto r = std::move(q);
    if (!q)
    {
        std::cout << "q = " << q.get() << '\n';
    }

    if (r)
    {
        std::cout << "*p = *r = *"
                  << r.get() << '(' << r.use_count() << ") = " << *r << '\n';
    }
    std::cout << '\n'
              << "terminated Succesfully" << '\n'
              << std::endl;
}

void linkedlistTest()
{
    Node<int> *x = new Node<int>(5);

    Linked_List<int> *list = new Linked_List<int>();
    list->add(5);
    list->insert(x);

    Linked_List<int> listaa(delete_node);
    listaa.add(5);
    listaa.insert(x);
    for (int i = 0; i < 20; i++)
    {
        list->add(i);
        listaa.add(i);
    }

    for (auto *n : listaa)
    {
        if (*n == 8)
        {
            std::cout << *n << std::endl;
        }
    }

    std::cout << listaa << std::endl;
    listaa.search_node(7);
    listaa.search_node(21);
    listaa += (44);
    std::cout << listaa << std::endl;

    Node<int> *f = listaa.search_node(2);
    std::cout << f->data << std::endl;
    listaa.remove(1);

    std::cout << listaa << std::endl;

    /*
    TODO
    for e in list
        remove e
    */
}

int main()
{

    linkedlistTest();
    // arrayTest();
    // sharedPtrTest();
}

namespace
{

    void delete_node(Node<int> *n)
    {
        delete n;
    }
}
#endif