
#include "mySharedPtr.h"
#include "myArray.h"
#include "linked_list.h"
#include "Binary_Heap.h"
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
    int x = 7;
    Node<int> *y = new Node<int>(x);

    Linked_List<int> *list = new Linked_List<int>();
    list->add(5);
    list->insert(y);

    Linked_List<int> listaa(delete_node);
    listaa.add(5);
    for (int i = 0; i < 30; i++)
    {
        list->add(i);
        listaa.add(i);
    }

    Linked_List<int> initList = {11, 44, 123, 22, 31, 55};
    for (auto *e : initList) 
    {
        std::cout << *e << std::endl;
    }
    //std::cout << initList << std::endl;

    for (auto *n : listaa)
    {
        if (*n == 8)
        {
            std::cout << *n << std::endl;
        }
    }

    Linked_List<int> ll = listaa;
    for (auto *e : ll)
        std::cout << *e << std::endl;
    
    Node<int> *e = ll.get_last();
    std::cout << *e << std::endl;
    std::cout << *ll.get_last() << std::endl;

    std::cout << listaa << std::endl;
    listaa.search_node(7);
    listaa.search_node(21);
    listaa += (44);
    std::cout << listaa << std::endl;
 
    listaa.remove(4);
    listaa.remove(0);
    listaa.remove(5);
    listaa.remove(5);
    listaa.remove(1);

    std::cout << listaa << std::endl;
    listaa.add(5);
    listaa.add(6);
    listaa.add(8);
   

    std::cout << listaa << std::endl;
    
    std::cout << listaa.get_last()->data << " last object"<< std::endl;

    for ( auto *e : listaa) {
        
        std::cout << *e << std::endl;
        
    }

    auto it = list->begin();
    for (; it != list->end(); it++) {
        std::cout << *it << " , "<< &it << std::endl;
    }

    listaa.erase_idx(15);
    std::cout << listaa.get_size() << " list size" << std::endl;
    listaa.erase_idx(listaa.get_size());
    Node<int> *g = listaa.erase_idx(1);
    std::cout << *g << " erased Node" << std::endl;

    std::cout << listaa  << " empty ? "<< std::endl;


    std::cout << listaa.get(0)->data << " list at 0" << std::endl;
    std::cout << listaa.get(1)->data << " list at 1" << std::endl;
    std::cout << listaa.get(2)->data << " list at 2" << std::endl;
    std::cout << listaa.get(3)->data << " list at 3" << std::endl;
    std::cout << listaa.get(16)->data << " list at 16" << std::endl;
    std::cout << listaa.get(listaa.get_size()-1)->data << " list at end" << std::endl;

    std::cout << listaa.get_size() << " list size" << std::endl;


    std::cout << listaa  << " empty ? "<< std::endl;
    delete y;
    delete list;

    
    listaa.print_list();
    //list->print_list();
}

void binary_heapTest()
{
    Binary_Heap<int> heap;
    heap.insert(5);
    for (size_t i = 0; i < 12; i++)
        heap.insert(i);

    std::cout << "heap size is " << heap.getSize() << std::endl;
    heap.print_heap();

}

int main()
{
    binary_heapTest();
    //linkedlistTest();
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
